# Yocto integration

How the RDK HAL AIDL interface libraries are built, packaged and consumed in a
Yocto build. For the underlying CMake build and the non-Yocto consumption
options, see [Build Integration](build_integration.md).

**Named `-aidl` throughout** (recipe, packages, install paths) so nothing here is
confused with the legacy C HAL (`rdk-halif-*`) it coexists with during
migration.

## What is what

| Item | Purpose |
| ---- | ------- |
| `rdk-halif-aidl.bb` in [`rdkcentral/meta-binder`](https://github.com/rdkcentral/meta-binder) | Builds this repository's root CMake project and packages the result ([PR 24](https://github.com/rdkcentral/meta-binder/pull/24)) |
| Baseline release files | YAML manifests listing the available interfaces and versions |
| `HALIF_AIDL_INTERFACE_VERSION_APPENDS` | `local.conf` variable that adds extra interface versions to a build |

## How it works

CMake reads a manifest of interfaces and versions, builds each of them and
installs everything into a single install directory. The recipe splits that
directory into packages:

- `rdk-halif-aidl-<interface>-v<version>` — the runtime package of one interface
  version, for example `rdk-halif-aidl-indicator-v0-1-0-0`;
- `rdk-halif-aidl-dev` — depends on all the `-dev` packages, so a consumer only
  needs `DEPENDS += "rdk-halif-aidl-dev"` to build against every interface.

Baseline release files list the interfaces and versions that are available. The
vendor layer has exactly one version of each interface; the middleware may carry
several versions of the same interface side by side.

## Consuming the interfaces

Add the build dependency, then clear the default runtime dependencies and add
back only the interfaces the component needs at runtime:

```bitbake
DEPENDS = "libbinder rdk-halif-aidl"

RDEPENDS:${PN} = " "
RDEPENDS:${PN} += " rdk-halif-aidl-indicator-v0-1-0-0"
```

The component's own build then links with CMake or pkg-config; see
[Consuming the interfaces](build_integration.md#consuming-the-interfaces).

## Developer workflows

| Goal | What to do |
| ---- | ---------- |
| Adopt a new interface | Add it to the baseline YAML |
| Move the middleware to a new version | Append the new version to the baseline YAML and keep the old one |
| Move the vendor layer to a new version | Add it through `HALIF_AIDL_INTERFACE_VERSION_APPENDS` in `local.conf` |
| Try changes before a release | Add `current` to `HALIF_AIDL_INTERFACE_VERSION_APPENDS` and use `current` as the version in CMake or pkg-config |

`current` versions run the AIDL compiler, so the `aidl` tool must be available
to the build.
