# RDK AIDL HAL Interface Versioning

## 1. Introduction

This document is a **technical specification** for the RDK AIDL HAL interface versioning mechanism. It defines normative requirements—metadata formats, hash algorithms, runtime behaviors, and testing obligations—that implementers must follow to ensure safe, compatible evolution of AIDL interfaces.

## 2. Versioning Metadata Versioning Metadata

Each AIDL interface carries two metadata fields embedded in the generated stub classes:

- **Version Number** (`int INTERFACE_VERSION`)
    - Incremented **every time** the AIDL file is modified (method added/removed/renamed, annotation changed).
    - Exposed at runtime as a constant field.

- **Interface Hash** (`String INTERFACE_HASH`)
    - SHA‑256 digest computed over the **canonical form** of the AIDL (see Section 3).
    - Ignores formatting/comments so that only signature changes affect the hash.

### Freeze Version vs. Current Version

- **Freeze Version**: the highest version number recorded in `hal/docs/golden_hashes.json`; represents the last published interface state.
- **Current Version**: the value in `INTERFACE_VERSION` in the AIDL file under development.
- **Increment Timing**: when modifying an AIDL file, the developer must:
    - Bump `INTERFACE_VERSION` to `FreezeVersion + 1`.
    - Recompute and publish the new `INTERFACE_HASH`.
    - Update `golden_hashes.json` accordingly.

Both values ensure that any new change starts from a known, immutable baseline and that the code version aligns with the published snapshot.

## 3. Hash Generation Process

- **Canonicalization**: Strip comments, normalize whitespace, and sort methods lexicographically by signature.
- **Serialization**: Concatenate each method signature (return type + name + parameter types) separated by newline.
- **Hashing**: Compute SHA‑256 over the serialized string. Output as lowercase hex.
- **Golden Hash Table**:
    - File: `hal/docs/golden_hashes.json`
    - Format:
      ```json
      {
        "1": "a1b2c3...",
        "2": "d4e5f6...",
        "3": "4f8e5c..."
      }
      ```

- **Automation Script**:
    - Command: `scripts/gen_hash.py --input path/to/MyInterface.aidl --output hal/docs/golden_hashes.json`
    - On execution, it computes the new hash for the declared version and updates the table.

## 4. Runtime Negotiation Protocol

Before any AIDL calls, client and server perform a handshake to ensure version alignment:

- **Client → Server**:

    ```cpp
    // Client-side handshake using generated stub
    auto stub = IMyInterface::getService();
    VersionCheckRequest req;
    req.interfaceName = "com.rdk.hal.IMyInterface";
    req.version = INTERFACE_VERSION;
    req.hash = INTERFACE_HASH;

    Status<void> result = stub->versionCheck(req);
    if (result.code != OK) 
    {
        // handle version mismatch or incompatibility
    }
    ```

- **Server Validation**:

    ```cpp
    // **Lookup expected values** from the golden hash table:
    int expectedVersion = lookupVersion(interfaceName);
    std::string expectedHash = goldenHashes.at(expectedVersion);
    // **Compare client version**:
    if (clientVersion != expectedVersion) 
    {
        // Client and server versions differ
        return Status<ReturnType>(ERROR_UNKNOWN_TRANSITION, {});
    }
    // **Verify interface hash**:
    if (clientHash != expectedHash) 
    {
        // Signature change detected
        return Status<ReturnType>(ERROR_UNKNOWN_TRANSITION, {});
    }
    // **Check minimum supported version** (for deprecation scenarios):
    int minSupported = minimumSupportedVersion(interfaceName);
    if (clientVersion < minSupported) 
    {
        return Status<ReturnType>(ERROR_INCOMPATIBLE_VERSION, {});
    }
    ```

- **On success**: `OK`, proceed to bind the interface and invoke methods.
- **Error Codes**:
    - `ERROR_UNKNOWN_TRANSITION`: version or hash mismatch.
    - `ERROR_INCOMPATIBLE_VERSION`: clientVersion < minimumSupportedVersion (for deprecation scenarios).

## 5. Return-Value Wrapper

In the generated C++ bindings, each interface method returns a `Status<T>` struct to encapsulate both the result payload and an error code.

```cpp
// Common status wrapper generated in C++
template<typename T>
struct Status 
{
    int code;       // OK (0), ERROR_UNKNOWN_TRANSITION (1), ERROR_INCOMPATIBLE_VERSION (2), etc.
    T payload;      // Actual return value; empty for void methods
};

// Example generated C++ interface
class IExample : public android::RefBase 
{
public:
    // Returns Foo on success or error code on failure
    virtual Status<Foo> getFoo(int id) = 0;

    // For void methods, payload is unused
    virtual Status<void> updateBar(const Bar& bar) = 0;
};
```

- **`code`**: one of `OK (0)`, `ERROR_UNKNOWN_TRANSITION (1)`, `ERROR_INCOMPATIBLE_VERSION (2)`, or custom.
- **`payload`**: the original return type, or `null` if `code` ≠ `OK`.

## 6. Bidirectional Compatibility

RDK AIDL HAL supports:

| Scenario                  | Behavior                                            |
|---------------------------|-----------------------------------------------------|
| `clientVersion > server`  | Missing methods → `ERROR_UNKNOWN_TRANSITION`.       |
| `clientVersion < server`  | Unknown client calls → default handling or `ERROR_INCOMPATIBLE_VERSION` if deprecated. |
| `hash mismatch`           | Always `ERROR_UNKNOWN_TRANSITION`.                  |

This flexibility lets either side lead or lag without hard ordering.

## 7. Testing & Validation Strategy

All AIDL changes **must** be verified locally **before** opening a pull request:

- **Hash Verification**:
    ```bash
    ./scripts/gen_hash.py --verify
    ```

    - Verifies that `INTERFACE_HASH` matches the entry in `golden_hashes.json` for the declared version.

- **Compatibility Regression Suite**:
    ```bash
    ./scripts/run_compat_tests.sh
    ```

- **Simulates**:
    - Older client vs. newer server
    - Newer client vs. older server
    - Exact-version match
    - Reports pass/fail per method.

- **Pull Request Validation**:
    - When creating a PR, attach logs from both scripts demonstrating successful verification and compatibility checks.
    - The PR reviewer will ensure these results are present and all tests pass before merging.

## 8. Developer Guidelines

### **When modifying AIDL**

1. Determine `FreezeVersion` from `golden_hashes.json`.
2. Increment `INTERFACE_VERSION` to `FreezeVersion + 1`.
3. Run hash generation script to update `golden_hashes.json`.
4. Execute both verification scripts and include results in your PR.

### **Removing or renaming methods**

- Always treat as breaking change—increment version.
- Ensure client gracefully handles missing methods via error codes.

### **Review Checklist**

- [ ] Version incremented correctly.
- [ ] `golden_hashes.json` updated and verified.
- [ ] All local tests pass (hash + compatibility).
- [ ] Return‑Value wrapper usage remains consistent.
- [ ] PR contains verification logs.