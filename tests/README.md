# Tests

On-demand build verification for the module-local layout.

| Concern | Where |
| ------- | ----- |
| Does the system build? | `./test.sh` — the top-level suite: build paths, direct-CMake, cross-compile, and `yocto/` (Test 12) |
| Module build smoke | `tests/smoke/` — the `build_modules.sh` paths in depth (standalone) |
| Yocto build integration | `tests/yocto/` — run by `test.sh` Test 12, also standalone |
| Is a release's structure OK? | `./scripts/release.sh` — link-check, no-untracked-generated-files, and a clean-checkout verification build |

## `smoke/`

Module-local **build** smoke test — exercises the `build_modules.sh` build paths
and asserts the produced HAL libraries:

```bash
./tests/smoke/smoke_test.sh
```

| Command | Assertion |
| ------- | --------- |
| `./build_modules.sh all --clean` | one `lib<module>-vcurrent-cpp.so` per `*/current/` component |
| `./build_modules.sh manifest` | the released cohort from `versions_released.yaml` |
| `./build_modules.sh manifest --file versions_current.yaml` | the dev cohort, every component at `current/` |
| `./build_modules.sh <c> --version <v>` | builds `lib<c>-v<v>-cpp.so` for a committed release snapshot |
| the same build with `<c>`'s dependency snapshots deleted first | the standalone snapshot build auto-resolves the dependency closure ([#638](https://github.com/rdkcentral/rdk-halif-aidl/issues/638)) |

Exit status is `0` only if every check passes. The Binder SDK is staged
automatically by `build_modules.sh` if missing.

## `yocto/`

Emulates the Yocto/BitBake **build** integration **without** a real BitBake, so
the production per-component CMake path is exercised offline.

**Builds** (examples an integrator can run):

- **`yocto_build_vendor.sh`** / **`yocto_build_mw.sh`** — build the **full** HAL
  for the vendor / MW role, from a versions manifest passed in (default: the
  repo's `versions_released.yaml`), installed to the role's destination. Thin
  wrappers over **`yocto_build.sh <role> [manifest]`**.

**Test:**

- **`yocto_staging_check.sh`** — builds `hdmicec → common` from the self-contained
  `<module>/<version>/CMakeLists.txt`, with a negative control proving the
  inter-module dependency staging is required (the regression from #661).

The consumable BitBake reference layer is `yocto/meta-rdk-halif/` (see
`docs/standards/build_integration.md`); the scripts above exercise the contract
its `rdk-halif` recipe implements.
