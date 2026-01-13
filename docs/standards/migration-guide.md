# RDK HAL AIDL Migration Guide

## Overview

This guide provides step-by-step instructions for migrating client applications when new HAL interface versions are released. Learn how to detect versions, update code, and deploy in mixed-version environments.

## Migration Scenarios

### Scenario 1: Upgrading from v1 to v2 Server

**Context:** Your application was developed against v1 of the boot HAL. A new v2 server is deployed with additional features.

#### Step 1: Assess the Changes

**What changed in v2?**
```bash
# Compare AIDL definitions
diff -u stable/aidl/boot/1/com/rdk/hal/boot/IBoot.aidl \
        stable/aidl/boot/2/com/rdk/hal/boot/IBoot.aidl
```

**Example output:**
```diff
interface IBoot {
    void reboot();
    void shutdown();
+   void rebootWithReason(String reason);  // NEW in v2
+   void getBootHistory(out BootHistory[] history);  // NEW in v2
}
```

#### Step 2: Update Client Code (Optional)

**Option A: No Changes Required**
```cpp
// Existing v1 client continues to work with v2 server
auto bootService = IBoot::fromBinder(binder);
bootService->reboot();  // Still works!
```

**Option B: Use New Features**
```cpp
// Updated client that uses v2 features when available
auto bootService = IBoot::fromBinder(binder);

int32_t serverVersion;
bootService->getInterfaceVersion(&serverVersion);

if (serverVersion >= 2) {
    // Use v2 feature
    bootService->rebootWithReason("system_update");
} else {
    // Fallback to v1
    bootService->reboot();
}
```

#### Step 3: Recompile (Optional)

**Keep linking to v1:**
```cmake
# CMakeLists.txt - no changes needed
target_link_interfaces_libraries(myapp boot-v1-cpp)
```

**OR upgrade to v2:**
```cmake
# CMakeLists.txt - link to v2
target_link_interfaces_libraries(myapp boot-v2-cpp)
```

#### Step 4: Deploy

**Mixed environment (gradual rollout):**
```bash
# Some devices with v1 server
device1$ ls /usr/lib/libboot-v1-cpp.so
/usr/lib/libboot-v1-cpp.so

# Other devices with v2 server
device2$ ls /usr/lib/libboot-v2-cpp.so
/usr/lib/libboot-v2-cpp.so

# Your v1 client works on both!
```

### Scenario 2: Proactive Migration to v3

**Context:** v3 HAL is released. You want to adopt new features before they're deployed everywhere.

#### Step 1: Review Release Notes

```markdown
## Boot HAL v3 Release Notes

### New Features
- Secure reboot with cryptographic validation
- Boot history with timestamps
- Power source tracking

### Breaking Changes
None (fully backward-compatible with v1 and v2)

### Minimum Requirements
- Kernel 5.10+
- Secure boot enabled
```

#### Step 2: Update Build Configuration

```cmake
# CMakeLists.txt
target_link_interfaces_libraries(myapp boot-v3-cpp)
```

```cpp
// Update includes
#include <com/rdk/hal/boot/IBoot.h>  // Now v3
```

#### Step 3: Implement Version-Aware Code

```cpp
class BootManager {
private:
    std::shared_ptr<IBoot> mService;
    int32_t mServerVersion;
    
public:
    bool initialize() {
        mService = getBootService();
        if (!mService) return false;
        
        mService->getInterfaceVersion(&mServerVersion);
        ALOGI("Boot HAL server version: v%d", mServerVersion);
        
        return true;
    }
    
    void performReboot(const std::string& reason, bool secure = false) {
        if (secure && mServerVersion >= 3) {
            // v3: Secure reboot
            ALOGI("Using v3 secure reboot");
            mService->secureReboot(reason);
            
        } else if (!reason.empty() && mServerVersion >= 2) {
            // v2: Reboot with reason
            ALOGI("Using v2 reboot with reason");
            mService->rebootWithReason(reason);
            
        } else {
            // v1: Basic reboot
            ALOGI("Using v1 basic reboot");
            mService->reboot();
        }
    }
};
```

#### Step 4: Test in Mixed Environment

```bash
# Test with v1 server
$ TEST_SERVER_VERSION=1 ./run_tests

# Test with v2 server
$ TEST_SERVER_VERSION=2 ./run_tests

# Test with v3 server
$ TEST_SERVER_VERSION=3 ./run_tests
```

### Scenario 3: Handling Breaking Changes (New Interface)

**Context:** HAL team determined that true breaking changes are needed and created `IBootNew`.

#### Step 1: Understand the New Interface

```aidl
// Old interface (still supported)
package com.rdk.hal.boot;
interface IBoot {
    void reboot();
    void shutdown();
    void rebootWithReason(String reason);
}

// New interface (incompatible changes)
package com.rdk.hal.boot;
interface IBootNew {
    // Completely redesigned API
    BootResult performAction(BootAction action, BootOptions options);
    Stream<BootEvent> monitorBootEvents();
}
```

#### Step 2: Plan Migration Strategy

**Strategy A: Gradual Migration**
```cpp
// Support both old and new interfaces
class BootManager {
private:
    std::shared_ptr<IBoot> mLegacyService;
    std::shared_ptr<IBootNew> mNewService;
    bool mUsingNewInterface = false;
    
public:
    bool initialize() {
        // Try new interface first
        mNewService = getBootNewService();
        if (mNewService) {
            ALOGI("Using new boot interface (IBootNew)");
            mUsingNewInterface = true;
            return true;
        }
        
        // Fallback to legacy
        mLegacyService = getBootService();
        if (mLegacyService) {
            ALOGI("Using legacy boot interface (IBoot)");
            return true;
        }
        
        return false;
    }
    
    void reboot(const std::string& reason) {
        if (mUsingNewInterface) {
            BootAction action{ActionType::REBOOT, reason};
            mNewService->performAction(action, BootOptions{});
        } else {
            if (!reason.empty()) {
                mLegacyService->rebootWithReason(reason);
            } else {
                mLegacyService->reboot();
            }
        }
    }
};
```

**Strategy B: Clean Cut**
```cpp
// Only support new interface, require migration
class BootManager {
private:
    std::shared_ptr<IBootNew> mService;
    
public:
    bool initialize() {
        mService = getBootNewService();
        if (!mService) {
            ALOGE("IBootNew not available - please upgrade HAL");
            return false;
        }
        return true;
    }
    
    void reboot(const std::string& reason) {
        BootAction action{ActionType::REBOOT, reason};
        mService->performAction(action, BootOptions{});
    }
};
```

## Deployment Strategies

### Strategy 1: Phased Rollout

**Phase 1: Deploy v2 Server (Week 1-2)**
```bash
# Update servers only
devices=(device1 device2 device3)
for device in "${devices[@]}"; do
    scp out/target/lib/halif/libboot-v2-cpp.so $device:/usr/lib/
    ssh $device "systemctl restart boot-hal"
done

# Existing v1 clients continue working
```

**Phase 2: Update Clients (Week 3-4)**
```bash
# Roll out updated clients
for device in "${devices[@]}"; do
    scp myapp-v2 $device:/usr/bin/myapp
    ssh $device "systemctl restart myapp"
done
```

**Phase 3: Verify (Week 5)**
```bash
# Verify all clients using v2 features
for device in "${devices[@]}"; do
    ssh $device "journalctl -u myapp | grep 'Boot HAL server version'"
done
```

### Strategy 2: Blue-Green Deployment

**Setup:**
```bash
# Blue environment: v1 server + v1 clients
# Green environment: v2 server + v2 clients

# Deploy green environment
./deploy_green.sh

# Validate green environment
./validate_green.sh

# Switch traffic to green
./switch_to_green.sh

# Monitor for issues
./monitor.sh

# Rollback if needed
./rollback_to_blue.sh
```

### Strategy 3: Canary Deployment

```bash
# Deploy v2 to 5% of devices
./deploy_canary.sh --percentage 5

# Monitor metrics
./monitor_canary.sh --duration 24h

# Expand to 25%
./deploy_canary.sh --percentage 25

# Monitor again
./monitor_canary.sh --duration 48h

# Full rollout
./deploy_all.sh
```

## Common Migration Tasks

### Task 1: Add Version Logging

**Before:**
```cpp
void MyApp::initialize() {
    mBootService = getBootService();
    // No version info logged
}
```

**After:**
```cpp
void MyApp::initialize() {
    mBootService = getBootService();
    
    int32_t version;
    std::string hash;
    mBootService->getInterfaceVersion(&version);
    mBootService->getInterfaceHash(&hash);
    
    ALOGI("Boot HAL - Version: v%d, Hash: %s", version, hash.c_str());
    
    // Log to metrics system
    Metrics::recordString("boot_hal_version", std::to_string(version));
    Metrics::recordString("boot_hal_hash", hash);
}
```

### Task 2: Feature Flag Integration

```cpp
class FeatureManager {
private:
    std::map<std::string, bool> mFeatures;
    
public:
    void discoverFeatures(const std::shared_ptr<IBoot>& service) {
        int32_t version;
        service->getInterfaceVersion(&version);
        
        // Map versions to feature flags
        mFeatures["reboot_with_reason"] = (version >= 2);
        mFeatures["secure_reboot"] = (version >= 3);
        mFeatures["boot_history"] = (version >= 2);
        
        // Log feature availability
        for (const auto& [feature, available] : mFeatures) {
            ALOGI("Feature '%s': %s", feature.c_str(), 
                  available ? "AVAILABLE" : "UNAVAILABLE");
        }
    }
    
    bool isAvailable(const std::string& feature) const {
        auto it = mFeatures.find(feature);
        return (it != mFeatures.end()) && it->second;
    }
};
```

### Task 3: Graceful Degradation

```cpp
class VideoDecoderClient {
public:
    void decodeStream(const VideoStream& stream) {
        int32_t serverVer;
        mDecoder->getInterfaceVersion(&serverVer);
        
        // Try newest API first
        if (serverVer >= 3 && stream.hasHDR()) {
            ALOGI("Using v3 HDR decoding");
            decodeWithHDR(stream);
        } 
        // Fall back to v2
        else if (serverVer >= 2 && stream.codec == Codec::HEVC) {
            ALOGI("Using v2 HEVC decoding");
            decodeWithHEVC(stream);
        } 
        // Final fallback to v1
        else {
            ALOGI("Using v1 basic decoding");
            decodeBasic(stream);
        }
    }
};
```

## Troubleshooting

### Problem 1: Service Not Found

**Symptom:**
```
E/MyApp: Failed to get boot service
```

**Diagnosis:**
```bash
# Check if service is registered
$ service list | grep boot
# (empty - service not running)

# Check HAL status
$ systemctl status boot-hal
● boot-hal.service - Boot HAL Service
   Active: failed
```

**Solution:**
```bash
# Restart HAL service
$ systemctl restart boot-hal

# Verify registration
$ service list | grep boot
com.rdk.hal.boot.IBoot
```

### Problem 2: Version Mismatch

**Symptom:**
```
W/MyApp: Version mismatch - client: v3, server: v2
E/MyApp: secureReboot failed: Method not implemented
```

**Diagnosis:**
```cpp
int32_t clientVer = IBoot::VERSION;  // 3
int32_t serverVer;
mService->getInterfaceVersion(&serverVer);  // 2
// Client expects v3, server is v2
```

**Solution:**
```cpp
// Add version checks before calling v3 methods
if (serverVer >= 3) {
    mService->secureReboot(reason);
} else if (serverVer >= 2) {
    mService->rebootWithReason(reason);  // Fallback
} else {
    mService->reboot();  // Final fallback
}
```

### Problem 3: Hash Mismatch

**Symptom:**
```
E/Binder: Interface hash mismatch
W/MyApp: Hash validation failed
```

**Diagnosis:**
```bash
# Check hash of deployed library
$ readelf -p .note.gnu.build-id /usr/lib/libboot-v2-cpp.so

# Compare with expected hash from build
$ cat stable/aidl/boot/2/.hash
```

**Solution:**
```bash
# Redeploy correct library
$ scp out/target/lib/halif/libboot-v2-cpp.so device:/usr/lib/
$ ssh device "systemctl restart boot-hal"
```

## Testing Migration

### Integration Test Example

```cpp
class MigrationTest : public ::testing::Test {
protected:
    void TestWithVersion(int32_t version) {
        auto mockService = std::make_shared<MockBoot>();
        
        EXPECT_CALL(*mockService, getInterfaceVersion(testing::_))
            .WillRepeatedly(testing::DoAll(
                testing::SetArgPointee<0>(version),
                testing::Return(Status::ok())
            ));
        
        BootManager manager(mockService);
        manager.initialize();
        
        // Test appropriate functionality for this version
        if (version >= 2) {
            EXPECT_CALL(*mockService, rebootWithReason("test"))
                .WillOnce(testing::Return(Status::ok()));
            manager.reboot("test");
        } else {
            EXPECT_CALL(*mockService, reboot())
                .WillOnce(testing::Return(Status::ok()));
            manager.reboot("test");
        }
    }
};

TEST_F(MigrationTest, WorksWithV1) {
    TestWithVersion(1);
}

TEST_F(MigrationTest, WorksWithV2) {
    TestWithVersion(2);
}

TEST_F(MigrationTest, WorksWithV3) {
    TestWithVersion(3);
}
```

## Best Practices

### DO:
- ✅ Test with all server versions you need to support
- ✅ Log version information at startup
- ✅ Provide fallbacks for older servers
- ✅ Plan rollout strategy before deployment
- ✅ Monitor version distribution in production
- ✅ Document version requirements clearly
- ✅ Use feature flags for new functionality

### DON'T:
- ❌ Deploy client updates before server updates
- ❌ Assume all servers are same version
- ❌ Remove fallback code prematurely
- ❌ Skip testing with older server versions
- ❌ Hard-code version assumptions
- ❌ Ignore version mismatch warnings

## Quick Reference

```bash
# Check server version from client
int32_t version;
service->getInterfaceVersion(&version);

# Check installed library version
readelf -p .comment /usr/lib/libboot-v2-cpp.so

# List running HAL services
service list | grep rdk.hal

# Monitor version distribution
for host in $(cat device_list); do
    ssh $host "readelf -p .comment /usr/lib/libboot-*-cpp.so"
done | grep "version"
```

## References

- **Versioning Guide:** [versioning-guide.md](versioning-guide.md)
- **Client Patterns:** [client-patterns.md](client-patterns.md)
- **Build System:** [build_interfaces.sh](../../build_interfaces.sh)
- **Example Migrations:** [examples/aidl_versioning/](../../examples/aidl_versioning/)
