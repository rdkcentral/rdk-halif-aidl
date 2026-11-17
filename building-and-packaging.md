# Building and Packaging

This document describes how the project builds and packages its interfaces, and how downstream projects should consume
the resulting artefacts. It does not cover developer-local workflows, such as working on `current` or releasing new
versions; it focuses solely on the build and packaging process as it concerns external consumers.

## Build Process

CMake drives the build. It consumes a YAML file that lists every interface and the versions to build; the same
interface can appear multiple times in this file as long as each entry specifies a different version. From this list,
CMake generates the build graph and installs all interfaces into a single install directory, using version-tagged
filenames or directories where needed.

When building locally, outside of a meta build system, use the helper scripts `build_binder.sh` and `build_modules.sh`.
They install the built dependencies and set up the environment so that the build can find them. Within a standard meta
build system, the build process finds everything it needs automatically, provided well-known paths are in place.

## Packaging

CMake installs all interfaces into a single install directory, as described above. For each interface and version, it
generates a CMake target named `RdkHalifAidl::Interfacename-v0.1.0.0`, which becomes available after calling
`find_package(RdkHalifAidlInterfacename 0.1.0.0 EXACT REQUIRED IMPORTED_TARGET)`. It also generates a pkg-config file
per interface and version, for example `/usr/lib/pkgconfig/rdk-halif-aidl-interfacename-0.1.0.0.pc`, whose `Name` field
is set to `rdk-halif-aidl-interfacename-0.1.0.0`; consumers therefore call
`pkg-config --cflags rdk-halif-aidl-interfacename-0.1.0.0` to retrieve the correct include paths.

Packaging the install directory into consumable artefacts is the meta build system's responsibility. We provide a
`rdk-halif-aidl.bb` recipe in `rdkcentral/meta-binder` that handles this packaging, and the rest of this section assumes
that recipe is in use. The `rdk-halif-aidl-dev` package contains all `-dev` dependencies needed to build against the
interfaces, so consumers should add `DEPENDS += "rdk-halif-aidl-dev"` to their recipes.

To avoid pulling in every artefact when only some are needed, runtime dependencies are split into separate packages.
For example, `rdk-halif-aidl-<interface>-v<version>` contains the runtime artefacts for one specific interface.
Consumers should remove `rdk-halif-aidl` itself from `RDEPENDS` with `RDEPENDS_${PN} = " "`, then add back only the
interfaces they need with `RDEPENDS_${PN} += "rdk-halif-aidl-<interface>-v<version>"`.

For consumption we have a set of baseline release files, that describes the available interfaces and their versions.
For the vendor layer the baseline file will describe exactly one version of each interface and it is expected that a vendor should deliver a corresponding implementation for each listed interface.
In the middleware, the release files may describe multiple versions of each interface, allowing the middleware to select the appropriate implementation based on its requirements.

Futhermore, to enable development and easy adoption of new interfaces, we allow to append additional version of interfaces to a custom build. This is done by setting a Yocto variable `HALIF_AIDL_INTERFACE_VERSION_APPENDS` in local.conf.

## Consumption

Consumers have three ways to link against a packaged interface, in order of preference.

The preferred approach uses CMake directly: call
`find_package(RdkHalifAidlInterfacename 0.1.0.0 EXACT REQUIRED IMPORTED_TARGET)` to obtain the correct CMake target,
then link it into the consumer's target with
`target_link_libraries(my_target PRIVATE RdkHalifAidl::Interfacename-v0.1.0.0)`.

Where CMake is unavailable, consumers can use `pkg-config` instead. Calling
`pkg-config --cflags rdk-halif-aidl-interfacename-0.1.0.0` returns the correct include paths, and
`pkg-config --libs rdk-halif-aidl-interfacename-0.1.0.0` returns the correct link flags. This avoids hard-coding paths
and is an acceptable alternative to the CMake approach.

As a fallback for legacy consumers, the CMake package configuration files still expose variables that let consumers
build the interface code themselves: `RDK_HALIF_AIDL_INTERFACENAME_SRC_FILES` lists the necessary source files, and
`RDK_HALIF_AIDL_INTERFACENAME_HEADERS_FILES` lists the necessary header files. Use this only as a last resort, since it
leads to unnecessary rebuilds and potential ABI mismatches.

As a temporary measure, the build artefacts also include `FindBinder.cmake` and `FindAndroidUtils.cmake` files, along
with `binder.pc` and `utils.pc` pkg-config files. The generated CMake targets use the former transitively, and the
generated pkg-config files use the latter transitively. These files should eventually be delivered by the components
that actually provide Binder and Android Utils, but this project provides them for now.

## Examples

The following examples show how to consume the packaged artefacts from different build systems.

### Yocto

This example is taken from
[`rdk-e/meta-rdk-vendor-polaris-bcm`](https://github.com/rdk-e/meta-rdk-vendor-polaris-bcm/commit/4ddf72f2b0bfa7650dc3833a8c8ae4995b098f3c)
and shows how to consume the packaged artefacts in a Yocto recipe. You can remove all custom CMake settings; the
following is all that is necessary to consume the interface code.

```bitbake
# ... other recipe content
DEPENDS = "libbinder rdk-halif-aidl"
RDEPENDS:${PN} = " "
RDEPENDS:${PN} +=  " rdk-halif-aidl-indicator-v0-1-0-0"

# ... other recipe content
```

### CMake

This example is taken and simplified from
[`rdk-e/indicator-polarishal-soc-broadcom`](https://github.com/rdk-e/indicator-polarishal-soc-broadcom/compare/feature/SERXIONE-8671...feature/use-new-rdk-halif-aidl)
and shows how to consume the `RdkHalifAidlIndicator` interface, version `0.1.0.0`.

```cmake
cmake_minimum_required(VERSION 3.16)
project(indicator-hal-bcm-soc LANGUAGES CXX)

# ...

find_package(RdkHalifAidlIndicator 0.1.0.0 EXACT REQUIRED CONFIG)

# ...

target_link_libraries(indicator-hal-service PRIVATE
    # Android Base for logging
    base
    # Polaris HAL interface library (pre-built from rdk-halif-aidl)
    RdkHalifAidl::Indicator-v0.1.0.0
    # System
    pthread
)
```

### Make

This example shows how to consume the packaged artefacts from a Makefile.

```make
CFLAGS += $(shell pkg-config --cflags rdk-halif-aidl-indicator-0.1.0.0)
LDFLAGS += $(shell pkg-config --libs rdk-halif-aidl-indicator-0.1.0.0)
```

### Other Build Systems

Tools that call `build_modules.sh` directly, such as
[`rdkcentral/rdk-halif-aidl-unified-vts`](https://github.com/rdkcentral/rdk-halif-aidl-unified-vts), need no changes.
We encourage them, though, to switch to a CMake-based (or at least `pkg-config`-based) build instead of relying on
hard-coded paths.

## Developer Workflows and Usecases

### Adoption of a New HAL Interface or a New Version of an Existing Interface

- **New interfaces**: Simply add the interface entry to the release baseline YAML. Since this is a pure addition, existing code builds without problems.
- **New versions of existing interfaces (middleware)**: Append the new version to the release baseline YAML while keeping the old one. This allows consumers to adopt the new version while still supporting the existing one.
- **New versions of existing interfaces (vendor layer)**: The vendor can adopt the new version by updating the Yocto variable `HALIF_AIDL_INTERFACE_VERSION_APPENDS` in `local.conf`, while keeping the old version for compatibility. Use this approach for vendor layers because they move from one baseline to another atomically.

### Trying Interface Changes Before Commiting

- To test interface changes before committing, modify the interface definition locally or on a branch and include `current` in `HALIF_AIDL_INTERFACE_VERSION_APPENDS` for your interface.
- When consuming the interface, make sure to use `current` as the version in CMake or pkg-config.
- This approach lets you test changes in your local environment without affecting mainline development or other consumers.


## Notes

In CMake, `SameMinorVersion` can be used instead of `EXACT` to allow for patch version updates. Note, however, that in
our current context `SameMinorVersion` behaves like `SameMajorVersion`, because we prepend a leading `0` to the version
numbers.

## References

- [`meta-binder PR`](https://github.com/rdkcentral/meta-binder/pull/24)
