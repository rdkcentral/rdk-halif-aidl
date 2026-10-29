# common — retired

`common` (package `com.rdk.hal`) is not a component of the in-development
release and takes no new types. Every HAL defines the types it uses in its own
package (`com.rdk.hal.<module>`), including where two HALs hold the same shape.

A shared package couples every importer's version to it: a change here
re-releases every HAL that imports it, whether or not that HAL's contract moved.

## What remains

| Path | Status |
|---|---|
| `0.1.0.0/`, `0.2.0.0/`, `0.3.0.0/` | Frozen. Released snapshots of other HALs import them and must keep building, so they are never edited. |
| `current/` | Removed. `PropertyValue`, `AVSource` and `OperationalMode` live in each consuming module's own package. |
| `halcompat.h` | Moved to the `halcompat` component (`halcompat/current/halcompat.h`). |

## Removal

The `common/` directory is deleted when no frozen version of any interface
imports any version of `common`. This lists the snapshots still holding it:

```bash
grep -l -E '^\s+- common@' */[0-9]*/interface.yaml | grep -v '^common/'
```

Tracking: [#869](https://github.com/rdkcentral/rdk-halif-aidl/issues/869).
