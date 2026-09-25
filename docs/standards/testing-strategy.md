# HAL Interface Testing Strategy

This document defines how conformance testing relates to the AIDL interface
contracts and HAL Feature Profiles (HFP) in this repository, and the rules a
test-suite author follows. The interface repo (`rdk-halif-aidl`) defines
**what** a HAL must do; the test suites that verify it are owned by a
**separate** test project.

## Separation of concerns

Four artifacts, distinct owners:

| Concern | Artifact | Owned by | Answers |
| --- | --- | --- | --- |
| Interface contract | `.aidl` (versioned) | `rdk-halif-aidl` (this repo) | Which methods and types exist at each interface version |
| Declared capability | `hfp-<component>.yaml` | `rdk-halif-aidl` (this repo) | The maximum feature set a platform's HAL may expose |
| Runtime capability | `getCapabilities()` | the running service | What this implementation actually supports right now |
| Test suite + config | ut-core / RAFT suites + per-platform YAML | separate test project | How the interface is exercised on a given platform |

The interface contract and the declared capability profile are **published from
here**. The test suites and their per-platform configuration are **owned by the
test project** — they consume this repo's `.aidl` and HFP files.

## Test levels and frameworks

| Level | Scope | Framework | Config source |
| --- | --- | --- | --- |
| L1 | Individual API functions | ut-core (C/C++, on device) | ut-core `ut-kvp` profile YAML |
| L2 | Module behaviour, state, capability interactions | ut-core (C/C++, on device) | ut-core `ut-kvp` profile YAML |
| L3 | Component with external stimulus | RAFT / ut-raft (`python_raft`) | RAFT per-platform device/rack YAML |
| L4 | System / vendor-stack interface (VSI, VST smoke) | RAFT / ut-raft (`python_raft`) | RAFT per-platform device/rack YAML |

L1/L2 are device-side C/C++ tests built on **ut-core**, typically one
monolithic binary per component using ut-core's suite organisation. L3/L4 are
Python suites built on **RAFT** (`python_raft`), with **ut-raft** providing the
L3–L4 profile classes. The RAFT layer carries its **own per-platform YAML** —
device descriptors, rack maps, platform configuration — provisioned per
platform as each suite requires, and independent of the HFP.

## The capability model

Two independent axes decide whether a call is valid on a given device. A suite
checks both, in this order.

### Version axis — does the method exist?

A test binary links one interface version (or `current`) at compile time; the
running server may be older or newer. The server reports its identity through
two methods on every interface:

- `int32_t getInterfaceVersion()` — the release version encoded as an int with
  fixed field widths **1-2-2-1** over `<era>.<major>.<minor>.<bugfix>`
  (`0.2.0.0` → `2000`, `1.0.0.0` → `100000`); a development build of
  `current/` reports the generator default.
- `std::string getInterfaceHash()` — the frozen contract hash, or
  `"notfrozen"` for a development build, which makes no compatibility promise.

Tests gate on these values through the `halcompat` helpers
(`common/current/halcompat.h`, installed with the common headers) — the same
one code path clients use, with the encoding and the era rules internal to the
helper. See the [AIDL Versioning Guide](versioning-guide.md) for the encoding
and the era compatibility rules the helper implements.

### Capability axis — is this optional feature supported here?

Within a version, features may be optional per platform. The service reports
what it supports through `getCapabilities()`. For `bootreason`
(`Capabilities.aidl`):

```cpp
Capabilities caps;
auto status = service->getCapabilities(&caps);
// caps.supportedBootCauses is BootCause[]; caps.supportedResetTypes is ResetType[]
```

A suite treats `getCapabilities()` as the runtime source of truth: it skips
checks for absent features rather than failing them.

### HFP bounds runtime capability

The HFP (`hfp-<component>.yaml`, in each component's version directory)
declares the platform's **maximum** supported feature set, keyed by the
component directory name. Real `bootreason/current/hfp-bootreason.yaml`
fields:

```yaml
bootreason:
    interfaceVersion: current
    supportedBootCauses:      # subset of BootCause
      - WATCHDOG
      - COLD_BOOT
      # ...
    supportedResetTypes:      # subset of ResetType
      - MAINTENANCE_REBOOT
      # ...
    supportedPowerSources:    # subset of PowerSource
      - PSU
      # ...
```

The binding invariant a conformance test asserts is:

```text
getCapabilities()  ⊆  HFP declared features
```

The HFP is capability declaration, consumed by tests as the upper bound. The
test framework's own configuration (which tests run, where the device is) is
the separate per-platform YAML owned by the test project.

## Version-adaptive suites (L1/L2)

One test binary, built against the latest interface, adapts at runtime to
whatever server version it meets — full coverage on a current server, graceful
degradation on an older one. This mirrors production client behaviour and
validates the server's backward-compatibility promise at the same time.

### Discover the version once, at suite init

ut-core suite init/clean functions return `int` (0 for success) and are
registered with `UT_add_suite()`, which returns the suite handle that
`UT_add_test()` requires:

```cpp
// bootreason_tests.cpp
#include <ut.h>
#include <halcompat.h>
#include <com/rdk/hal/bootreason/IBootReason.h>

using com::rdk::hal::bootreason::IBootReason;
using com::rdk::hal::bootreason::Capabilities;
namespace hc = com::rdk::hal::halcompat;

static android::sp<IBootReason> gService;

static int bootreason_suite_init(void)
{
    gService = hc::getService<IBootReason>();
    if (gService == nullptr) {
        return -1;
    }
    // Dev images run "notfrozen" servers; allow them explicitly.
    if (!hc::isCompatible(gService, /*allowUnfrozen=*/true)) {
        return -1;
    }
    UT_LOG("Server version: %d hash: %s",
           gService->getInterfaceVersion(),
           gService->getInterfaceHash().c_str());
    return 0;
}

static int bootreason_suite_clean(void)
{
    gService = nullptr;
    return 0;
}
```

The version is queried once here; every test in the suite gates on the cached
service through `halcompat`.

### Gate version-specific tests, skip-don't-fail

Feature gates name the **additive release** that introduced the API. Suppose a
hypothetical `getBootCount()` was added to `IBootReason` in release 0.2.1.0:

```cpp
static void test_l1_boot_count(void)
{
    if (!hc::atLeast(gService, 0, 2, 1)) {   // added in 0.2.1.0
        UT_LOG("Server predates 0.2.1.0 - skipping getBootCount test");
        return;                              // skip, not a failure
    }
    int32_t count = 0;
    auto status = gService->getBootCount(&count);
    UT_ASSERT(status.isOk());
    UT_ASSERT(count >= 0);
}
```

`hc::atLeast()` applies the era rules internally: in era 1 plain ordering is
sufficient; in era 0 the gate also requires the same major, because an era-0
major bump is a breaking change. A test never probes for a method by calling
it when a version gate can answer first.

### Fallback signals, when probing is the test

A fallback test deliberately calls the newer method to verify the server's
behaviour at the boundary. Two distinct signals, per
[client usage of Stable AIDL](../whitepapers/client_usage_of_stable_aidl.md):

```cpp
auto status = gService->getBootCount(&count);
if (status.transactionError() == ::android::UNKNOWN_TRANSACTION) {
    // Method does not exist on this server (older implementation):
    // fall back to the pre-0.2.1.0 API.
} else if (status.exceptionCode() ==
           ::android::binder::Status::EX_UNSUPPORTED_OPERATION) {
    // Method exists but the feature is unavailable on this platform:
    // consistent with getCapabilities() - skip.
} else {
    UT_ASSERT(status.isOk());
}
```

The cpp backend is non-throwing: every outcome arrives through the returned
`android::binder::Status` (`status.toString8()` for diagnostics).

### Validate capabilities against the HFP and the platform profile

L2 suites assert the capability invariant. Platform expectations come from the
ut-core `ut-kvp` profile passed at run time; HFP list fields are read with the
list accessors:

```cpp
static void test_l2_capabilities_within_hfp(void)
{
    Capabilities caps;
    auto status = gService->getCapabilities(&caps);
    UT_ASSERT(status.isOk());

    // Declared upper bound, from the platform's HFP.
    uint32_t declared =
        UT_KVP_PROFILE_GET_LIST_COUNT("bootreason/supportedBootCauses");

    // Every runtime-reported cause must appear in the declared list.
    for (auto cause : caps.supportedBootCauses) {
        UT_ASSERT(hfpDeclaresBootCause(cause, declared));  // suite helper
    }
}
```

Scalar expectations use the typed accessors —
`UT_KVP_PROFILE_GET_BOOL(key)`, `UT_KVP_PROFILE_GET_UINT32(key)`,
`UT_KVP_PROFILE_GET_STRING(key, outBuffer)` — and the
`UT_ASSERT_EQUAL_KVP_PROFILE_*` assertion macros compare a live value against
the profile in one step.

### Register and run

```cpp
int main(int argc, char** argv)
{
    UT_init(argc, argv);

    UT_test_suite_t* pSuiteL1 = UT_add_suite("[L1 bootreason]",
                                             bootreason_suite_init,
                                             bootreason_suite_clean);
    UT_add_test(pSuiteL1, "getBootCause", test_l1_get_boot_cause);
    UT_add_test(pSuiteL1, "getBootCount (0.2.1.0+)", test_l1_boot_count);

    UT_test_suite_t* pSuiteL2 = UT_add_suite("[L2 bootreason]",
                                             bootreason_suite_init,
                                             bootreason_suite_clean);
    UT_add_test(pSuiteL2, "capabilities within HFP",
                test_l2_capabilities_within_hfp);

    return UT_run_tests();
}
```

The profile is supplied with the `-p` switch; ut-core's modes (`-c` console,
`-a` automated xUnit XML, `-b` basic) select how results are reported:

```bash
./bootreason_tests -p platform_profile.yml -a
```

### Multi-version execution

The same binary runs unmodified against every server generation:

| Server | Expected suite behaviour |
| --- | --- |
| Older frozen release | Base tests pass; gated tests skip with a version message; fallback tests exercise the older path |
| Current frozen release | Everything passes; fallback tests take the new path |
| Development build (`"notfrozen"`) | Runs only with `allowUnfrozen` — dev images opt in; a production image reporting `"notfrozen"` is a deployment error |

## Building a suite

Link the test binary against the interface library it targets — the
development build or a pinned frozen snapshot — plus the binder SDK libraries:

```cmake
target_link_libraries(bootreason_tests
    bootreason-vcurrent-cpp        # or bootreason-v0.2.0.0-cpp, pinned
    # ... binder SDK + ut-core libraries per the test project's build
)
```

Generated headers are module-local (`<module>/current/include/`); snapshot
libraries are versioned so multiple releases coexist on one image. See
[Third-Party Build Integration](build_integration.md) for consuming the
interface libraries from an external build, and the ut-core wiki (in this
site's Testing section) for the suite build template.

## Rules for a suite author

- Link against a specific interface version (or `current`); gate
  newer-release calls with `hc::atLeast()` naming the additive release that
  introduced them — never probe with raw calls when a gate can answer.
- Discover the server version once at suite init through `halcompat`; skip
  gated tests on older servers, don't fail them.
- Distinguish the two fallback signals: `UNKNOWN_TRANSACTION` means the
  method doesn't exist (older server); `EX_UNSUPPORTED_OPERATION` means the
  feature is unavailable on this platform.
- Treat `getCapabilities()` as the runtime source of truth for optional
  features, and assert `getCapabilities() ⊆ HFP` as the conformance
  invariant.
- Keep platform and device wiring in the test project's per-platform YAML —
  not hard-coded in the test, and not conflated with the HFP.
- Treat `"notfrozen"` from a production image as a deployment error;
  development images opt in with `allowUnfrozen`.

## References

- [AIDL Versioning Guide](versioning-guide.md) — version encoding, era rules,
  `halcompat` compatibility checks
- [Client Usage of Stable AIDL](../whitepapers/client_usage_of_stable_aidl.md)
  — the fallback signal contract in full
- [Third-Party Build Integration](build_integration.md) — linking the
  interface libraries from an external build
- [References](../references/references.md) — RAFT / `python_raft`, ut-raft,
  and ut-core repositories and wikis
- HFP source — `*/current/hfp-*.yaml` in this repository

---

**Applies to:** `rdk-halif-aidl`, all components.
