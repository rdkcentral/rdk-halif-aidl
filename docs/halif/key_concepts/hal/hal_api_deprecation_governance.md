# **HAL API Evolution Governance Process**

## Document History

|Date|Author|Comments|
|----|------|--------|
|06 June 2025|G.Weatherup|Draft Revision|

## **Objective**

This document defines the governance process for managing the lifecycle of HAL APIs through evolution and eventual removal. It outlines how HAL API evolutions will be communicated, documented, validated, and executed in a controlled and visible manner. This ensures backward compatibility during transition periods, minimises risk, and provides clear guidance to engineering teams on the required steps and responsibilities throughout the evolution process.

## **Step 1: Soft Evolution**

### **Header Annotation**

* Move API declaration to a clearly marked **Deprecated APIs** section in the HAL header files.

* Use the Doxygen `@deprecated` tag with:

  * **Evolution date** (e.g. `@deprecated Deprecated since 2025-04-01`)
  * **Replacement API** if available (e.g. `Use NewHALAPI_DoTask() instead.`)
  * Example:

    ```c
    /**
     * @deprecated Deprecated since 2025-04-01. Use NewHALAPI_DoTask() instead.
     */
    void OldHALAPI_DoTask();
    ```

* This allows IDEs (such as VSCode) to highlight deprecated APIs automatically.

**Recommended VSCode extensions**:

* **Doxygen Documentation Generator**
* **Better C++ Syntax**
* **C/C++ (Microsoft)** (recognizes Doxygen tags)

### **Compiler Warning**

* In addition to Doxygen, wrap deprecated functions in a **deprecation macro** to trigger compiler warnings when the API is used in code.

* Example warning format:

  ```c
  WARNING: DEPRECATED FUNCTION <API> USED. Please migrate.
  ```

* This is achieved by adding a macro definition to a **common HAL header file** (typically `hal_common.h` or `platform_macros.h`):

```c
#ifndef DEPRECATED_API
   #define DEPRECATED_API(api) __attribute__((deprecated("WARNING: DEPRECATED FUNCTION " #api " USED.    Please migrate.")))
#endif
```

* Then annotate deprecated functions as follows:

  ```c
  DEPRECATED_API(OldHALAPI_DoTask)
  void OldHALAPI_DoTask();
  ```

* When compiled with GCC or Clang, this will generate a compiler warning each time `OldHALAPI_DoTask()` is used.
* Works with GCC 4.5+ and Clang.
* The `#ifndef` guard ensures compatibility with SDKs or platforms that already define `DEPRECATED_API`.
* Helps ensure migration away from deprecated APIs over time.

#### **Runtime Logging**

* Log usage at runtime:

   ```c
   ERROR: DEPRECATED FUNCTION <API> USED.
   ```

#### **Module Documentation**

* Review and update any related Markdown documentation for the HAL module to reflect the deprecated status.
* Ensure deprecated APIs are clearly marked and guidance on replacements is provided.

---

## **Step 2: HAL Validation & Documentation**

### **VTS Adjustment**  

* When an API is marked deprecated, its function tests must continue to exist and be executed until the API is fully removed.
* Removal of function tests from the HAL Validation Test Suite (VTS) may only occur once the header file version without the deprecated API has been released.
* The new header file version must not be consumed or published externally until the corresponding VTS version is also ready and aligned.
* Document the deprecated API in VTS documentation for reference.
* Create a dedicated Evolved APIs Section in VTS Release Notes that lists:
  * API Name
  * Evolution Date
  * Replacement API (if available)

### **HAL Release Notes**  

* Create a dedicated **Evolved APIs Section** in the HAL Release Notes that lists:
  * API Name
  * Evolution Date
  * Replacement API (if available)

### **Communicate Evolution**  

* Inform all relevant engineering stakeholders. IDE + Doxygen warnings will provide developer visibility.

---

## **Step 3: Evolution Ticketing**

### **Evolution Ticket**

* Title: "Evolve `<API Name>`"  
* Include:
  * Rationale
  * Target removal release version
  * Replacement guidance
  * Evolution date

### **Assignment & Tracking**

* Assign to relevant HAL engineering teams.

---

## **Step 4: Hard Removal**

> *A deprecated API may only be removed after at least one release cycle (or defined period) with no active consumers.*

### **Major Version Bump**

* Increment HAL major version to signal breaking change (e.g. v5.0.0 → v6.0.0).
* Document removal in unified Release Notes, and update the Evolved APIs sections accordingly.

### **Code & Test Cleanup**

* Fully remove declaration, implementation, and related HAL tests.

### **Verification**

* HAL CI and build/test pass criteria validated post-removal.

### Module Documentation

* Ensure all relevant Markdown documentation is updated to remove references to the deprecated API.

---

## **Step 5: Final Verification & Ticket Closure**

### **Final Verification**

* Ensure HAL layer builds and passes validation.

### **Ticket Resolution**

* Close the Evolution Ticket upon verification.

---

## **Step 6: Emergency Exceptions**

If urgent removal is necessary (e.g. security risks):

1. **Document Rationale** in the Evolution Ticket.
2. **Obtain Explicit Sign-Off** from Principal Architect and QA.
3. **Accelerated Execution** of HAL removal.

---

## **Roles & Responsibilities**

| Role               | Responsibilities                                                                 |
|--------------------|----------------------------------------------------------------------------------|
| HAL Vendor Team    | Soft evolution, warnings/logging, version bump, final removal and verification |
| QA/Test Team      | Update VTS/tests, enforce build/test pass criteria, maintain Evolved APIs sections in release notes |
| Architecture & PM | Approve plan/changes, manage exceptions, track evolution through ticketing     |

## Checklists Lists for Pasting into PR reviews

---

```markdown
### **HAL API Evolution Ticket Checklist (Soft Removal)**

* [ ] API declaration moved to `Deprecated APIs` section in HAL header file
* [ ] `@deprecated` Doxygen tag added with date and replacement API
* [ ] Compiler deprecation macro implemented to generate warnings
* [ ] Runtime logging added to capture deprecated API usage
* [ ] HAL module Markdown documentation updated to reflect evolution
* [ ] HAL Release Notes updated with Evolved APIs section
* [ ] Relevant engineering teams notified
```

---

```markdown
### **HAL API Evolution Ticket Checklist (Hard Removal)**

* [ ] At least one release cycle (or defined period) with no active consumers completed
* [ ] HAL header file version without deprecated API released
* [ ] HAL major version incremented to signal breaking change
* [ ] API removed from HAL header and implementation
* [ ] HAL module Markdown documentation updated to remove API references
* [ ] HAL Release Notes updated to remove API
* [ ] HAL CI build and test verification completed
* [ ] Evolution Ticket closed
```

---

```markdown
### **VTS Ticket Checklist (Soft Removal)**

* [ ] Deprecated API tests retained in VTS
* [ ] VTS Release Notes updated with Evolved APIs section
* [ ] VTS Markdown documentation updated with evolution notice
* [ ] VTS Doxygen updated with evolution notice
```

---

```markdown
### **VTS Ticket Checklist (Hard Removal)**

* [ ] Deprecated API tests removed from VTS (aligned with HAL header removal)
* [ ] VTS Markdown documentation updated to reflect API removal
* [ ] VTS Doxygen updated to reflect API removal
* [ ] VTS Release Notes updated to remove Evolved APIs section entry
```
