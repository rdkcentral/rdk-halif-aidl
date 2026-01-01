# RDK HAL AIDL Client Patterns

## Overview

This guide provides practical patterns for client applications consuming RDK HAL AIDL versioned interfaces. Learn how to handle version discovery, graceful degradation, and optional feature usage.

## Basic Client Setup

### Linking Against an Interface

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
project(MyHALClient)

# Link to specific version
target_link_interfaces_libraries(myclient boot-v1-cpp)

# OR link to latest (current)
target_link_interfaces_libraries(myclient boot-vcurrent-cpp)

# Include paths are handled automatically
```

### Getting a Service Connection

```cpp
#include <android/binder_manager.h>
#include <com/rdk/hal/boot/IBoot.h>

using namespace com::rdk::hal::boot;

// Get service by name
std::shared_ptr<IBoot> getBootService() {
    ndk::SpAIBinder binder(
        AServiceManager_getService(IBoot::serviceName.c_str())
    );
    
    if (binder == nullptr) {
        ALOGE("Failed to get boot service");
        return nullptr;
    }
    
    return IBoot::fromBinder(binder);
}

int main() {
    auto bootService = getBootService();
    if (!bootService) {
        return 1;
    }
    
    // Use the service...
}
```

## Version Discovery Patterns

### Pattern 1: Check Version at Connection

```cpp
#include <com/rdk/hal/boot/IBoot.h>

class BootClient {
private:
    std::shared_ptr<IBoot> mService;
    int32_t mClientVersion;
    int32_t mServerVersion;
    std::string mServerHash;
    
public:
    bool connect() {
        mService = getBootService();
        if (!mService) {
            return false;
        }
        
        // Get version information
        mClientVersion = IBoot::VERSION;
        
        auto status = mService->getInterfaceVersion(&mServerVersion);
        if (!status.isOk()) {
            ALOGE("Failed to get server version: %s", 
                  status.getDescription().c_str());
            return false;
        }
        
        status = mService->getInterfaceHash(&mServerHash);
        if (!status.isOk()) {
            ALOGE("Failed to get server hash");
            return false;
        }
        
        ALOGI("Boot HAL - Client: v%d, Server: v%d (hash: %s)",
              mClientVersion, mServerVersion, mServerHash.c_str());
        
        // Warn if versions don't match
        if (mClientVersion != mServerVersion) {
            ALOGW("Version mismatch - client: v%d, server: v%d",
                  mClientVersion, mServerVersion);
        }
        
        return true;
    }
    
    bool supportsVersion(int32_t minVersion) {
        return mServerVersion >= minVersion;
    }
};
```

### Pattern 2: Lazy Version Check

```cpp
class BootClient {
private:
    std::shared_ptr<IBoot> mService;
    std::optional<int32_t> mServerVersion;  // Cached version
    
    int32_t getServerVersion() {
        if (!mServerVersion.has_value()) {
            int32_t version;
            auto status = mService->getInterfaceVersion(&version);
            if (status.isOk()) {
                mServerVersion = version;
            } else {
                // Assume v1 if version query fails (old server?)
                mServerVersion = 1;
            }
        }
        return mServerVersion.value();
    }
    
public:
    void reboot() {
        // Always safe - in v1
        mService->reboot();
    }
    
    void rebootWithReason(const std::string& reason) {
        if (getServerVersion() >= 2) {
            // v2+ feature
            mService->rebootWithReason(reason);
        } else {
            // Fallback for v1 servers
            ALOGW("Server doesn't support rebootWithReason, using basic reboot");
            mService->reboot();
        }
    }
};
```

## Graceful Degradation

### Pattern 3: Try-Catch with Fallback

```cpp
void BootClient::rebootWithOptions(const RebootOptions& options) {
    try {
        // Try v3 feature first
        auto status = mService->rebootWithOptions(options);
        if (status.isOk()) {
            return;
        }
        
        // Check if it's a "method not found" error
        if (status.getExceptionCode() == EX_UNSUPPORTED_OPERATION) {
            ALOGW("rebootWithOptions not supported, falling back");
        } else {
            ALOGE("rebootWithOptions failed: %s", 
                  status.getDescription().c_str());
            return;
        }
    } catch (const std::exception& e) {
        ALOGW("Exception calling rebootWithOptions: %s", e.what());
    }
    
    // Fallback to v2 if available
    if (getServerVersion() >= 2) {
        ALOGI("Using v2 rebootWithReason");
        mService->rebootWithReason(options.reason);
    } else {
        // Final fallback to v1
        ALOGI("Using v1 basic reboot");
        mService->reboot();
    }
}
```

### Pattern 4: Feature Flags

```cpp
class BootClient {
private:
    struct Features {
        bool hasRebootWithReason = false;
        bool hasRebootWithOptions = false;
        bool hasSecureReboot = false;
    };
    
    Features mFeatures;
    
    void discoverFeatures() {
        int32_t version = getServerVersion();
        
        // Map versions to features
        mFeatures.hasRebootWithReason = (version >= 2);
        mFeatures.hasRebootWithOptions = (version >= 3);
        mFeatures.hasSecureReboot = (version >= 4);
        
        ALOGI("Boot HAL Features:");
        ALOGI("  - RebootWithReason: %s", 
              mFeatures.hasRebootWithReason ? "YES" : "NO");
        ALOGI("  - RebootWithOptions: %s", 
              mFeatures.hasRebootWithOptions ? "YES" : "NO");
        ALOGI("  - SecureReboot: %s", 
              mFeatures.hasSecureReboot ? "YES" : "NO");
    }
    
public:
    bool connect() {
        if (!connectToService()) {
            return false;
        }
        discoverFeatures();
        return true;
    }
    
    void performReboot(const std::string& reason, bool secure = false) {
        if (secure && mFeatures.hasSecureReboot) {
            mService->secureReboot(reason);
        } else if (mFeatures.hasRebootWithReason) {
            mService->rebootWithReason(reason);
        } else {
            mService->reboot();
        }
    }
};
```

## Optional Feature Usage

### Pattern 5: Capability Query

```cpp
class VideoDecoderClient {
private:
    std::shared_ptr<IVideoDecoder> mDecoder;
    
public:
    bool supportsHEVC() {
        // Check version first (cheap)
        if (getServerVersion() < 2) {
            return false;
        }
        
        // Query capabilities (may be expensive)
        Capabilities caps;
        auto status = mDecoder->getCapabilities(&caps);
        if (!status.isOk()) {
            return false;
        }
        
        return caps.supportedCodecs.contains(Codec::HEVC);
    }
    
    Status decodeVideo(const VideoStream& stream) {
        if (stream.codec == Codec::HEVC && !supportsHEVC()) {
            ALOGE("HEVC not supported by this decoder version");
            return Status::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
        }
        
        return mDecoder->decode(stream);
    }
};
```

### Pattern 6: Progressive Enhancement

```cpp
class HDMIOutputClient {
private:
    std::shared_ptr<IHDMIOutput> mOutput;
    
public:
    void setResolution(int width, int height, int refreshRate) {
        if (getServerVersion() >= 3) {
            // v3: Full control including refresh rate
            DisplayMode mode{width, height, refreshRate};
            mOutput->setDisplayMode(mode);
            
        } else if (getServerVersion() >= 2) {
            // v2: Width and height only
            Resolution res{width, height};
            mOutput->setResolution(res);
            ALOGW("Refresh rate %d ignored (requires v3+)", refreshRate);
            
        } else {
            // v1: Predefined resolutions only
            auto presetMode = findClosestPreset(width, height);
            mOutput->setMode(presetMode);
            ALOGW("Exact resolution not supported (requires v2+)");
        }
    }
};
```

## Error Handling

### Pattern 7: Robust Error Handling

```cpp
class RobustClient {
private:
    std::shared_ptr<IBoot> mService;
    
    bool callSafely(std::function<Status()> operation, 
                    const char* opName) {
        try {
            auto status = operation();
            
            if (status.isOk()) {
                return true;
            }
            
            // Handle specific error codes
            switch (status.getExceptionCode()) {
                case EX_UNSUPPORTED_OPERATION:
                    ALOGW("%s: Operation not supported", opName);
                    break;
                    
                case EX_ILLEGAL_ARGUMENT:
                    ALOGE("%s: Invalid argument", opName);
                    break;
                    
                case EX_ILLEGAL_STATE:
                    ALOGE("%s: Invalid state", opName);
                    break;
                    
                case EX_SERVICE_SPECIFIC:
                    ALOGE("%s: Service error: %s", opName, 
                          status.getDescription().c_str());
                    break;
                    
                default:
                    ALOGE("%s: Unknown error (code %d): %s", 
                          opName, status.getExceptionCode(),
                          status.getDescription().c_str());
            }
            
            return false;
            
        } catch (const std::exception& e) {
            ALOGE("%s: Exception: %s", opName, e.what());
            return false;
        }
    }
    
public:
    bool reboot() {
        return callSafely([this]() { return mService->reboot(); }, 
                         "reboot");
    }
    
    bool rebootWithReason(const std::string& reason) {
        if (getServerVersion() < 2) {
            ALOGW("rebootWithReason requires v2+, using basic reboot");
            return reboot();
        }
        
        return callSafely(
            [this, &reason]() { return mService->rebootWithReason(reason); },
            "rebootWithReason"
        );
    }
};
```

### Pattern 8: Retry with Degradation

```cpp
void PersistentClient::performOperation() {
    const int MAX_RETRIES = 3;
    
    for (int attempt = 0; attempt < MAX_RETRIES; attempt++) {
        // Try newest method first
        if (getServerVersion() >= 3) {
            auto status = mService->newMethod();
            if (status.isOk()) {
                return;
            }
            
            // If unsupported, downgrade permanently
            if (status.getExceptionCode() == EX_UNSUPPORTED_OPERATION) {
                ALOGW("newMethod not supported, downgrading client version assumption");
                mServerVersion = 2;  // Force downgrade
                continue;
            }
            
            // Transient error? Retry
            if (attempt < MAX_RETRIES - 1) {
                ALOGW("Attempt %d failed, retrying...", attempt + 1);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
        }
        
        // Fallback to older method
        if (getServerVersion() >= 1) {
            mService->oldMethod();
            return;
        }
    }
    
    ALOGE("All attempts failed");
}
```

## Multi-Version Support

### Pattern 9: Support Multiple Server Versions

```cpp
class UniversalClient {
private:
    std::shared_ptr<IBoot> mService;
    int32_t mServerVersion;
    
    enum class RebootMethod {
        BASIC,           // v1
        WITH_REASON,     // v2
        WITH_OPTIONS,    // v3
    };
    
    RebootMethod selectRebootMethod(const RebootRequest& request) {
        if (mServerVersion >= 3 && request.hasOptions()) {
            return RebootMethod::WITH_OPTIONS;
        }
        if (mServerVersion >= 2 && !request.reason.empty()) {
            return RebootMethod::WITH_REASON;
        }
        return RebootMethod::BASIC;
    }
    
public:
    void reboot(const RebootRequest& request) {
        switch (selectRebootMethod(request)) {
            case RebootMethod::WITH_OPTIONS:
                ALOGI("Using v3 rebootWithOptions");
                mService->rebootWithOptions(request.toOptions());
                break;
                
            case RebootMethod::WITH_REASON:
                ALOGI("Using v2 rebootWithReason");
                mService->rebootWithReason(request.reason);
                break;
                
            case RebootMethod::BASIC:
                ALOGI("Using v1 basic reboot");
                mService->reboot();
                break;
        }
    }
};
```

### Pattern 10: Version-Specific Behavior

```cpp
class AdaptiveClient {
public:
    void initialize() {
        int32_t version = getServerVersion();
        
        switch (version) {
            case 1:
                ALOGI("Connected to v1 server - basic features only");
                initializeV1Features();
                break;
                
            case 2:
                ALOGI("Connected to v2 server - enhanced features available");
                initializeV1Features();
                initializeV2Features();
                break;
                
            case 3:
                ALOGI("Connected to v3 server - all features available");
                initializeV1Features();
                initializeV2Features();
                initializeV3Features();
                break;
                
            default:
                ALOGW("Unknown server version %d, assuming v1", version);
                initializeV1Features();
                break;
        }
    }
    
private:
    void initializeV1Features() {
        // Register callbacks, set up basic functionality
    }
    
    void initializeV2Features() {
        // Enable enhanced features
    }
    
    void initializeV3Features() {
        // Enable latest features
    }
};
```

## Testing Client Code

### Unit Test Example

```cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockBoot : public IBoot {
public:
    MOCK_METHOD(Status, reboot, (), (override));
    MOCK_METHOD(Status, rebootWithReason, (const std::string&), (override));
    MOCK_METHOD(Status, getInterfaceVersion, (int32_t*), (override));
};

TEST(BootClientTest, HandlesVersionMismatch) {
    auto mockService = std::make_shared<MockBoot>();
    
    // Simulate v1 server (no rebootWithReason)
    EXPECT_CALL(*mockService, getInterfaceVersion(testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgPointee<0>(1),
            testing::Return(Status::ok())
        ));
    
    // Client requests v2 feature
    EXPECT_CALL(*mockService, reboot())
        .WillOnce(testing::Return(Status::ok()));
    
    BootClient client(mockService);
    client.rebootWithReason("test");  // Should fall back to reboot()
}

TEST(BootClientTest, UsesV2WhenAvailable) {
    auto mockService = std::make_shared<MockBoot>();
    
    // Simulate v2 server
    EXPECT_CALL(*mockService, getInterfaceVersion(testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgPointee<0>(2),
            testing::Return(Status::ok())
        ));
    
    EXPECT_CALL(*mockService, rebootWithReason("test"))
        .WillOnce(testing::Return(Status::ok()));
    
    BootClient client(mockService);
    client.rebootWithReason("test");  // Should use v2 method
}
```

## Best Practices

### DO:
- ✅ Check server version at connection time
- ✅ Cache version information to avoid repeated calls
- ✅ Provide fallback behavior for older servers
- ✅ Log version mismatches for debugging
- ✅ Handle `EX_UNSUPPORTED_OPERATION` gracefully
- ✅ Test with multiple server versions
- ✅ Document minimum required version in your code

### DON'T:
- ❌ Assume server supports latest features
- ❌ Fail hard on version mismatch
- ❌ Call version methods repeatedly (they won't change)
- ❌ Ignore error codes
- ❌ Use v2+ features without checking version
- ❌ Crash on unsupported operations

## Quick Reference

```cpp
// Get service
auto service = IBoot::fromBinder(binder);

// Check version
int32_t serverVer;
service->getInterfaceVersion(&serverVer);

// Check hash
std::string hash;
service->getInterfaceHash(&hash);

// Compile-time version
int32_t clientVer = IBoot::VERSION;

// Use feature with version check
if (serverVer >= 2) {
    service->newMethod();
} else {
    service->oldMethod();  // Fallback
}

// Handle errors
auto status = service->someMethod();
if (!status.isOk()) {
    switch (status.getExceptionCode()) {
        case EX_UNSUPPORTED_OPERATION:
            // Method not supported
            break;
        case EX_ILLEGAL_ARGUMENT:
            // Invalid argument
            break;
        // ... handle other cases
    }
}
```

## References

- **Versioning Guide:** [versioning-guide.md](versioning-guide.md)
- **Migration Guide:** [migration-guide.md](migration-guide.md)
- **Example Clients:** [examples/aidl_versioning/clients/](../../examples/aidl_versioning/clients/)
- **Android Binder:** [Android Binder Overview](https://source.android.com/docs/core/architecture/aidl)
