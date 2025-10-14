# **WhitePaper: Client Usage of Stable AIDL with Versioning & Fallback**

**Type:** Engineering Whitepaper
**Audience:** Developers integrating and maintaining C++ client code that interacts with Stable AIDL-generated interfaces.
**Purpose:** Define a consistent client-side approach for version discovery, capability management, and fallback when new features are introduced in Stable AIDL interfaces.

---

## 1. Overview

Stable AIDL interfaces evolve over time—new APIs, new capabilities, updated features.
The interface definition guarantees compatibility across versions, but the **client** must still detect and adapt to what the connected service actually supports.

This paper defines the client engineering standard for version handling and runtime adaptation when using Stable AIDL-generated C++ interfaces (as produced by Google’s AIDL compiler).
The patterns and examples align with the interface style used in this repository.

---

## 2. Key Design Goals

1. **Additive evolution** – new functions are added, never replacing or removing old ones.
2. **Self-contained headers** – each generated interface (e.g., `IFoo.h`) includes all required functionality and AIDL plumbing.
3. **Capability awareness** – clients should discover what’s available and adapt accordingly.
4. **Consistent error semantics** – handle unknown transactions and unsupported operations explicitly.
5. **Centralised logic** – version and feature handling belongs in a thin adapter, not scattered across the codebase.

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

* Probe version/hash once per connection.
* Cache capabilities.
* Provide clear optional feature accessors (e.g., `supportsFunctionB()`).
* Handle runtime errors gracefully and clearly.

### Example: `FooClient`

```cpp
#pragma once
#include "IFoo.h"   // All AIDL-generated content for IFoo lives here
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <iostream>

class FooClient {
public:
    static std::shared_ptr<FooClient> Connect(const char* serviceName = "com.example.IFoo/default") {
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
        if (!st.isOk()) throw std::runtime_error(st.getDescription());
        return out;
    }

    // ---- V2 optional API ----
    std::optional<int> tryFunctionB(int y) {
        if (!supportsFunctionB()) return std::nullopt;

        int out = 0;
        auto st = mRemote->functionB(y, &out);

        if (st.isOk()) return out;

        if (st.getStatus() == STATUS_UNKNOWN_TRANSACTION ||
            st.getExceptionCode() == EX_UNSUPPORTED_OPERATION) {
            return std::nullopt;
        }

        throw std::runtime_error(st.getDescription());
    }

private:
    explicit FooClient(std::shared_ptr<IFoo> remote)
        : mRemote(std::move(remote)) {
        int32_t v = 1;
        std::string h;

        if (!mRemote->getInterfaceVersion(&v).isOk()) v = 1;
        if (!mRemote->getInterfaceHash(&h).isOk()) h = "unknown";

        mVersion = v;
        mHash = std::move(h);
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
    std::cout << "functionB not supported on this implementation" << std::endl;
}
```

---

## 5. Error Handling Semantics

| Scenario                           | Binder Status                | Client Response                  |
| ---------------------------------- | ---------------------------- | -------------------------------- |
| Method missing (older server)      | `STATUS_UNKNOWN_TRANSACTION` | Treat as not supported           |
| Method exists but feature disabled | `EX_UNSUPPORTED_OPERATION`   | Treat as temporarily unavailable |
| Any other binder failure           | `!isOk()`                    | Raise runtime error              |

---

## 6. Lifecycle & Version Refresh

* **Re-probe** after binder death or reconnect.
* **Do not** cache version/hash between process restarts.
* **Log once per connection**: version and hash for telemetry/debug.

```cpp
std::cout << "Connected to IFoo v" << mVersion << " (hash=" << mHash << ")" << std::endl;
```

---

## 7. Server Guidelines

Servers implementing Stable AIDL should:

1. Only add new functions or parcelable fields.
2. Increment the interface version whenever a new feature is added.
3. Return `EX_UNSUPPORTED_OPERATION` when a feature is unavailable at runtime.
4. Avoid using `STATUS_UNKNOWN_TRANSACTION` except for genuinely missing methods.

---

## 8. Summary

Stable AIDL ensures interface stability, but forward compatibility relies on **client discipline**:

* Detect supported features.
* Use new APIs only when available.
* Handle unsupported or missing methods gracefully.
* Centralize all versioning and fallback logic in a dedicated adapter.

---

**Author:** Gerald Weatherup  
**Date:** 13th October 2025
