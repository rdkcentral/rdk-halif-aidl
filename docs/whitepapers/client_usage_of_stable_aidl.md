# **WhitePaper: Client Usage of Stable AIDL with Versioning & Fallback**

- **Type:** Engineering Whitepaper
- **Audience:** Developers integrating and maintaining C++ client code that interacts with Stable AIDL-generated interfaces.  
- **Purpose:** Define a consistent client-side approach for version discovery, capability management, and fallback when new features are introduced in Stable AIDL interfaces.

---

## 1. Overview

Stable AIDL interfaces evolve over time—new APIs, new capabilities, updated features.
Stable AIDL enforces constraints that *enable* compatibility across versions, but the **client** must still detect and adapt to what the connected service actually supports at runtime.

This paper defines the client engineering standard for version handling and runtime adaptation when using Stable AIDL-generated C++ interfaces (as produced by Google’s AIDL compiler).
The patterns and examples align with the interface style used in this repository and are intended to avoid version checks and feature flags being scattered throughout the codebase.

---

## 2. Key Design Goals

1. **Additive evolution** – new functions are added, never replacing or removing old ones.
2. **Self-contained headers** – each generated interface (e.g., `IFoo.h`) includes all required functionality and AIDL plumbing.
3. **Capability awareness** – clients should discover what’s available and adapt accordingly.
4. **Consistent error semantics** – handle unknown transactions and unsupported operations explicitly.
5. **Centralised logic** – version and feature handling belongs in a thin adapter, not scattered across the codebase.  
   All other code should go through this adapter, not call `getInterfaceVersion()` or `getInterfaceHash()` directly.

---

## 3. Interface Example

### Version 1 (V1)

```aidl
package com.example;
interface IFoo {
    int functionA(int x);
}
```

### Version 2 (V2 – additive)

```aidl
package com.example;
interface IFoo {
    int functionA(int x);   // existing function
    int functionB(int y);   // new optional feature
}
```

The generated `IFoo.h` contains everything required — function definitions, interface version accessors, hash accessors, and binder transaction IDs.

---

## 4. Client Design Pattern

### Objectives

- Probe version/hash once per connection.
- Cache capabilities.
- Provide clear optional feature accessors (e.g., `supportsFunctionB()`).
- Handle runtime errors gracefully and clearly.
- Re-probe capabilities after reconnecting (e.g., after binder death).

### Example: `FooClient`

```cpp
#include "IFoo.h"   // All AIDL-generated content for IFoo lives here
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <iostream>

class FooClient {
public:
    static std::shared_ptr<FooClient> Connect(const char* serviceName = "com.example.IFoo/default") 
    {
        auto binder = AServiceManager_waitForService(serviceName);
        if (!binder) return nullptr;

        auto remote = IFoo::fromBinder(binder);
        if (!remote) return nullptr;

        return std::shared_ptr<FooClient>(new FooClient(remote));
    }

    // ---- Capability Info ----
    int32_t interfaceVersion() const { return mVersion; }
    const std::string& interfaceHash() const { return mHash; }
    bool supportsFunctionB() const { return mVersion >= 2; }

    // ---- V1 API ----
    int functionA(int x) {
        int out = 0;
        auto st = mRemote->functionA(x, &out);
        if (!st.isOk()) 
        {
            throw std::runtime_error(st.getDescription());
        }
        return out;
    }

    // ---- V2 optional API ----
    // Returns std::nullopt if functionB is not usable on this connection:
    // - either the method is missing on the server
    // - or the feature is currently disabled/unavailable
    std::optional<int> tryFunctionB(int y) 
    {
        // Version gate to avoid known-failing calls on older servers
        if (!supportsFunctionB()) return std::nullopt;

        int out = 0;
        auto st = mRemote->functionB(y, &out);

        if (st.isOk()) return out;

        // Method genuinely missing on the remote side
        if (st.getStatus() == STATUS_UNKNOWN_TRANSACTION ||
            // Method exists but the feature is currently disabled/unavailable
            st.getExceptionCode() == EX_UNSUPPORTED_OPERATION) {
            return std::nullopt;
        }

        // Any other binder failure is treated as a real error
        throw std::runtime_error(st.getDescription());
    }

private:
    explicit FooClient(std::shared_ptr<IFoo> remote)
        : mRemote(std::move(remote)) {
        int32_t v = 1;
        std::string h;

        // We treat version 1 as the minimum supported version for IFoo.
        // If the server cannot report its version, we default to v=1.
        if (!mRemote->getInterfaceVersion(&v).isOk()) v = 1;
        if (!mRemote->getInterfaceHash(&h).isOk()) h = "unknown";

        mVersion = v;
        mHash = std::move(h);

        std::cout << "Connected to IFoo v" << mVersion
                  << " (hash=" << mHash << ")" << std::endl;
    }

    std::shared_ptr<IFoo> mRemote;
    int32_t mVersion = 1;
    std::string mHash = "unknown";
};
```

### Usage

```cpp
auto client = FooClient::Connect();
if (!client) throw std::runtime_error("Failed to connect to IFoo service");

int resultA = client->functionA(10);

if (auto resultB = client->tryFunctionB(20)) {
    std::cout << "functionB result: " << *resultB << std::endl;
} else {
    std::cout << "functionB not supported or not available on this implementation"
              << std::endl;
}
```

The important rule is: **all** consumers call `supportsFunctionB()` and `tryFunctionB()` on `FooClient`; nobody else performs their own version/hash checks.

---

## 5. Error Handling Semantics

Client behaviour is driven by binder status and exception codes:

| Scenario                           | Detection in client code                                 | Client Response                  |
| ---------------------------------- | -------------------------------------------------------- | -------------------------------- |
| Method missing (older server)      | `st.getStatus() == STATUS_UNKNOWN_TRANSACTION`           | Treat as not supported           |
| Method exists but feature disabled | `st.getExceptionCode() == EX_UNSUPPORTED_OPERATION`      | Treat as temporarily unavailable |
| Any other binder failure           | `!st.isOk()` and neither of the above conditions matches | Raise runtime error              |

This mapping is implemented in `tryFunctionB()`:

* `STATUS_UNKNOWN_TRANSACTION` ⇒ method doesn’t exist on the server implementation.
* `EX_UNSUPPORTED_OPERATION` ⇒ method exists, but the feature is currently disabled or otherwise unavailable.
* Any other failure ⇒ treated as a real error, propagated as an exception.

---

## 6. Lifecycle & Version Refresh

* **Re-probe after binder death or reconnect.**
  When the underlying binder dies (e.g., via `linkToDeath` callbacks), the client should:

  1. Reconnect (e.g., call `FooClient::Connect()` again).
  2. Let the new `FooClient` instance re-discover version/hash and recompute capabilities.

* **Do not cache version/hash between process restarts.**
  Treat version and hash as per-connection, per-process state. When the process starts, assume nothing and probe again.

* **Log once per connection.**
  Log the interface version and hash at connection time for telemetry/debug purposes:

  ```cpp
  std::cout << "Connected to IFoo v" << mVersion
            << " (hash=" << mHash << ")" << std::endl;
  ```

  Avoid logging this on every call.

---

## 7. Server Guidelines

Servers implementing Stable AIDL should:

1. **Only add** new functions or parcelable fields.
   Do not remove or change existing method signatures or field types.

2. **Increment the interface version** whenever a new feature is added.
   Depending on your AIDL setup, the version may be driven by annotations or build-time configuration.
   Ensure your process bumps the version whenever you add public methods or capabilities that clients might gate on.

3. **Return `EX_UNSUPPORTED_OPERATION` when a feature is unavailable at runtime.**
   For example, if a feature is disabled by configuration, or temporarily unavailable due to resource constraints, the method should:

   * Exist on the interface.
   * Return a status where `getExceptionCode() == EX_UNSUPPORTED_OPERATION`.

4. **Avoid using `STATUS_UNKNOWN_TRANSACTION` except for genuinely missing methods.**
   In practice, `STATUS_UNKNOWN_TRANSACTION` is raised when a client calls a method that does not exist in the server’s implementation (e.g., older server, newer client).
   Do not repurpose this status for “feature disabled” scenarios.

---

## 8. Summary

Stable AIDL ensures interface stability, but forward compatibility relies on **client discipline**:

* Detect supported features via version/hash.
* Use new APIs only when available (`supportsX()` helpers).
* Handle unsupported or missing methods gracefully via optional-returning wrappers.
* Centralize all versioning and fallback logic in a dedicated adapter (e.g., `FooClient`), and keep the rest of the codebase free of ad-hoc version checks.

---

## Appendix A: Implementation Notes

The examples assume the standard binder APIs. Typical includes for a real implementation might be:

```cpp
#include <binder_manager.h>     // ServiceManager_waitForService
#include <binder_auto_utils.h>  // Status helpers, if used
```

Project-specific error handling (logging macros, error types, etc.) can be layered on top of the pattern shown here without changing the versioning and fallback semantics.

---

**Author:** Gerald Weatherup
**Date:** 13th October 2025

