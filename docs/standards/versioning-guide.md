# RDK HAL AIDL Versioning Guide

## Overview

Every HAL component is released as versioned snapshots (`<component>/<X.Y.Z.W>/`)
frozen from its development tree (`<component>/current/`). This guide defines
what the version number means, what a running service reports through
`getInterfaceVersion()` / `getInterfaceHash()`, and how clients check
compatibility.

## Release Version Format

A release version has four fields:

```text
<pre-post-aidl> . <major> . <minor> . <bugfix>
```

| Field | Meaning |
| --- | --- |
| `pre-post-aidl` (era) | `0` = pre-AIDL-versioning era: breaking changes are permitted with a major bump. `1` = the component has adopted full AIDL frozen-interface discipline: **breaking changes are no longer allowed, ever**. |
| `major` | Bumped for a **breaking** interface change (only possible in era `0`). |
| `minor` | Bumped for a **backwards-compatible addition** (new methods/fields/enum values, appended). |
| `bugfix` | Bumped for documentation/comment-only respins. The interface surface is unchanged. |

### The Era Promise

- **`0.x.y.z`** — the interface may still break between majors: `0.2.*.*` does
  not promise compatibility with `0.1.*.*` clients. Within one major,
  additions are backwards-compatible: a `0.2.3.*` server serves any `0.2.y.*`
  client with `y <= 3`.
- **`1.x.x.x`** — freezing `1.0.0.0` is the moment the component signs up for
  "never break again". From then on every change must be additive, exactly as
  [Android AIDL versioning](https://source.android.com/docs/core/architecture/aidl/aidl-versioning)
  requires. A truly incompatible redesign requires a **new interface
  component** (e.g. `IBootReason` → `IBootNew`); the old one keeps working and
  clients migrate at their own pace.

## What a Service Reports

Generated interface code carries two identity values, baked in when the
snapshot is frozen by the release flow:

| State | `getInterfaceVersion()` | `getInterfaceHash()` |
| --- | --- | --- |
| Frozen snapshot | the release version, encoded as an int (below) | the toolchain contract hash of the snapshot's AIDL (the committed `<version>/.hash`) |
| Development build (`current/`) | generator default | `"notfrozen"` |

`getInterfaceHash() == "notfrozen"` is the **pre-freeze marker**: the build
comes from an unfrozen tree and makes no compatibility promise. A real hash
identifies exactly one frozen contract.

These values are baked in by `scripts/release.sh` at freeze time. A snapshot
frozen before that stamping existed reports the development defaults
(`VERSION = 1` / `"notfrozen"`) until it is next re-frozen.

### Version Encoding

`getInterfaceVersion()` returns the release version packed into an `int32`
with fixed field widths **1-2-2-1** (era, major, minor, bugfix):

| Release | `getInterfaceVersion()` |
| --- | --- |
| 0.1.0.0 | `1000` |
| 0.1.0.1 | `1001` |
| 0.2.0.0 | `2000` |
| 0.10.0.0 | `10000` |
| 0.99.99.9 | `99999` (era-0 maximum) |
| 1.0.0.0 | `100000` |
| 1.2.3.4 | `102034` |

To decode: zero-pad to 6 digits and read `E|MM|NN|B` —
`era = v / 100000`, `major = (v / 1000) % 100`, `minor = (v / 10) % 100`,
`bugfix = v % 10`.

The same encoding is used in every era, so the value is monotonic across a
component's entire history and never goes backwards. Field limits are
`major`/`minor` ≤ 99 and `bugfix` ≤ 9 — a tenth doc-only respin of the same
minor therefore forces a minor bump.

## Client Compatibility Checks

```cpp
#include <com/rdk/hal/bootreason/IBootReason.h>

std::shared_ptr<IBootReason> service = IBootReason::fromBinder(binder);

int32_t client = IBootReason::VERSION;            // compile-time constant
int32_t server = service->getInterfaceVersion();  // runtime value
std::string hash = service->getInterfaceHash();

if (hash == "notfrozen") {
    // Development build: no compatibility promise. Acceptable on a dev
    // image; a production client should treat this as a mismatch.
}

auto era   = [](int32_t v) { return v / 100000; };
auto major = [](int32_t v) { return (v / 1000) % 100; };

bool compatible;
if (era(server) >= 1 && era(client) >= 1) {
    // Era 1+: additive-only discipline makes ordering sufficient.
    compatible = (server >= client);
} else {
    // Era 0: compatibility only holds within one major.
    compatible = (era(server) == era(client))
              && (major(server) == major(client))
              && (server >= client);
}
```

Feature detection then works on the encoded value:

```cpp
if (service->getInterfaceVersion() >= 3000) {   // 0.3.0.0 added this API
    service->newMethod();
} else {
    service->existingMethod();                  // pre-0.3 fallback
}
```

## Allowed and Prohibited Changes

Backwards-compatible (bump **minor**):

- ADD new methods at the END of an interface
- ADD new fields at the END of a parcelable
- ADD new enum values (clients handle unknown values)
- ADD a new parcelable, enum or interface type

Breaking (bump **major**; era `0` only — forbidden once era `1` is declared):

- Remove or rename methods, fields or enum values
- Change method signatures, return types or field types
- Reorder methods or fields (declaration order is ABI: it defines binder
  transaction ids and parcel layout)
- Change an enum value's backing integer
- Remove `@VintfStability` or change wire-affecting annotations

Documentation-only (bump **bugfix**): comment and doc changes; the interface
surface is untouched.

### Mechanical Classification

The binder toolchain classifies interface changes structurally
(`linux_binder_idl`'s `aidl_ops dump-surface` / `diff-surface`): it dumps the
declared surface of two trees and reports `breaking`, `major` (additive) or
`none`. The release flow enforces this as the pre-tag structural audit:

```bash
./scripts/release.sh --audit --strict
```

For every component, the audit classifies the last-frozen → `current/` diff
and fails the release when the declared change class or `metadata.yaml`
version disagrees with what the AIDL actually changed (see the
[versioning SOP](../governance/versioning-sop.md) for the full audit
procedure):

| `diff-surface` class | Era `0.x.y.z` requires | Era `1.x.x.x` requires |
| --- | --- | --- |
| `breaking` | **major** bump | **release fails** — not allowed |
| `major` (additive) | **minor** bump | **minor** bump |
| `none`, sources differ | **bugfix** bump | **bugfix** bump |
| `none`, sources identical | no snapshot | no snapshot |

## Development and Release Workflow

```bash
# 1. Develop freely in current/ — builds report HASH = "notfrozen"
vim bootreason/current/com/rdk/hal/bootreason/IBootReason.aidl
./build_interfaces.sh bootreason

# 2. Choose the bump from the change class (table above) and release.
#    scripts/release.sh freezes current/ into <component>/<X.Y.Z.W>/:
#    it stamps the version + contract hash, regenerates so the snapshot's
#    C++ carries the real getInterfaceVersion()/getInterfaceHash() values,
#    and restores current/ to its unfrozen state.
```

A frozen snapshot is **immutable**: its AIDL, generated C++, `interface.yaml`
version and `.hash` are committed and never edited. Fixes go into `current/`
and ship in the next snapshot.

## Library Naming and Linking

Each snapshot builds a distinctly named library, so multiple versions coexist
on one image:

```text
libbootreason-vcurrent-cpp.so     # development build of current/
libbootreason-v0.2.0.0-cpp.so     # frozen 0.2.0.0 snapshot
```

```cmake
target_link_interfaces_libraries(myapp bootreason-v0.2.0.0-cpp)  # pinned
# OR
target_link_interfaces_libraries(myapp bootreason-vcurrent-cpp)  # development
```

## Deprecating Features

Methods cannot be removed from a released interface. Either keep the method
as a documented no-op:

```cpp
Status BootReason::oldDeprecatedMethod() {
    LOG_WARNING("oldDeprecatedMethod is deprecated, use newMethod instead");
    return Status::ok();
}
```

or, for a genuine redesign, introduce a new interface component and let both
coexist while clients migrate.

## Best Practices

- Plan the interface carefully before its first snapshot; iterate in
  `current/` rather than churning released versions.
- Declare era `1` only when the component is ready to never break again.
- Gate optional features on `getInterfaceVersion()` (encoded values), never on
  probing calls.
- Treat `"notfrozen"` from a production service as a deployment error.
- Never edit a released `<version>/` directory.

## References

- **Semantic versioning primer:** [semantic_versioning.md](semantic_versioning.md)
- **Client Patterns:** [client-patterns.md](client-patterns.md)
- **Migration Guide:** [migration-guide.md](migration-guide.md)
- **Android AIDL Docs:** [Android AIDL Versioning](https://source.android.com/docs/core/architecture/aidl/aidl-versioning)
- **Surface classification tool:** [linux_binder_idl `dump-surface` / `diff-surface`](https://github.com/rdkcentral/linux_binder_idl/blob/develop/README.md)
