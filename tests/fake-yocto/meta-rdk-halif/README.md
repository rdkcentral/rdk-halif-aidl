# meta-rdk-halif

A **reference** Yocto layer for the RDK HAL AIDL interface libraries, generated
from `interface.yaml` and exercised by this repo's CI (`test.sh` Test 12). Each
released snapshot under `<component>/<version>/` is available as
`rdk-halif-<component>`, built from its self-contained CMakeLists — the
committed, pre-generated C++, with **no AIDL toolchain or Python** on the build
host.

The integration team owns its production recipes. This layer is here to (a) prove
the per-component build contract works end to end and (b) give you something to
**use as-is or copy and adapt** — see `docs/standards/build_integration.md` for
the contract your own recipes must honour.

## Use (or copy)

Add the layer to `BBLAYERS`:

```bitbake
BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/meta-rdk-halif"
```

Install the components you need; inter-component dependencies are pulled in
automatically:

```bitbake
IMAGE_INSTALL:append = " rdk-halif-hdmicec"    # brings in rdk-halif-common
```

The Binder SDK is provided by the `linux-binder` recipe (from `linux_binder_idl`);
every HAL recipe `DEPENDS` on it. Pin `SRCREV` to the released tag's commit in
`classes/rdk-halif-module.bbclass` for reproducible builds.

## Layout

| Path | Purpose |
| ---- | ------- |
| `conf/layer.conf` | Layer definition |
| `classes/rdk-halif-module.bbclass` | Shared build: per-component CMake, lib + header staging |
| `recipes-halif/rdk-halif-<comp>/rdk-halif-<comp>_<ver>.bb` | Generated recipe, one per component (latest released version) |

## Generated — do not hand-edit recipes

The recipes are generated from each snapshot's `interface.yaml` by
`../scripts/gen_recipes.py`. A recipe's `DEPENDS` comes from that snapshot's
`imports:` — the dependency graph lives in `interface.yaml`, not in the `.bb`.
Regenerate after adding or bumping a snapshot:

```bash
./scripts/gen_recipes.py            # regenerate
./scripts/gen_recipes.py --check    # CI guard: fail if recipes are stale
```

The build contract these recipes implement is exercised offline, without
BitBake, by `tests/fake-yocto/run-fake-yocto-per-component.sh`.

See `docs/standards/build_integration.md` for the full integration contract.
