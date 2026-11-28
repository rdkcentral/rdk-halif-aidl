# Tests

On-demand build verification for the root-CMake interface build.

| Concern | Where |
| ------- | ----- |
| Does the system build? | `./tests/test.sh` — the top-level suite: build paths, direct-CMake, and cross-compile |
| Module build smoke | `tests/smoke/` — the `build_modules.sh` paths in depth (standalone) |
| Is a release's structure OK? | `./scripts/release.sh` — link-check, no-untracked-generated-files, and a clean-checkout verification build |

Yocto packaging and consumption are documented in
[`docs/standards/yocto_integration.md`](../docs/standards/yocto_integration.md).

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
