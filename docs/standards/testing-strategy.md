# AIDL Interface Testing Strategy

## Overview

This document provides practical guidance for writing version-adaptive L1/L2 tests using the ut-core framework. The goal is to ensure the **latest test suite** works correctly with **any server version** (v1, v2, latest), validating both full functionality on current servers and graceful fallback behavior on older servers.

## Key Requirements

1. **Version Adaptation**: Single test binary must adapt behavior based on server version detected at runtime
2. **Client-Like Fallback**: Tests mirror production client fallback patterns (try v2 → catch exception → fall back to v1)
3. **Platform Independence**: Tests work with any platform via external YAML profiles specifying `platform_caps`
4. **HFP Validation**: Tests validate capability consistency: `platform_caps ⊆ runtime_caps ⊆ HFP_max_caps`

## Testing Levels

This document focuses on **L1 (Function Testing)** and **L2 (Unit Testing)**:

- **L1**: Test individual API functions with various input parameters
- **L2**: Test module-level behavior, state machines, and capability interactions
- **L3/L4**: Component stimulus and system interface testing (platform-specific, out of scope)

Both L1 and L2 tests are typically combined in a single monolithic test binary using ut-core's suite organization and menu system.

---

## Suite-Level Version Discovery

Tests use ut-core's suite initialization to discover and cache server version once, making it available to all tests in the suite.

### Basic Pattern

```cpp
// boot_tests.cpp
#include <ut.h>
#include <aidl/com/rdk/hal/boot/IBoot.h>

using namespace aidl::com::rdk::hal::boot;

// Suite-level context
struct BootTestContext {
    std::shared_ptr<IBoot> bootService;
    int32_t serverVersion;
    std::string serverHash;
};

static BootTestContext* gContext = nullptr;

// Suite initialization - called once before all tests
void boot_test_suite_init(void) {
    gContext = new BootTestContext();
    
    // Connect to Boot service
    const std::string serviceName = std::string() + IBoot::descriptor + "/default";
    auto bootService = IBoot::fromBinder(
        ndk::SpAIBinder(AServiceManager_checkService(serviceName.c_str())));
    
    UT_ASSERT_NOT_NULL(bootService.get());
    gContext->bootService = bootService;
    
    // Discover version ONCE at suite level
    auto status = bootService->getInterfaceVersion(&gContext->serverVersion);
    UT_ASSERT_TRUE(status.isOk());
    UT_LOG_INFO("Server version: %d", gContext->serverVersion);
    
    // Get hash for integrity check (see client-patterns.md Pattern 1)
    status = bootService->getInterfaceHash(&gContext->serverHash);
    UT_ASSERT_TRUE(status.isOk());
    UT_LOG_INFO("Server hash: %s", gContext->serverHash.c_str());
}

// Suite cleanup
void boot_test_suite_cleanup(void) {
    delete gContext;
    gContext = nullptr;
}
```

**Key Points:**
- Version queried **once** at suite initialization via `getInterfaceVersion()`
- Hash queried for integrity validation (detects ABI mismatches)
- Stored in suite context accessible to all tests
- See [client-patterns.md](client-patterns.md) Pattern 1 for version discovery rationale

---

## Client-Like Fallback in Tests

Tests must mirror production client behavior: attempt newest API first, catch exceptions, fall back to older equivalent. This validates both the test logic AND the server's backward compatibility.

### Try-Catch Fallback Pattern

```cpp
// L1 Function Test: reboot with reason (v2) falls back to basic reboot (v1)
void test_l1_reboot_with_fallback(void) {
    UT_LOG_INFO("Testing reboot with version fallback");
    
    bool rebooted = false;
    
    if (gContext->serverVersion >= 2) {
        // Try v2 method: reboot with reason
        UT_LOG_INFO("Attempting v2 rebootWithReason()");
        auto status = gContext->bootService->rebootWithReason(RebootReason::SOFTWARE_UPDATE);
        
        if (status.isOk()) {
            UT_LOG_INFO("✓ v2 rebootWithReason succeeded");
            rebooted = true;
        } else if (status.getExceptionCode() == EX_UNSUPPORTED_OPERATION) {
            UT_LOG_WARNING("v2 method unsupported, falling back to v1");
            // Fall through to v1 fallback
        } else {
            UT_FAIL("Unexpected error from rebootWithReason");
        }
    }
    
    // Fallback to v1 basic reboot
    if (!rebooted) {
        UT_LOG_INFO("Using v1 reboot()");
        auto status = gContext->bootService->reboot();
        UT_ASSERT_TRUE(status.isOk());
        UT_LOG_INFO("✓ v1 reboot succeeded");
    }
    
    UT_PASS("Reboot succeeded with appropriate method for server version");
}
```

**Fallback Logic:**
1. Check cached `serverVersion` to know if v2 methods exist
2. Attempt v2 method first (if version supports it)
3. Catch `EX_UNSUPPORTED_OPERATION` → indicates server doesn't support feature
4. Fall back to v1 equivalent method
5. Validate v1 method always works (backward compatibility guarantee)

This pattern matches [client-patterns.md](client-patterns.md) Pattern 3 (Try-Catch with Fallback).

### Progressive Enhancement Pattern

```cpp
// L2 Unit Test: get boot details with progressive enhancement
void test_l2_boot_details_progressive(void) {
    UT_LOG_INFO("Testing boot details with progressive enhancement");
    
    BootDetails details;
    
    if (gContext->serverVersion >= 3) {
        // Try v3: detailed boot info with timestamps
        auto status = gContext->bootService->getBootDetailsV3(&details);
        if (status.isOk()) {
            UT_LOG_INFO("✓ Got v3 boot details with timestamps");
            UT_ASSERT_NOT_EQUAL(details.bootTimestamp, 0);
            UT_ASSERT_NOT_EQUAL(details.lastShutdownTimestamp, 0);
            return;
        }
    }
    
    if (gContext->serverVersion >= 2) {
        // Try v2: boot details with count
        BootDetailsV2 detailsV2;
        auto status = gContext->bootService->getBootDetailsV2(&detailsV2);
        if (status.isOk()) {
            UT_LOG_INFO("✓ Got v2 boot details with count");
            UT_ASSERT_GE(detailsV2.bootCount, 0);
            return;
        }
    }
    
    // Fall back to v1: basic boot state
    State state;
    auto status = gContext->bootService->getState(&state);
    UT_ASSERT_TRUE(status.isOk());
    UT_LOG_INFO("✓ Got v1 boot state: %d", static_cast<int>(state));
    
    UT_PASS("Boot details retrieved using best available API");
}
```

**Progressive Enhancement:**
- Always try newest API first (v3 → v2 → v1)
- Gracefully degrade through version chain
- Matches [client-patterns.md](client-patterns.md) Pattern 6

### Version-Conditional Test Execution

```cpp
// L1 Function Test: secure boot (v2+ only)
void test_l1_secure_boot_version_conditional(void) {
    UT_LOG_INFO("Testing secure boot (v2+ feature)");
    
    if (gContext->serverVersion < 2) {
        UT_LOG_INFO("Skipping secure boot test - requires v2+ (server is v%d)",
                    gContext->serverVersion);
        UT_PASS("Test skipped appropriately for server version");
        return;
    }
    
    // v2+ test: check secure boot status
    bool isSecure = false;
    auto status = gContext->bootService->isSecureBootEnabled(&isSecure);
    UT_ASSERT_TRUE(status.isOk());
    
    UT_LOG_INFO("Secure boot enabled: %s", isSecure ? "YES" : "NO");
    UT_PASS("Secure boot query succeeded");
}
```

**Conditional Execution:**
- Check `serverVersion` before attempting version-specific API
- Skip test with clear log message if server doesn't support feature
- Pass test (not fail) when skipped due to version

### Platform Capability Integration

```cpp
// L2 Unit Test: watchdog capabilities from external profile
void test_l2_watchdog_with_platform_caps(void) {
    UT_LOG_INFO("Testing watchdog with platform capabilities");
    
    // Get runtime capabilities from server
    Capabilities caps;
    auto status = gContext->bootService->getCapabilities(&caps);
    UT_ASSERT_TRUE(status.isOk());
    
    // Read platform capabilities from external YAML profile
    bool platformSupportsWatchdog = 
        UT_KVP_PROFILE_GET_BOOL("boot/platform_caps/supportsWatchdog");
    
    UT_LOG_INFO("Server reports watchdog: %s", 
                caps.supportsWatchdog ? "YES" : "NO");
    UT_LOG_INFO("Platform supports watchdog: %s",
                platformSupportsWatchdog ? "YES" : "NO");
    
    // Validate relationship: platform_caps ⊆ runtime_caps
    if (platformSupportsWatchdog) {
        UT_ASSERT_TRUE(caps.supportsWatchdog);
        UT_LOG_INFO("✓ Platform capability present in runtime capabilities");
    } else {
        UT_LOG_INFO("Platform does not support watchdog - runtime state: %s",
                    caps.supportsWatchdog ? "ENABLED (unexpected)" : "DISABLED (expected)");
    }
    
    // If both platform and runtime support watchdog, test the API
    if (platformSupportsWatchdog && caps.supportsWatchdog) {
        if (gContext->serverVersion >= 2) {
            // Try v2 watchdog API
            int32_t timeout = 30;
            status = gContext->bootService->configureWatchdog(timeout);
            UT_ASSERT_TRUE(status.isOk());
            UT_LOG_INFO("✓ Watchdog configured with %d second timeout", timeout);
        } else {
            UT_LOG_INFO("v1 server - watchdog configuration not available in this version");
        }
    }
    
    UT_PASS("Watchdog capabilities validated across platform/runtime/version");
}
```

**Capability Layers:**

1. **Interface Version Capabilities**: What APIs exist in the version (v1: basic, v2: watchdog, secure boot)
2. **Runtime Capabilities**: What the server implementation supports (`getCapabilities()`)
3. **Platform Capabilities**: What the hardware supports (external YAML profile `platform_caps`)

**Validation Relationship:**
```
platform_caps ⊆ runtime_caps ⊆ version_max_caps ⊆ HFP_max_caps
```

### Combining Version and Capability Checks

```cpp
// L2 Unit Test: comprehensive version + capability adaptation
void test_l2_boot_with_full_adaptation(void) {
    UT_LOG_INFO("Testing boot with version and capability adaptation");
    
    // Get runtime capabilities
    Capabilities caps;
    auto status = gContext->bootService->getCapabilities(&caps);
    UT_ASSERT_TRUE(status.isOk());
    
    // Read platform capabilities
    bool platformHasSecureBoot = 
        UT_KVP_PROFILE_GET_BOOL("boot/platform_caps/supportsSecureBoot");
    
    UT_LOG_INFO("Server version: v%d", gContext->serverVersion);
    UT_LOG_INFO("Runtime caps - secureBoot: %s, watchdog: %s",
                caps.supportsSecureBoot ? "YES" : "NO",
                caps.supportsWatchdog ? "YES" : "NO");
    UT_LOG_INFO("Platform caps - secureBoot: %s",
                platformHasSecureBoot ? "YES" : "NO");
    
    // Test 1: Version check for API availability
    bool apiSupportsSecureBoot = (gContext->serverVersion >= 2);
    UT_LOG_INFO("API supports secure boot: %s", 
                apiSupportsSecureBoot ? "YES (v2+)" : "NO (v1)");
    
    // Test 2: Validate capability consistency
    if (caps.supportsSecureBoot) {
        // Runtime claims support → API must have the methods
        UT_ASSERT_TRUE(apiSupportsSecureBoot);
        UT_LOG_INFO("✓ Runtime capability consistent with API version");
        
        // Platform must support it
        UT_ASSERT_TRUE(platformHasSecureBoot);
        UT_LOG_INFO("✓ Runtime capability consistent with platform");
    }
    
    // Test 3: Attempt secure boot if all layers support it
    if (apiSupportsSecureBoot && caps.supportsSecureBoot && platformHasSecureBoot) {
        bool isSecure;
        status = gContext->bootService->isSecureBootEnabled(&isSecure);
        UT_ASSERT_TRUE(status.isOk());
        UT_LOG_INFO("✓ Secure boot query succeeded: %s", 
                    isSecure ? "ENABLED" : "DISABLED");
    } else {
        UT_LOG_INFO("Secure boot not fully supported - test adapted accordingly");
    }
    
    UT_PASS("Boot tested with full version+capability adaptation");
}
```

---

## HFP Validation

Tests must validate that runtime capabilities respect the maximum capabilities defined in the HAL Feature Profile (HFP).

### HFP Parsing Utility

```cpp
// Utility function to parse HFP YAML
#include <yaml-cpp/yaml.h>
#include <set>
#include <string>

struct HFPCapabilities {
    std::set<std::string> supportedFeatures;
    std::string interfaceVersion;
};

HFPCapabilities parseBootHFP(const std::string& hfpPath) {
    HFPCapabilities hfp;
    
    YAML::Node config = YAML::LoadFile(hfpPath);
    YAML::Node bootConfig = config["Boot"];
    
    hfp.interfaceVersion = bootConfig["interfaceVersion"].as<std::string>();
    
    if (bootConfig["supportedFeatures"]) {
        for (const auto& feature : bootConfig["supportedFeatures"]) {
            hfp.supportedFeatures.insert(feature.as<std::string>());
        }
    }
    
    return hfp;
}
```

### HFP Validation Test

```cpp
// L2 Unit Test: validate runtime capabilities against HFP
void test_l2_capabilities_match_hfp(void) {
    UT_LOG_INFO("Validating runtime capabilities against HFP");
    
    // Parse HFP file
    std::string hfpPath = "../hfp-boot.yaml";  // Relative to test binary
    HFPCapabilities hfp = parseBootHFP(hfpPath);
    
    UT_LOG_INFO("HFP interface version: %s", hfp.interfaceVersion.c_str());
    UT_LOG_INFO("HFP supported features:");
    for (const auto& feature : hfp.supportedFeatures) {
        UT_LOG_INFO("  - %s", feature.c_str());
    }
    
    // Get runtime capabilities
    Capabilities caps;
    auto status = gContext->bootService->getCapabilities(&caps);
    UT_ASSERT_TRUE(status.isOk());
    
    // Build runtime feature set
    std::set<std::string> runtimeFeatures;
    if (caps.supportsWatchdog) runtimeFeatures.insert("WATCHDOG");
    if (caps.supportsSecureBoot) runtimeFeatures.insert("SECURE_BOOT");
    if (caps.supportsBootCount) runtimeFeatures.insert("BOOT_COUNT");
    if (caps.supportsRebootReason) runtimeFeatures.insert("REBOOT_REASON");
    
    UT_LOG_INFO("Runtime capabilities:");
    for (const auto& feature : runtimeFeatures) {
        UT_LOG_INFO("  - %s", feature.c_str());
    }
    
    // Validation: runtime_caps ⊆ HFP_max_caps
    for (const auto& feature : runtimeFeatures) {
        bool inHFP = hfp.supportedFeatures.count(feature) > 0;
        UT_ASSERT_TRUE(inHFP);
        if (inHFP) {
            UT_LOG_INFO("✓ %s is in HFP", feature.c_str());
        } else {
            UT_LOG_ERROR("✗ %s NOT in HFP (violation!)", feature.c_str());
        }
    }
    
    // Note: HFP may list more features than runtime provides
    // (runtime is platform-specific subset)
    if (runtimeFeatures.size() < hfp.supportedFeatures.size()) {
        UT_LOG_INFO("Runtime provides %zu of %zu HFP features (platform-specific)",
                    runtimeFeatures.size(), hfp.supportedFeatures.size());
    }
    
    UT_PASS("Runtime capabilities validated against HFP");
}
```

**HFP Validation Rules:**

1. **Runtime ⊆ HFP**: Every runtime capability must be in HFP (strict subset)
2. **Platform ⊆ Runtime**: External profile capabilities ⊆ runtime capabilities
3. **Version Consistency**: HFP version should match or be compatible with server version

---

## Multi-Version Test Execution

The same test binary must validate behavior against different server versions. This ensures the **latest tests** work correctly with **all server versions**.

### Test Execution Matrix

```
                          Server Version
                    v1         v2         latest (v3)
Latest Test     ┌─────────┬─────────┬─────────────┐
Binary          │ Fallback│ Full v2 │ Full v3     │
                │ to v1   │ features│ features    │
                │ APIs    │ + v1    │ + v2 + v1   │
                └─────────┴─────────┴─────────────┘
```

### Execution Workflow

```bash
#!/bin/bash
# test_all_versions.sh - Run latest tests against all server versions

MODULE="boot"
TEST_BINARY="./build/boot_tests"
PROFILE_DIR="../profiles"

echo "Running latest $MODULE tests against all server versions"

# Test 1: Against v1 server
echo ""
echo "========================================"
echo "TEST 1: Latest tests vs v1 server"
echo "========================================"
# Start v1 server (or connect to existing v1 service)
# Run tests - expect fallback behavior
$TEST_BINARY -p $PROFILE_DIR/platform_minimal.yml
echo "✓ v1 server tests completed"

# Test 2: Against v2 server
echo ""
echo "========================================"
echo "TEST 2: Latest tests vs v2 server"
echo "========================================"
# Start v2 server (or connect to existing v2 service)
# Run tests - expect full v2 + v1 functionality
$TEST_BINARY -p $PROFILE_DIR/platform_standard.yml
echo "✓ v2 server tests completed"

# Test 3: Against latest (development) server
echo ""
echo "========================================"
echo "TEST 3: Latest tests vs latest server"
echo "========================================"
# Start latest server
# Run tests - expect full functionality
$TEST_BINARY -p $PROFILE_DIR/platform_full.yml
echo "✓ latest server tests completed"

echo ""
echo "========================================"
echo "✅ All multi-version tests passed"
echo "========================================"
```

### Expected Behavior by Server Version

**Testing against v1 server:**

- ✓ All v1 API tests pass
- ⚠ v2+ API tests skip with "requires v2+" message
- ✓ Fallback tests pass (attempt v2 → fall back to v1)
- ⚠ v2+ capability tests skip if `platform_caps` includes v2 features

**Testing against v2 server:**

- ✓ All v1 API tests pass (backward compatibility)
- ✓ All v2 API tests pass
- ✓ Fallback tests pass (v2 API succeeds, no fallback needed)
- ✓ v2 capability tests pass if `platform_caps` supports them

**Testing against latest (v3) server:**

- ✓ All v1, v2, v3 API tests pass
- ✓ All fallback chains work (v3→v2→v1)
- ✓ Latest capability tests pass

---

## Test Suite Organization

Using ut-core's suite and menu system for monolithic L1/L2 test organization.

### Suite Structure

```cpp
// boot_tests.cpp - Single monolithic test binary
#include <ut.h>

// Forward declarations
void boot_test_suite_init(void);
void boot_test_suite_cleanup(void);

// L1 Function Tests
void test_l1_initialize(void);
void test_l1_get_state(void);
void test_l1_reboot(void);
void test_l1_reboot_with_fallback(void);
void test_l1_secure_boot_version_conditional(void);

// L2 Unit Tests
void test_l2_capabilities_basic(void);
void test_l2_capabilities_match_hfp(void);
void test_l2_watchdog_with_platform_caps(void);
void test_l2_boot_with_full_adaptation(void);
void test_l2_boot_details_progressive(void);

int main(int argc, char** argv) {
    // Initialize ut-core
    UT_init(argc, argv);
    
    // Register L1 suite
    UT_add_suite("Boot L1 Function Tests", boot_test_suite_init, boot_test_suite_cleanup);
    UT_add_test("Initialize", test_l1_initialize);
    UT_add_test("Get State", test_l1_get_state);
    UT_add_test("Reboot", test_l1_reboot);
    UT_add_test("Reboot with Version Fallback", test_l1_reboot_with_fallback);
    UT_add_test("Secure Boot (v2+)", test_l1_secure_boot_version_conditional);
    
    // Register L2 suite
    UT_add_suite("Boot L2 Unit Tests", NULL, NULL);
    UT_add_test("Capabilities Basic", test_l2_capabilities_basic);
    UT_add_test("Capabilities vs HFP", test_l2_capabilities_match_hfp);
    UT_add_test("Watchdog with Platform Caps", test_l2_watchdog_with_platform_caps);
    UT_add_test("Full Version+Capability Adaptation", test_l2_boot_with_full_adaptation);
    UT_add_test("Boot Details Progressive Enhancement", test_l2_boot_details_progressive);
    
    // Run tests (supports ut-core menu, selective execution)
    return UT_run_tests();
}
```

### ut-core Test Execution

```bash
# Run all tests
./boot_tests -p platform_profile.yml

# Run specific suite via menu (interactive)
./boot_tests -p platform_profile.yml
# Menu appears:
# 1. Boot L1 Function Tests
# 2. Boot L2 Unit Tests
# 3. Run All
# Select: 1

# Run specific test
./boot_tests -p platform_profile.yml -t "Reboot with Version Fallback"

# Run all L1 tests
./boot_tests -p platform_profile.yml -s "Boot L1 Function Tests"

# Verbose logging
./boot_tests -p platform_profile.yml -l 5
```

**ut-core Benefits:**

- Menu-driven test selection
- YAML profile integration via `-p` flag
- Suite-level initialization (version discovery once)
- Selective test execution without recompilation

---

## External YAML Profile Schema

Platform-specific capabilities passed to tests via external YAML profiles (location hidden/platform-specific).

### Profile Structure

```yaml
# platform_full.yml - Full-featured platform
boot:
  platform_caps:
    supportsWatchdog: true
    supportsSecureBoot: true
    supportsBootCount: true
    supportsRebootReason: true
    hardwareWatchdogPresent: true

videodecoder:
  platform_caps:
    maxDecoders: 4
    supportsHEVC: true
    supports4K: true
    supportsHDR: true

# Other module capabilities...
```

```yaml
# platform_minimal.yml - Minimal platform
boot:
  platform_caps:
    supportsWatchdog: false
    supportsSecureBoot: false
    supportsBootCount: false
    supportsRebootReason: false
    hardwareWatchdogPresent: false

videodecoder:
  platform_caps:
    maxDecoders: 1
    supportsHEVC: false
    supports4K: false
    supportsHDR: false
```

### Profile Access in Tests

```cpp
// Read boolean capability
bool hasWatchdog = UT_KVP_PROFILE_GET_BOOL("boot/platform_caps/supportsWatchdog");

// Read integer capability
int maxDecoders = UT_KVP_PROFILE_GET_UINT32("videodecoder/platform_caps/maxDecoders");

// Read string capability
const char* hwRevision = UT_KVP_PROFILE_GET_STRING("boot/platform_caps/hardwareRevision");

// Check if key exists
if (UT_KVP_PROFILE_HAS_KEY("boot/platform_caps/supportsSecureBoot")) {
    // Key present - read value
}
```

**Profile Guidelines:**

- Profiles specify `platform_caps` (hardware), NOT interface version
- Interface version discovered at runtime via `getInterfaceVersion()`
- Tests combine both: `if (version >= 2 && platform_caps.supports*) { test }`
- Profiles are **external** (not in VTS repo), passed at test execution

---

## Architecture Decisions

### Decision 1: Single vs Multiple Test Binaries

**Option A: Single Test Binary (Recommended)**

**Pros:**

- Simpler build: one CMakeLists.txt, one binary
- Easier maintenance: all tests in one place
- Matches monolithic suite philosophy
- ut-core menu handles test organization
- Tests adapt to any server version automatically
- Validates "latest tests work with all versions" requirement

**Cons:**

- Links against latest library version only
- Cannot test frozen version behavior independently
- Larger binary size (all test code included)

**Option B: Multiple Test Binaries (per version)**

**Pros:**

- Each binary links to specific library version (boot-v1-cpp, boot-v2-cpp)
- Can test exact frozen version behavior
- Aligns with freeze_interface.sh workflow (snapshot tests with interface)
- Smaller per-binary size

**Cons:**

- More complex build: separate CMakeLists.txt per version
- Duplicate test code across binaries
- Must maintain multiple binaries as versions grow
- Harder to ensure test consistency across versions

**Recommendation:** Use **Option A (Single Binary)** for most modules:

- Latest tests validate backward compatibility (primary goal)
- Single binary easier to maintain
- Version adaptation in test code matches production client patterns
- ut-core menu provides organization without binary proliferation

Use **Option B** only if:

- Need to validate exact frozen version snapshot behavior
- Module has complex version-specific state machines
- Regression testing requires bit-exact version behavior

---

### Decision 2: Capability Test Organization

**Option A: Separate L2 Suite for Capabilities**

**Pros:**

- Clean separation: L1 tests functions, L2 tests capabilities
- Easy to run capability validation independently
- Matches documentation structure (L1 vs L2)
- Clear test organization in ut-core menu

**Cons:**

- Capability checks separated from functional tests
- May duplicate version checks across suites
- Deeper menu hierarchy

**Option B: Integrate Capabilities into L1 Functional Tests**

**Pros:**

- Test function + capability together (more realistic)
- Single version check per test function
- Shallower menu structure
- Less test code duplication

**Cons:**

- Mixes functional and capability validation concerns
- Harder to run "capability validation only"
- L1/L2 distinction less clear

**Recommendation:** Use **Option A (Separate L2 Suite)** for clarity:

- Matches RDK testing level definitions
- Easier to validate HFP independently
- Can run capability validation without functional tests
- Better aligns with documentation structure

Compromise: Include basic capability checks in L1 tests, comprehensive validation in L2:

```cpp
// L1: Basic capability check before using feature
void test_l1_watchdog_basic(void) {
    Capabilities caps;
    gContext->bootService->getCapabilities(&caps);
    
    if (!caps.supportsWatchdog) {
        UT_LOG_INFO("Watchdog not supported - test skipped");
        return;
    }
    
    // Test watchdog functional behavior
    // ...
}

// L2: Comprehensive capability validation
void test_l2_capabilities_match_hfp(void) {
    // Parse HFP, validate runtime ⊆ HFP, check platform consistency
    // ...
}
```

---

## CMake Build Integration

### Linking Test Binary

```cmake
# boot/current/tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(boot_tests)

# Find ut-core
find_package(ut-core REQUIRED)

# Find YAML parser for HFP validation
find_package(yaml-cpp REQUIRED)

# Test binary
add_executable(boot_tests
    boot_tests.cpp
    hfp_parser.cpp
)

# Link against latest Boot library (for version adaptation testing)
target_link_libraries(boot_tests
    boot-vcurrent-cpp  # Latest version from stable/generated/boot/current/
    ut-core::ut-core
    yaml-cpp
    binder_ndk
)

# Include AIDL generated headers
target_include_directories(boot_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/stable/generated/boot/current/include
)

# Install test binary
install(TARGETS boot_tests
    RUNTIME DESTINATION bin/tests
)

# Copy HFP file for runtime access
install(FILES
    ${CMAKE_SOURCE_DIR}/boot/current/hfp-boot.yaml
    DESTINATION share/tests/boot
)
```

### Building Tests

```bash
# From workspace root
cd boot/current/tests
mkdir build && cd build

# Configure
cmake ..

# Build
make

# Run tests (with external profile)
./boot_tests -p /path/to/platform_profile.yml
```

---

## Complete Example

### Full Test Implementation

See example implementation structure:

```text
boot/
├── current/
│   ├── hfp-boot.yaml
│   ├── com/rdk/hal/boot/
│   │   ├── IBoot.aidl
│   │   └── Capabilities.aidl
│   └── tests/
│       ├── CMakeLists.txt
│       ├── boot_tests.cpp          # Main test binary (shown above)
│       ├── hfp_parser.cpp          # HFP parsing utility
│       ├── hfp_parser.h
│       └── README.md               # Test execution guide
└── 1/  # Frozen v1 (optional: snapshot tests)

│   └── tests/
│       ├── CMakeLists.txt
│       ├── boot_tests.cpp          # Main test binary (shown above)
│       ├── hfp_parser.cpp          # HFP parsing utility
│       ├── hfp_parser.h
│       └── README.md               # Test execution guide
└── 1/  # Frozen v1 (optional: snapshot tests)
```

### Sample Test Output

```text
$ ./boot_tests -p platform_full.yml

================================================
UT Framework - Boot HAL Tests
================================================
Server version: v2
Server hash: abc123...
Platform profile: platform_full.yml

Test Suite: Boot L1 Function Tests
  [PASS] Initialize
  [PASS] Get State
  [PASS] Reboot
  [PASS] Reboot with Version Fallback (used v2 API)
  [PASS] Secure Boot (v2+)

Test Suite: Boot L2 Unit Tests
  [PASS] Capabilities Basic
  [PASS] Capabilities vs HFP (5/6 features supported)
  [PASS] Watchdog with Platform Caps
  [PASS] Full Version+Capability Adaptation
  [PASS] Boot Details Progressive Enhancement (v2 API)

================================================
Results: 10 tests, 10 passed, 0 failed, 0 skipped
================================================
```

---

## Best Practices

### Version Discovery

- **Do**: Check version once at suite level, cache result
- **Don't**: Query version in every test (slow, redundant)
- **Do**: Log server version at test start for debugging
- **Don't**: Hard-code version assumptions in test logic

### Fallback Implementation

- **Do**: Mirror production client fallback patterns
- **Don't**: Create test-only fallback mechanisms
- **Do**: Validate both success paths (latest API) and fallback paths (older API)
- **Don't**: Only test "happy path" with latest server

### Capability Testing

- **Do**: Validate `platform_caps ⊆ runtime_caps ⊆ HFP_max_caps`
- **Don't**: Assume runtime capabilities match HFP exactly
- **Do**: Test with multiple profile variants (minimal, standard, full)
- **Don't**: Hard-code capability assumptions

### Test Adaptation

- **Do**: Skip tests gracefully when version doesn't support feature
- **Don't**: Fail tests due to version limitations
- **Do**: Log clear messages when tests skip/adapt
- **Don't**: Silently skip without explanation

### ut-core Integration

- **Do**: Use `UT_KVP_PROFILE_GET_*()` for all platform-specific data
- **Don't**: Hard-code platform capabilities in test code
- **Do**: Leverage ut-core menu system for test organization
- **Don't**: Create separate binaries for test selection

---

## Summary

This testing strategy enables **version-adaptive L1/L2 testing** using ut-core framework:

1. **Suite-level version discovery**: Cache version once, use throughout tests
2. **Client-like fallback**: Tests mirror production client patterns (try v2 → fallback v1)
3. **Test adaptation**: Combine version checks + platform capabilities for intelligent test behavior
4. **HFP validation**: Validate capability consistency across API/runtime/platform layers
5. **Multi-version execution**: Same test binary validates all server versions
6. **Single monolithic binary**: ut-core menu provides organization without binary proliferation
7. **External profiles**: Platform-specific capabilities passed via YAML at runtime

**Key Validation:** Latest test suite works correctly with v1, v2, and latest servers through graceful adaptation.

---

## References

- [Versioning Guide](versioning-guide.md) - Interface versioning strategy and compatibility rules
- [Client Patterns](client-patterns.md) - Version discovery and graceful degradation patterns (referenced throughout)
- [Migration Guide](migration-guide.md) - Upgrading between interface versions
- [ut-core Documentation](https://github.com/rdkcentral/ut-core/wiki) - Testing framework reference
- [HFP Files](../../boot/current/hfp-boot.yaml) - HAL Feature Profile examples

---

**Document Version**: 1.0
**Last Updated**: 31 December 2025
**Applies To**: RDK HALIF AIDL v1.0+

