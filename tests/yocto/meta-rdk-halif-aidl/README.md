# meta-rdk-halif-aidl

A **reference** Yocto layer for the RDK HAL AIDL interface libraries, exercised
by this repo's CI (`test.sh` Test 12). A single `rdk-halif-aidl` recipe builds a
chosen set of components from their committed, pre-generated C++ — **no AIDL /
codegen toolchain** required — and splits the output into one package per
component (`rdk-halif-aidl-<comp>`).

The integration team owns its production recipe. This layer is here to (a) prove
the build contract works end to end and (b) be something to **use as-is or copy
and adapt** — see `docs/standards/build_integration.md` for the contract your own
recipe must honour.

## Use (or copy)

Add the layer to `BBLAYERS` and install the components you need:

```bitbake
BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-rdk-halif-aidl"
IMAGE_INSTALL:append = " rdk-halif-aidl-common rdk-halif-aidl-avclock"
```

The Binder SDK is provided by the `linux-binder` recipe (from `linux_binder_idl`).
Pin `SRCREV` in `recipes-halif/rdk-halif-aidl/rdk-halif-aidl.bb` to the released
tag's commit for reproducible builds.

## One recipe, driven by variables

The recipe builds the components in **`HALIF_COMPONENTS`** (default: every
released component, from the generated `halif-components.inc`). You name only the
components you want; their dependency closure is resolved automatically, so
`common` is never listed by hand, and different versions of one dependency
coexist in a single build. **`HALIF_VERSIONS_FILE`** pins the top-level versions.
It resolves the build order with `halif_plan.py`, stages each component's lib +
headers for its dependents, and installs to `HALIF_LIBDIR` / `HALIF_INCDIR`
(overridable), rooted at the mount point `HALIF_MOUNT_POINT` (`/vendor` | `/mw`).

The sibling **`meta-vendor`** and **`meta-mw`** example layers both build the full
HAL at latest, differing only by mount point; the versions manifest defaults to
the released cohort (`versions_released.yaml`).

## Layout

| Path | Purpose |
| ---- | ------- |
| `conf/layer.conf` | Layer definition |
| `recipes-halif/rdk-halif-aidl/rdk-halif-aidl.bb` | The recipe: build loop + per-component `PACKAGES` split |
| `recipes-halif/rdk-halif-aidl/halif-components.inc` | Generated default `HALIF_COMPONENTS` (full) list |
| `halif_plan.py` | Resolves the build order + dependency closure |
| `gen_recipes.py` | Regenerates `halif-components.inc` |

## The one generated file — do not hand-edit

`halif-components.inc` is the default component list, generated from the snapshots
by `gen_recipes.py` (the per-config version manifests are hand-written and
consumed directly):

```bash
./tests/yocto/meta-rdk-halif-aidl/gen_recipes.py            # regenerate the component list
./tests/yocto/meta-rdk-halif-aidl/gen_recipes.py --check    # CI guard: fail if it is stale
```

The build contract is exercised offline, without BitBake, by
`tests/yocto/ci/yocto_staging_check.sh` (per-component staging) and
`tests/yocto/ci/yocto_build_vendor.sh` / `yocto_build_mw.sh` (full-HAL example
builds), and with real BitBake by `tests/yocto/bitbake/run.sh`. See
`docs/standards/build_integration.md` for the full integration contract.
