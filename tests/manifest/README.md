# Manifest-driven build tests

`test_plan.sh` — inputs → plan. Configure-only; needs no Binder SDK or aidl.
Every case names its inputs (`HALIF_VERSIONS_FILE`, `HALIF_COMPONENTS`, the
legacy `INTERFACE_TARGET`) and the exact `(component, version)` plan they must
produce, checks dependency order, and cross-checks three plans against
develop's `tests/yocto/meta-rdk-halif-aidl/halif_plan.py`.

`test_install.sh` — build → install → consume. Needs the Binder SDK
(`./build_binder.sh`, or `BINDER_SDK_DIR` / `BINDER_SDK_INCLUDE_DIR` at a staged
sysroot). Installs the `two-commons` fixture, asserts every installed path
carries its version, and links `consumer/` through `find_package(CONFIG)`,
`pkg-config`, and an EXACT selection of two versions of `common` from one prefix.

```sh
./tests/manifest/test_plan.sh
./tests/manifest/test_install.sh
```
