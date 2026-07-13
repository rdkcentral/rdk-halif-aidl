# meta-rdk-halif

A **reference** Yocto layer for the RDK HAL AIDL interface libraries, exercised
by this repo's CI (`test.sh` Test 12). A single `rdk-halif` recipe builds a chosen
set of components from their committed, pre-generated C++ — **no AIDL toolchain
or Python** on the build host — and splits the output into one package per
component (`rdk-halif-<comp>`).

The integration team owns its production recipe. This layer is here to (a) prove
the build contract works end to end and (b) be something to **use as-is or copy
and adapt** — see `docs/standards/build_integration.md` for the contract your own
recipe must honour.

## Use (or copy)

Add the layer to `BBLAYERS` and install the components you need:

```bitbake
BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-rdk-halif"
IMAGE_INSTALL:append = " rdk-halif-common rdk-halif-avclock"
```

The Binder SDK is provided by the `linux-binder` recipe (from `linux_binder_idl`).
Pin `SRCREV` in `recipes-halif/rdk-halif/rdk-halif.bb` to the released tag's
commit for reproducible builds.

## One recipe, driven by variables

The recipe builds the components in **`HALIF_COMPONENTS`** (default: every
released component, from the generated `halif-components.inc`), each at
**`HALIF_VERSION_<comp>`** (default: the latest snapshot). It resolves the build
order with `scripts/halif_plan.py`, stages each component's lib + headers for its
dependents, and installs to `HALIF_LIBDIR` / `HALIF_INCDIR` (overridable), tagged
by `HALIF_ROLE` (`vendor` | `mw`).

A build configuration selects a subset + versions through a generated include;
the sibling **`meta-vendor`** and **`meta-mw`** example layers pin divergent
cohorts (0.2.x vs 0.1.x) via `versions_<team>.yaml` + `scripts/gen_team_conf.py`,
from the *same* recipe.

## Layout

| Path | Purpose |
| ---- | ------- |
| `conf/layer.conf` | Layer definition |
| `recipes-halif/rdk-halif/rdk-halif.bb` | The recipe: build loop + per-component `PACKAGES` split |
| `recipes-halif/rdk-halif/halif-components.inc` | Generated default `HALIF_COMPONENTS` list |

## Generated bits — do not hand-edit

- `halif-components.inc` — the default component list, from `scripts/gen_recipes.py`.
- `../meta-vendor/conf/halif-vendor.inc`, `../meta-mw/conf/halif-mw.inc` — the
  per-config includes, from `scripts/gen_team_conf.py`.

```bash
./scripts/gen_recipes.py            # regenerate the component list
./scripts/gen_recipes.py --check    # CI guard: fail if it is stale
```

The build contract is exercised offline, without BitBake, by
`tests/yocto/run-yocto-per-component.sh` (per-component staging) and
`tests/yocto/run-yocto-roles.sh` (vendor/MW version divergence). See
`docs/standards/build_integration.md` for the full integration contract.
