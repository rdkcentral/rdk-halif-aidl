# RDK HAL AIDL Versioning Guide

## Overview

This guide explains how to manage AIDL interface versions in the RDK HAL AIDL project. **Version numbers represent backward-compatible evolution**, not breaking changes.

## Core Principles

### 1. **Backward Compatibility is Mandatory**

Every new version MUST be fully backward-compatible with all previous versions:

- ✅ **Allowed Changes:**
  - ADD new methods at the END of an interface
  - ADD new fields at the END of a parcelable/struct
  - ADD new enum values (with fallback handling)
  - ADD new optional parameters with defaults

- ❌ **Prohibited Changes:**
  - Remove methods or fields
  - Change method signatures or field types
  - Reorder methods or fields
  - Rename methods or fields
  - Change method return types

### 2. **Version Numbers are Incremental**

- **v1** = First frozen/stable version
- **v2** = v1 + additional features (backward-compatible)
- **v3** = v2 + additional features (backward-compatible)
- Each version includes ALL features from previous versions

### 3. **Breaking Changes Require New Interface**

If you need incompatible changes, create a **completely new interface component**:

- Original: `IBoot` → New: `IBootNew` or `IBootV2`
- The old interface continues to exist
- Clients migrate at their own pace
- Both interfaces can coexist

## Development Workflow

### Initial Development (No Frozen Versions)

```bash
# 1. Create/edit AIDL interfaces in module/current/
vim boot/current/com/rdk/hal/boot/IBoot.aidl

# 2. Build and test
./build_interfaces.sh boot

# 3. Iterate as needed - no versioning constraints yet
# You can make ANY changes during this phase
```

**Note:** Before the first freeze, you have complete freedom to change interfaces.

### Freezing Version 1

When your interface is stable and ready for production:

```bash
# Freeze the current interface as version 1
./freeze_interface.sh boot

# This creates:
# - stable/aidl/boot/1/          (frozen AIDL)
# - stable/generated/boot/1/     (frozen C++ code)
# - Builds lib boot-v1-cpp.so    (frozen library)
```

**After freezing v1:**
- Version 1 is **immutable** - no changes allowed
- `boot/current/` remains editable for v2 development
- Both `boot-v1-cpp` and `boot-vcurrent-cpp` libraries exist

### Evolving to Version 2

```aidl
// Version 1 (frozen - immutable)
interface IBoot {
    void reboot();
    void shutdown();
}

// Version 2 development (boot/current/)
// Add new methods ONLY at the end
interface IBoot {
    void reboot();                  // MUST keep v1 methods
    void shutdown();                // MUST keep v1 methods
    void rebootWithReason(String reason);  // NEW in v2
}
```

```bash
# 1. Edit boot/current/ to add new methods
vim boot/current/com/rdk/hal/boot/IBoot.aidl

# 2. Update API (validates compatibility)
./build_interfaces.sh boot

# 3. If validation fails with compatibility error:
#    - You made a breaking change
#    - Revert your changes OR create new interface (IBootNew)

# 4. When ready, freeze v2
./freeze_interface.sh boot
```

### Version Evolution Example

Real-world example from `examples/aidl_versioning/`:

**Version 1:**
```aidl
package com.demo.hal.car;

interface IVehicle {
    VehicleSpecs getVehicleSpecs();
    VehicleStatus getVehicleStatus();
    void startVehicleEngine();
    void stopVehicleEngine();
    void startMoving();
    void stopMoving();
    void registerVehicleStatusListener(IVehicleStatusListener listener);
    void unregisterVehicleStatusListener(IVehicleStatusListener listener);
}
```

**Version 2** (adds lock/unlock):
```aidl
package com.demo.hal.car;

interface IVehicle {
    // ALL v1 methods remain unchanged
    VehicleSpecs getVehicleSpecs();
    VehicleStatus getVehicleStatus();
    void startVehicleEngine();
    void stopVehicleEngine();
    void startMoving();
    void stopMoving();
    void registerVehicleStatusListener(IVehicleStatusListener listener);
    void unregisterVehicleStatusListener(IVehicleStatusListener listener);

    // NEW v2 methods added at the end
    void lockVehicle();
    void unlockVehicle();
}
```

**Version 3** (adds fuel control):
```aidl
package com.demo.hal.car;

interface IVehicle {
    // ALL v1 and v2 methods remain
    // ... (v1 methods)
    void lockVehicle();
    void unlockVehicle();

    // NEW v3 method
    void setFuelLevel(float fuelLevel);
}
```

## Validation and Error Handling

### Pre-Copy Validation

The build system validates compatibility **BEFORE** copying changes:

```bash
$ ./build_interfaces.sh boot
--> [Step 3/4] Updating APIs...
    Updating: boot
Pre-validating compatibility before updating boot
Pre-validation FAILED: Source changes are incompatible with existing stable API

================================================================================
AIDL Compatibility Check FAILED for boot
================================================================================
ERROR: Removed method "reboot()" - this is a breaking change

IMPORTANT: Breaking changes are NOT permitted in AIDL versioned interfaces.
Only the following changes are allowed:
  ✓ ADD new methods at the END of an interface
  ✓ ADD new fields at the END of a parcelable
  ✓ ADD new enum values (with fallback handling)

The following changes are FORBIDDEN:
  ✗ Remove methods or fields
  ✗ Change method signatures or field types
  ✗ Reorder methods or fields
  ✗ Rename methods or fields

If you need to make breaking changes:
  1. Create a NEW interface component (e.g., IBootNew)
  2. Leave the existing interface unchanged
  3. Clients can migrate to the new interface at their own pace
================================================================================
```

### First Freeze Special Case

When creating version 1 (first freeze), compatibility checks are skipped:

```bash
$ ./freeze_interface.sh boot
No frozen versions exist for boot - skipping compatibility validation
Freezing boot as version 1...
✅ Version 1 created successfully
```

## Client Version Discovery

Clients can detect and adapt to different server versions:

```cpp
#include <com/rdk/hal/boot/IBoot.h>

// Connect to service
std::shared_ptr<IBoot> bootService = IBoot::fromBinder(binder);

// Get server version
int32_t clientVersion = IBoot::VERSION;  // Compile-time constant
int32_t serverVersion = bootService->getInterfaceVersion();
std::string serverHash = bootService->getInterfaceHash();

// Version-based behavior
if (serverVersion >= 2) {
    // Safe to use v2 features
    bootService->rebootWithReason("system_update");
} else {
    // Fallback for v1-only servers
    bootService->reboot();
}
```

### Client-Server Compatibility Matrix

| Client Version | Server Version | Result |
|---------------|----------------|--------|
| v1 | v1 | ✅ Perfect match |
| v1 | v2 | ✅ Works - server supports all v1 methods |
| v1 | v3 | ✅ Works - server supports all v1 methods |
| v2 | v1 | ⚠️ Partial - v1 methods work, v2 methods return error |
| v2 | v2 | ✅ Perfect match |
| v3 | v2 | ⚠️ Partial - v1+v2 methods work, v3 methods return error |

## When to Freeze

### Freeze When:
- ✅ Interface is stable and ready for production use
- ✅ External partners need a stable API to develop against
- ✅ Multiple devices will use this interface version
- ✅ You want to start developing v2 features while maintaining v1

### Don't Freeze If:
- ❌ Still actively experimenting with interface design
- ❌ Only used internally in development
- ❌ Interface design not yet reviewed/approved
- ❌ Expect significant changes in near future

**Recommendation:** Freeze conservatively. It's better to iterate in `current/` longer than to create many similar frozen versions.

## Library Naming and Deployment

### Library Names

Each version produces a separate library:

```
libboot-vcurrent-cpp.so  # Development version (current/)
libboot-v1-cpp.so        # Frozen version 1
libboot-v2-cpp.so        # Frozen version 2
```

### Application Linking

Applications choose which version to link at build time:

```cmake
# CMakeLists.txt
target_link_interfaces_libraries(myapp boot-v1-cpp)  # Use frozen v1
# OR
target_link_interfaces_libraries(myapp boot-vcurrent-cpp)  # Use latest
```

### Deployment Scenarios

**Scenario 1: Single Version Deployment**
```bash
# Deploy only v1 (stable) - runtime library only
scp out/target/lib/halif/libboot-v1-cpp.so device:/usr/lib/
```

**Scenario 2: Multi-Version Deployment**
```bash
# Deploy both v1 and v2 (transition period) - runtime libraries only
scp out/target/lib/halif/libboot-v1-cpp.so device:/usr/lib/
scp out/target/lib/halif/libboot-v2-cpp.so device:/usr/lib/
```

## Testing Versioned Interfaces

### Automated Tests

```bash
# Test compatibility validation
./build_interfaces.sh test-validation

# Tests:
# ✅ First update succeeds
# ✅ Adding methods succeeds (compatible)
# ✅ Removing methods fails (incompatible)
# ✅ Changing signatures fails (incompatible)
```

### Manual Testing

```bash
# 1. Make compatible change (add method)
vim boot/current/com/rdk/hal/boot/IBoot.aidl
# Add: void newMethod();
./build_interfaces.sh boot
# ✅ Should succeed

# 2. Make incompatible change (remove method)
vim boot/current/com/rdk/hal/boot/IBoot.aidl
# Remove: void reboot();
./build_interfaces.sh boot
# ❌ Should fail with clear error message
```

## Common Scenarios

### Scenario 1: Adding Optional Features

**Good Pattern:**
```aidl
// v1
interface IBoot {
    void reboot();
}

// v2 - add optional features
interface IBoot {
    void reboot();
    void rebootWithReason(String reason);  // Client checks version first
}
```

**Client Code:**
```cpp
if (bootService->getInterfaceVersion() >= 2) {
    bootService->rebootWithReason("update");
} else {
    bootService->reboot();  // Fallback
}
```

### Scenario 2: Extending Data Structures

**Good Pattern:**
```aidl
// v1
parcelable BootStatus {
    boolean isBooting;
}

// v2 - add fields at end
parcelable BootStatus {
    boolean isBooting;      // v1 field
    long bootTimeMs;        // NEW v2 field
}
```

### Scenario 3: Deprecating Features

**Problem:** Can't remove methods from versioned interface.

**Solution 1:** Make method no-op in implementation:
```cpp
// v2 implementation - deprecate but keep method
Status IBoot::oldDeprecatedMethod() {
    ALOGW("oldDeprecatedMethod is deprecated, use newMethod instead");
    return Status::ok();
}
```

**Solution 2:** Create new interface:
```aidl
// If truly incompatible, create IBootNew
interface IBootNew {
    void modernReboot(RebootOptions options);
    // No old deprecated methods
}
```

## Best Practices

### DO:
- ✅ Plan interface design carefully before first freeze
- ✅ Add comprehensive documentation to interfaces
- ✅ Use semantic naming for new methods (e.g., `rebootWithReason` not `reboot2`)
- ✅ Test compatibility before committing changes
- ✅ Provide migration guides when adding features
- ✅ Use version checking in client code for optional features

### DON'T:
- ❌ Remove or modify frozen versions
- ❌ Make breaking changes to `current/` after freezing v1
- ❌ Bypass validation by manually editing `stable/aidl/`
- ❌ Freeze too frequently (creates version sprawl)
- ❌ Freeze too early (before interface is stable)
- ❌ Use v2 features without version checking

## Troubleshooting

### "Compatibility validation failed" Error

**Problem:** Build fails with incompatibility error.

**Solution:**
1. Check error message - identifies specific violation
2. If you need the breaking change:
   - Revert your changes, OR
   - Create new interface (e.g., `IBootNew`)
3. If change should be compatible, ensure methods added at END

### "No frozen versions exist" Warning

**Problem:** Seeing warnings about no frozen versions.

**Solution:** This is normal before first freeze. Validation is skipped automatically.

### Multiple Frozen Versions Colliding

**Problem:** v1 and v2 clients both running, causing conflicts.

**Solution:** This is by design - both versions should coexist. Ensure:
- Different library names (libboot-v1-cpp.so vs libboot-v2-cpp.so)
- Different include paths (boot/1/ vs boot/2/)
- Service registration uses version-specific names or versioned endpoints

## References

- **Live Examples:** [examples/aidl_versioning/](../../examples/aidl_versioning/)
- **Client Patterns:** [client-patterns.md](client-patterns.md)
- **Migration Guide:** [migration-guide.md](migration-guide.md)
- **Android AIDL Docs:** [Android AIDL Versioning](https://source.android.com/docs/core/architecture/aidl/aidl-versioning)
- **Build Script:** [build_interfaces.sh](../../build_interfaces.sh)
- **Freeze Script:** [freeze_interface.sh](../../freeze_interface.sh)

## Quick Reference

```bash
# Development workflow
vim module/current/com/rdk/hal/module/IModule.aidl
./build_interfaces.sh module              # Update + validate
./build_interfaces.sh test-validation     # Test validation logic

# Freeze workflow
./freeze_interface.sh module              # Create v1, v2, etc.

# Testing
./build_interfaces.sh test                # Basic build test
./build_interfaces.sh test-all            # Comprehensive test
./build_interfaces.sh test-validation     # Validation logic test

# Cleanup
./build_interfaces.sh clean               # Remove build outputs
./build_interfaces.sh cleanstable         # Remove generated code
```
