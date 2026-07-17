# Real bitbake packaging test

Everything under `tests/yocto/ci/` emulates the build *offline* - it proves the
components compile and stage, but it cannot see BitBake packaging (`do_install`,
`do_package`, the `PACKAGES`/`FILES` split, `-dbg`). Packaging bugs therefore
reached integrators instead of us.

`run.sh` closes that gap: it runs **real bitbake** on the `rdk-halif-aidl` recipe
in a container and **asserts the packaging is correct**. It already earned its
keep - it found that the per-component `-dbg` split did not work (OE puts every
`.debug` file in the first `-dbg` package, so 20 shipped empty), which is fixed
now to a single `rdk-halif-aidl-dbg`.

## Run it

```bash
./tests/yocto/bitbake/run.sh
```

The first run builds a cross toolchain from source (~an hour); every run after is
cached (minutes). Options:

| Env | Effect |
| --- | ------ |
| `HALIF_BB_CLEAN=1`   | force a clean re-fetch + rebuild of the recipe |
| `HALIF_TEST_BRANCH=` | test a different branch (default: the #661 branch) |
| `HALIF_BB_WORK=`     | put the (large) build tree somewhere else |

## Prerequisites

- **docker**
- the **Binder SDK built** (`./build_binder.sh` -> `out/`) - the stub recipe
  stages it so we do not have to reproduce the whole RDK layer stack
- **`fs.inotify.max_user_instances` >= 512** - a standard Yocto requirement;
  bitbake's parser fails without it. `run.sh` raises it if it can (passwordless
  sudo), otherwise it prints the one command to run. Persist it in
  `/etc/sysctl.d/`.

## What it asserts

After a green `do_package`, on the produced `packages-split/`:

1. one **`rdk-halif-aidl-<comp>`** per component, each holding exactly its own
   `lib<comp>-v<ver>-cpp.so` on the role mount (`/vendor/rdk-halif-aidl/` etc.)
2. a matching **`rdk-halif-aidl-<comp>-dev`** holding that component's headers
3. exactly one **`rdk-halif-aidl-dbg`**, holding every component's debug library
   (no empty `-dbg` packages)

## How it is wired

```
tests/yocto/bitbake/
├── run.sh                 the test: docker + poky + bitbake + assertions
└── meta-halif-ci/         a minimal layer that only exists for CI
    ├── conf/layer.conf
    ├── recipes-binder/linux-binder/       stub: stages the prebuilt Binder SDK
    │                                       so the recipe's DEPENDS resolves
    └── recipes-halif/rdk-halif-aidl/
        └── rdk-halif-aidl.bbappend         fetches the branch under test
```

The recipe itself lives in the consumable layer `tests/yocto/meta-rdk-halif-aidl/`
and is fetched from git (not `externalsrc` - that broke fakeroot for `do_package`
and hashed the in-repo build tree). To test a local commit, push it and point
`HALIF_TEST_BRANCH`/the bbappend `SRCREV` at it.

`.work/` (poky, the build tree, downloads, sstate) is git-ignored.
