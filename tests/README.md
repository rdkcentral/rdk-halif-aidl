# Tests

On-demand build verification for the module-local layout (#493). Nothing here
is wired into CI — run it by hand.

## `smoke_test.sh`

Exercises the three build paths the module-local restructure added and asserts
the produced HAL libraries:

```bash
./tests/smoke_test.sh
```

| Step | Command | Assertion |
| ---- | ------- | --------- |
| 1 | `./build_modules.sh all --clean` | one `lib<module>-vcurrent-cpp.so` per `*/current/` component |
| 2 | `./build_modules.sh manifest` | same set, built from `versions.yaml` |
| 3 | `./build_modules.sh <c> --version <v>` | `lib<c>-v<v>-cpp.so` for the first committed release snapshot |

Exit status is `0` only if every check passes. The Binder SDK is staged
automatically by `build_modules.sh` if missing.

## `fake-yocto/`

Emulates a Yocto/BitBake build **without** a real BitBake, so the production
CMake path can be smoke-tested offline:

```bash
./tests/fake-yocto/run-fake-yocto.sh [--keep]
```

It reproduces, in a throwaway work directory, what the recipes would do:

- **`linux-binder` recipe** — builds the Binder SDK and stages it into a
  sysroot in the **flat** layout a Yocto consumer sees
  (`<sysroot>/usr/{include/binder_sdk,lib/binder}`).
- **`rdk-halif-aidl` recipe** — runs `do_configure` / `do_compile` /
  `do_install` against that staged sysroot and asserts the HAL libraries land
  in the image (`<image>/usr/lib/halif/`).

This is the path a plain `./build_modules.sh` run never touches: the flat SDK
layout (vs the local dev split of `out/build` headers and `out/target` libs)
and the `cmake --install` step. `--keep` preserves the work directory for
inspection.

- [`hal-aidl.bb.sample`](fake-yocto/hal-aidl.bb.sample) — the reference
  BitBake recipe whose tasks `run-fake-yocto.sh` emulates. Copy it into a
  layer and pin `SRCREV` to use it for real.
