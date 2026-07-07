# halcompat — Client Compatibility Helpers

`halcompat.h` is the client-side adapter for RDK HAL AIDL service
compatibility. It installs with the `common` component headers and is the
single place version and compatibility logic lives in client code — clients
ask the same three questions in every era and never handle version values,
encodings, or era rules directly.

```cpp
#include <halcompat.h>
#include <com/rdk/hal/bootreason/IBootReason.h>

using com::rdk::hal::bootreason::IBootReason;
namespace hc = com::rdk::hal::halcompat;

auto service = hc::getService<IBootReason>();

if (!hc::isCompatible(service)) {
    // Absent, unfrozen (development build), or incompatible server.
    return;
}

if (hc::atLeast(service, 0, 3)) {   // release 0.3.0.0 introduced the API
    service->newMethod();
} else {
    service->existingMethod();      // pre-0.3 fallback
}
```

## The Three Questions

| Call | Question | Answer covers |
| --- | --- | --- |
| `getService<I>()` | Give me the service | Service-manager lookup via the interface's published `serviceName`; returns the typed proxy or `nullptr` |
| `isCompatible(service)` | Can I use it? | Present **and** frozen **and** version-compatible with the headers this client compiled against (`I::VERSION`) |
| `atLeast(service, era, major, minor, bugfix)` | Is feature X available? | The server carries at least the named release, under the era rules |

The arguments to `atLeast()` are the **release fields of the feature being
gated** — the release that introduced an API is the one fact a client
genuinely owns (`atLeast(service, 0, 3)` reads "added in 0.3.0.0"). No raw
encoded values appear in client code.

## Era Behaviour

The compatibility rules differ between the pre-AIDL era (`0.x.y.z`) and the
frozen-AIDL era (`1.x.y.z` onward). The helper applies the right rule
internally — client code is identical in both:

| Server state | `isCompatible()` / `atLeast()` behaviour |
| --- | --- |
| Era 0, same major | Compatible when the server is the same or newer (`>=` within the major) |
| Era 0, different major | **Not compatible** — era-0 majors make no cross-major promise, even when numerically newer |
| Era 1+, both sides | Compatible when the server is the same or newer — additive-only discipline makes ordering sufficient |
| Era differs from the client's | Not compatible — the era transition is a compatibility boundary; rebuild against the new era's headers |
| Development build (`"notfrozen"`) | Not compatible by default — see below |

These rules are enforced by `static_assert`s inside the header, so every
compile that includes `halcompat.h` re-verifies them.

## Development Images

A pre-freeze development server reports `getInterfaceHash() ==
"notfrozen"` and makes no compatibility promise. `isCompatible(service)`
rejects it; a development image that accepts unfrozen servers opts in
explicitly:

```cpp
if (hc::isCompatible(service, /*allowUnfrozen=*/true)) { ... }
```

Production clients never pass `allowUnfrozen`.

## Requirements

- Header-only: include `<halcompat.h>` from the installed `common`
  include tree; no additional library to link beyond the binder libraries
  every HAL client already uses.
- Works with any generated RDK HAL interface: the templates use the
  interface's `serviceName()`, `VERSION`, `getInterfaceVersion()` and
  `getInterfaceHash()` surface.

## References

- [AIDL Versioning Guide](../../../docs/standards/versioning-guide.md) —
  the version encoding and era contract the helper implements.
- [Client Usage of Stable AIDL](../../../docs/whitepapers/client_usage_of_stable_aidl.md)
  — the adapter pattern and error-semantics guidance.
