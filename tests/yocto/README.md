# Yocto integration

Everything an integrator needs to build and consume the RDK HAL AIDL interface
libraries — plus the offline tests that prove the contract works.

**Named `-aidl` throughout** (layer, recipe, packages, install paths) so nothing
here is ever confused with the legacy C HAL (`rdk-halif-*`) it coexists with
during migration.

## What is what

| Path | Yours to use? | Purpose |
| ---- | ------------- | ------- |
| `meta-rdk-halif-aidl/` | **yes** | the consumable layer — one `rdk-halif-aidl` recipe, one package per component |
| `meta-vendor/`, `meta-mw/` | **as examples** | role build-config + a worked consumer recipe each |
| `ci/` | **no** | our offline test harness. It emulates the recipe without BitBake so CI can prove the contract. Not consumption material. |

## Consume it

Add the layer and install the components you need:

```bitbake
BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-rdk-halif-aidl"
IMAGE_INSTALL:append = " rdk-halif-aidl-common rdk-halif-aidl-avclock"
```

The Binder SDK comes from the `linux-binder` recipe (`linux_binder_idl`). Pin
`SRCREV` in `meta-rdk-halif-aidl/recipes-halif/rdk-halif-aidl/rdk-halif-aidl.bb`
to a released tag for reproducible builds.

## What you get

One package per component, plus its headers:

```
${libdir}/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so            → rdk-halif-aidl-<comp>
${includedir}/rdk-halif-aidl/<comp>/<ver>/include/com/rdk/hal/...
                                                            → rdk-halif-aidl-<comp>-dev
```

Concretely, for `hdmicec@0.1.0.0` (which imports `common@0.2.0.0`):

```
${libdir}/rdk-halif-aidl/libhdmicec-v0.1.0.0-cpp.so
${libdir}/rdk-halif-aidl/libcommon-v0.2.0.0-cpp.so
${includedir}/rdk-halif-aidl/hdmicec/0.1.0.0/include/com/rdk/hal/hdmicec/IHdmiCec.h
${includedir}/rdk-halif-aidl/common/0.2.0.0/include/com/rdk/hal/...
```

**Why the version appears where it does:** it is in the library *name* (and its
`SONAME`), so libraries for several versions sit side by side in one flat
directory and you link an exact one. Headers have no version in the filename —
`BnPropertyValue.h` is the same name in every version — so for headers the
version lives in the *path*.

## Consuming from your recipe

```bitbake
DEPENDS        = "rdk-halif-aidl linux-binder"      # stages libs + headers
RDEPENDS:${PN} = "rdk-halif-aidl-hdmicec rdk-halif-aidl-common"

CXXFLAGS += "-I${STAGING_INCDIR}/rdk-halif-aidl/hdmicec/0.1.0.0/include"
LDFLAGS  += "-L${STAGING_LIBDIR}/rdk-halif-aidl -lhdmicec-v0.1.0.0-cpp -lbinder -lutils"
```

then include by the AIDL namespace:

```cpp
#include <com/rdk/hal/hdmicec/IHdmiCec.h>
```

Link the same versions the `rdk-halif-aidl` recipe built (its
`HALIF_VERSIONS_FILE`) — the `.so` you link must be the one on the rootfs.

Worked examples, which you can copy the shape of:

- `meta-vendor/recipes-example/vendor-halif-example/` — **server**: subclass the
  generated `Bn<Interface>` stub and register the service
- `meta-mw/recipes-example/mw-halif-example/` — **client**: look the service up
  and gate newer calls on `getInterfaceVersion()`

Client and server link the *same* interface library; the role difference is what
the code does, not how it builds.

## Choosing what gets built

The recipe builds `HALIF_COMPONENTS` at the versions in `HALIF_VERSIONS_FILE`:

| Variable | Default | Meaning |
| -------- | ------- | ------- |
| `HALIF_COMPONENTS` | every released component (`halif-components.inc`) | which components to build |
| `HALIF_VERSIONS_FILE` | `${S}/versions_released.yaml` | which version of each |
| `HALIF_ROLE` | `vendor` | labels who is building (`vendor` \| `mw`) |
| `HALIF_LIBDIR` / `HALIF_INCDIR` | `${libdir}/rdk-halif-aidl` etc. | install destinations |

Every version of every component is committed side by side in the source, so
`HALIF_VERSIONS_FILE` *selects* — it does not fetch. See `meta-vendor/conf/halif-vendor.inc`
and `meta-mw/conf/halif-mw.inc` for role configs to `require` from your
`local.conf`/distro.

Relocating the libraries needs no snapshot edits — each snapshot's install
destination is an overridable input:

```bash
cmake -S <comp>/<ver> -B <build> -DHALIF_INSTALL_LIBDIR=lib64/rdk-halif-aidl
```

## Running the tests (`ci/`)

Offline — no BitBake, no AIDL toolchain. Each uses a fresh temporary work dir.

```bash
./tests/yocto/ci/yocto_staging_check.sh    # inter-module staging + negative control
./tests/yocto/ci/yocto_build_each.sh       # every component built individually
./tests/yocto/ci/yocto_build_vendor.sh     # full HAL, vendor role
./tests/yocto/ci/yocto_build_mw.sh         # full HAL, MW role
```

`test.sh` Test 12 runs the component-list check, the staging check and both role
builds; Test 13 runs the per-component build.

The default component list is generated — never hand-edit it:

```bash
./tests/yocto/meta-rdk-halif-aidl/gen_recipes.py           # regenerate
./tests/yocto/meta-rdk-halif-aidl/gen_recipes.py --check   # CI guard
```

See [`docs/standards/build_integration.md`](../../docs/standards/build_integration.md)
for the full integration contract.
