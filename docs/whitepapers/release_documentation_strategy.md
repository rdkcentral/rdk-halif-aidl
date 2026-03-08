# **White Paper: Release Documentation Strategy**

## **Executive Summary**

AIDL (Android Interface Definition Language) source files in this project contain rich Doxygen-style documentation: method descriptions, parameter annotations, return value specifications, and cross-references. However, Google's AIDL compiler **completely strips all comments** when generating C++ code. The generated headers that engineers actually include and call contain zero documentation.

This creates a fundamental problem: running Doxygen on the AIDL source files would document function signatures that nobody calls (AIDL signatures differ significantly from generated C++), and running Doxygen on the generated C++ headers produces empty references with no useful content.

This white paper proposes a **comment injection tool** (`aidl_comment_inject.py`) that, as part of the release workflow, re-injects AIDL Doxygen comments into the generated C++ headers. This enables:

- Engineers to see documentation in the headers they actually use.
- Doxygen to generate accurate API reference documentation from annotated C++ headers.
- Build-time validation to catch documentation drift before release.

---

## **1. The Documentation Gap**

### **1.1 AIDL Source: Rich Documentation**

The AIDL source files follow the project's Doxygen governance guidelines (see [Doxygen Code Documentation](doxygen_code_documentation.md)). For example, `boot/current/com/rdk/hal/boot/IBoot.aidl`:

```java
/**
 *  @brief     Boot HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
@VintfStability
interface IBoot
{
    /**
     * Performs a shutdown and warm reboot of the device.
     *
     * A number of reset types can be applied as part of the reboot process.
     * On success this function does not return.
     *
     * @param[in] resetType     ResetType value
     * @param[in] reasonString  Free-form reset reason string (64 bytes)
     */
    void reboot(in ResetType resetType, in String reasonString);
}
```

Enum types are similarly documented. From `boot/current/com/rdk/hal/boot/BootReason.aidl`:

```java
/**
 *  @brief     Boot reasons.
 */
@VintfStability
@Backing(type="int")
enum BootReason
{
    /** Boot Reason is unknown. */
    ERROR_UNKNOWN = -1,

    /** Boot Reason is due to Watchdog Timer. */
    WATCHDOG = 0,

    /** Boot Reason is due to Cold Boot. */
    COLD_BOOT = 4,
}
```

### **1.2 Generated C++: Zero Documentation**

The AIDL compiler (`aidl --lang=cpp`) generates C++ headers with no comments whatsoever. The generated `stable/generated/boot/current/include/com/rdk/hal/boot/IBoot.h`:

```cpp
class IBoot : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Boot)
  static const int32_t VERSION = 1;
  const std::string HASH = "80e31b1e4037b6988846f183be9c68c2f7427a3f";
  virtual ::android::binder::Status reboot(
      ::com::rdk::hal::boot::ResetType resetType,
      const ::android::String16& reasonString) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};
```

The generated `BootReason.h`:

```cpp
enum class BootReason : int32_t {
  ERROR_UNKNOWN = -1,
  WATCHDOG = 0,
  COLD_BOOT = 4,
};
```

All documentation is lost. Every method, every enum value, every field -- bare declarations only.

### **1.3 Signature Transformations**

The AIDL compiler also transforms signatures during code generation. Running Doxygen on the AIDL source would document signatures that don't match what engineers actually call:

| AIDL Source | Generated C++ |
|---|---|
| `Capabilities getCapabilities()` | `::android::binder::Status getCapabilities(::com::rdk::hal::boot::Capabilities* _aidl_return)` |
| `void setBootReason(in BootReason reason, in String reasonString)` | `::android::binder::Status setBootReason(::com::rdk::hal::boot::BootReason reason, const ::android::String16& reasonString)` |
| `BootReason getBootReason()` | `::android::binder::Status getBootReason(::com::rdk::hal::boot::BootReason* _aidl_return)` |

Key transformations:

- **Return types**: All methods return `::android::binder::Status`. Original return values become output pointer parameters.
- **String types**: AIDL `String` becomes `const ::android::String16&`.
- **Array types**: AIDL `BootReason[]` becomes `::std::vector<::com::rdk::hal::boot::BootReason>`.
- **Fully qualified names**: All types are fully namespace-qualified in generated code.

This means Doxygen output from AIDL source files would describe an API surface that does not exist in the actual C++ code engineers consume.

---

## **2. Comment Injection Tool**

### **2.1 Overview**

A standalone Python tool, `aidl_comment_inject.py`, will be placed alongside the existing AIDL tooling at `build-tools/linux_binder_idl/host/`. It performs two operations:

1. **Parse** AIDL source files to extract Doxygen comment blocks and associate them with their target declarations.
2. **Inject** those comments into the corresponding generated C++ header files, matching by declaration name.

### **2.2 AIDL Comment Parsing**

The parser extracts `/** ... */` Doxygen-style comment blocks (distinguished from `/* ... */` license headers by the double-asterisk opening). After each comment block, it skips blank lines and AIDL annotations (`@VintfStability`, `@Backing`, etc.) to find the next declaration.

Supported declaration types:

| AIDL Declaration | Example |
|---|---|
| Interface | `interface IBoot` |
| Parcelable | `parcelable Capabilities` |
| Enum | `enum BootReason` |
| Method | `void reboot(in ResetType resetType, in String reasonString)` |
| Parcelable field | `BootReason[] supportedBootReasons;` |
| Enum value | `WATCHDOG = 0,` |
| Constant | `const @utf8InCpp String serviceName = "Boot"` |

### **2.3 C++ Header Matching**

Names are identical between AIDL source and generated C++. The tool matches by **identifier name only** -- no type matching is required.

For each module, the tool processes generated headers in `stable/generated/{module}/{version}/include/`. It **skips**:

- `Bp*.h` files (binder proxy implementation)
- `Bn*.h` files (binder stub implementation)

These are internal binder machinery and not part of the public API surface. The tool targets:

- `I*.h` files (abstract interface declarations)
- Enum headers (e.g., `BootReason.h`)
- Parcelable headers (e.g., `Capabilities.h`)

### **2.4 Idempotency**

Injected comments are marked with a `@aidl-doc` sentinel tag on the opening line:

```cpp
/** @aidl-doc
 * Performs a shutdown and warm reboot of the device.
 * ...
 */
```

On subsequent runs, the tool detects existing `@aidl-doc` blocks above target declarations and replaces them rather than duplicating. This ensures the tool can be run repeatedly without accumulating duplicate comments.

### **2.5 CLI Interface**

```
python3 aidl_comment_inject.py \
    --aidl-root <path>           \  # Root containing {module}/current/ AIDL sources
    --generated-root <path>      \  # Root containing generated C++ (stable/generated/)
    [--module <name>]            \  # Specific module, or omit for all
    [--version <ver>]            \  # Version subdirectory (default: current)
    [--dry-run]                  \  # Preview changes without modifying files
    [--validate]                 \  # Check comment-to-target mapping; exit non-zero on mismatch
    [--verbose]                     # Detailed logging
```

### **2.6 Build-Time Validation**

The `--validate` flag enables the tool to be used during regular builds without modifying any files. It checks that every Doxygen comment in the AIDL source has a corresponding target in the generated C++ headers. If a comment references a method that no longer exists (e.g., after a rename), validation fails with a non-zero exit code.

This catches documentation drift early -- before it reaches the release process.

---

## **3. Release Workflow Integration**

### **3.1 The Release Pipeline**

Comment injection is designed as one step in the broader release pipeline. The full workflow:

```
1. Freeze Interface
   └── freeze_interface.sh <module>
   └── AIDL compiler freezes interface as integer version (v1, v2, ...)
   └── Frozen AIDL files stored in stable/aidl/{module}/{version}/

2. Generate C++ Code
   └── AIDL compiler generates C++ stubs/proxies/headers
   └── Output in stable/generated/{module}/{version}/

3. Inject Documentation                          <-- NEW STEP
   └── aidl_comment_inject.py
   └── AIDL Doxygen comments injected into generated C++ headers
   └── Headers now contain full API documentation

4. Generate API Reference
   └── Doxygen processes annotated C++ headers
   └── Produces HTML/PDF API reference documentation

5. Commit Release
   └── Frozen AIDL, generated C++, annotated headers, and docs all committed
   └── Both pre-AIDL (source) and post-AIDL (generated) directories versioned
```

### **3.2 Pre-AIDL and Post-AIDL Directory Structures**

The release produces two parallel directory structures, both versioned:

**Pre-AIDL (source)**:
```
boot/current/
  com/rdk/hal/boot/
    IBoot.aidl           # Source with Doxygen comments
    BootReason.aidl      # Source with Doxygen comments
    Capabilities.aidl    # Source with Doxygen comments
    interface.yaml       # Interface metadata
```

**Post-AIDL (generated + annotated)**:
```
stable/generated/boot/current/
  include/com/rdk/hal/boot/
    IBoot.h              # Generated C++ with injected Doxygen comments
    BpBoot.h             # Proxy (no comments injected)
    BnBoot.h             # Stub (no comments injected)
    BootReason.h         # Generated enum with injected comments
    Capabilities.h       # Generated parcelable with injected comments
  com/rdk/hal/boot/
    IBoot.cpp            # Generated implementation
    ...
```

### **3.3 Existing Precedent**

The build system already performs post-processing on generated C++ headers. In `build_interfaces.sh`, a step injects missing `#include <mutex>` directives into generated proxy headers that reference `std::mutex`. The comment injection tool follows the same pattern -- a post-generation fixup that addresses a gap in the AIDL compiler's output.

---

## **4. Versioning Scheme**

### **4.1 AIDL Integer Versions vs. Display Versions**

Google's AIDL compiler enforces integer-only versions. The generated C++ code exposes this via:

```cpp
static const int32_t VERSION = 1;          // Compile-time constant
virtual int32_t getInterfaceVersion() = 0; // Runtime query
```

The `getInterfaceVersion()` method returns `int32_t` -- it cannot represent sub-versions like `1.2`. This is a hard constraint of the binder protocol.

### **4.2 Composite Version Model**

To support documentation-only revisions without requiring a full interface freeze, the project adopts a composite version model:

```
0.MAJOR.MINOR.BUGFIX
```

Where:

- **0** -- Prefix indicating pre-1.0 development phase
- **MAJOR** -- Corresponds to the latest AIDL frozen version (0 if never frozen)
- **MINOR** -- Backward-compatible functional enhancements
- **BUGFIX** -- Bug fixes and documentation-only changes

### **4.3 Version Lifecycle**

| State | AIDL Frozen Version | Display Version |
|---|---|---|
| Initial development (unfrozen) | (none) | 0.0.0.0 |
| Documentation update | (none) | 0.0.0.1 |
| First interface freeze | 1 | 0.1.0.0 |
| Documentation update to v1 | 1 | 0.1.0.1 |
| Minor enhancement | 1 | 0.1.1.0 |
| Second interface freeze | 2 | 0.2.0.0 |

The AIDL compiler continues to use integer versions internally. The composite version is a **metadata layer** stored in `interface.yaml` and displayed in documentation and generated header comments.

For the full versioning philosophy, see [Interface Version Alignment](interface_version_alignment.md).

---

## **5. Before and After Examples**

### **5.1 Interface Header (IBoot.h)**

**Before injection:**

```cpp
class IBoot : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Boot)
  static const int32_t VERSION = 1;
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(
      ::com::rdk::hal::boot::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status reboot(
      ::com::rdk::hal::boot::ResetType resetType,
      const ::android::String16& reasonString) = 0;
};
```

**After injection:**

```cpp
/** @aidl-doc
 *  @brief     Boot HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IBoot : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Boot)
  static const int32_t VERSION = 1;
  /** @aidl-doc The service name to publish. */
  static const ::std::string& serviceName();
  /** @aidl-doc
   * Gets the capabilities of the boot service.
   *
   * @returns Capabilities parcelable.
   */
  virtual ::android::binder::Status getCapabilities(
      ::com::rdk::hal::boot::Capabilities* _aidl_return) = 0;
  /** @aidl-doc
   * Performs a shutdown and warm reboot of the device.
   *
   * A number of reset types can be applied as part of the reboot process.
   * On success this function does not return.
   *
   * @param[in] resetType     ResetType value
   * @param[in] reasonString  Free-form reset reason string (64 bytes)
   */
  virtual ::android::binder::Status reboot(
      ::com::rdk::hal::boot::ResetType resetType,
      const ::android::String16& reasonString) = 0;
};
```

### **5.2 Enum Header (BootReason.h)**

**Before injection:**

```cpp
enum class BootReason : int32_t {
  ERROR_UNKNOWN = -1,
  WATCHDOG = 0,
  MAINTENANCE_REBOOT = 1,
  COLD_BOOT = 4,
};
```

**After injection:**

```cpp
/** @aidl-doc
 *  @brief     Boot reasons.
 */
enum class BootReason : int32_t {
  /** @aidl-doc Boot Reason is unknown. */
  ERROR_UNKNOWN = -1,
  /** @aidl-doc Boot Reason is due to Watchdog Timer. */
  WATCHDOG = 0,
  /** @aidl-doc Boot Reason is due to Maintenance Reboot. */
  MAINTENANCE_REBOOT = 1,
  /** @aidl-doc Boot Reason is due to Cold Boot. */
  COLD_BOOT = 4,
};
```

### **5.3 Parcelable Header (Capabilities.h)**

**Before injection:**

```cpp
class Capabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::boot::BootReason> supportedBootReasons;
  ::std::vector<::com::rdk::hal::boot::ResetType> supportedResetTypes;
};
```

**After injection:**

```cpp
/** @aidl-doc
 *  @brief     Boot service capabilities definition.
 */
class Capabilities : public ::android::Parcelable {
public:
  /** @aidl-doc Array of boot reasons supported by the boot service. */
  ::std::vector<::com::rdk::hal::boot::BootReason> supportedBootReasons;
  /** @aidl-doc Array of reset types supported by the boot service. */
  ::std::vector<::com::rdk::hal::boot::ResetType> supportedResetTypes;
};
```

---

## **6. Conclusion**

The comment injection approach solves the documentation gap created by Google's AIDL compiler without modifying the compiler itself or diverging from the standard AIDL toolchain. By operating as a post-processing step in the release pipeline, it:

- Preserves the existing AIDL build workflow unchanged.
- Produces C++ headers that are both functionally correct and fully documented.
- Enables Doxygen to generate API references that match the actual C++ interface engineers consume.
- Provides build-time validation to prevent documentation from drifting out of sync with the interface.

The tool, the release workflow, and the composite versioning scheme together form a complete documentation strategy that scales across all HAL interface modules.

---

## **Version History**

| **Version** | **Date** | **Author** | **Comments** |
|---|---|---|---|
| Draft | 6th March 2026 | Gerald Weatherup | Initial whitepaper outlining release documentation strategy for AIDL-generated C++ interfaces. |
