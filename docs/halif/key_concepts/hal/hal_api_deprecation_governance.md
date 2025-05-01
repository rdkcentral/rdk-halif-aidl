# **HAL API Deprecation Governance Process**

**Objective**

This document defines the governance process for managing the lifecycle of HAL APIs through deprecation and eventual removal. It outlines how HAL API deprecations will be communicated, documented, validated, and executed in a controlled and visible manner. This ensures backward compatibility during transition periods, minimises risk, and provides clear guidance to engineering teams on the required steps and responsibilities throughout the deprecation process.

---

## **Step 1: Soft Deprecation**

#### **Header Annotation**

   - Move API declaration to a clearly marked **Deprecated APIs** section in HAL header files.  
   - Use Doxygen `@deprecated` tag with:
     - Deprecation date (e.g. `@deprecated Deprecated since 2025-04-01`)
     - Replacement API if available (e.g. `Use NewHALAPI_DoTask() instead.`)
   - Example:
      ```c
      /**
      * @deprecated Deprecated since 2025-04-01. Use NewHALAPI_DoTask() instead.
      */
      void OldHALAPI_DoTask();
      ```
   - This allows IDEs (such as VSCode) to highlight deprecated APIs automatically. Recommended VSCode extensions:
     - **Doxygen Documentation Generator**
     - **Better C++ Syntax**
     - **C/C++ (Microsoft)** (recognises Doxygen tags)

#### **Compiler Warning**

   - Wrap deprecated function in a deprecation macro to trigger warnings in builds:
      ```
      WARNING: DEPRECATED FUNCTION <API> USED. Please migrate.
      ```

#### **Runtime Logging**

   - Log usage at runtime:
      ```
      ERROR: DEPRECATED FUNCTION <API> USED.
      ```

---

## **Step 2: HAL Validation & Documentation**

### **VTS Adjustment**  

- Remove deprecated API from HAL Validation Test Suite (VTS).
- Document the deprecated API in VTS documentation for reference.
- Create a dedicated **Deprecated APIs Section** in VTS Release Notes that lists:
- API Name
- Deprecation Date
- Replacement API (if available)

### **HAL Release Notes**  

- Create a dedicated **Deprecated APIs Section** in the HAL Release Notes that lists:
- API Name
- Deprecation Date
- Replacement API (if available)

### **Communicate Deprecation**  

- Inform all relevant engineering stakeholders. IDE + Doxygen warnings will provide developer visibility.

---

## **Step 3: Deprecation Ticketing**

### **Deprecation Ticket**

- Title: "Deprecate `<API Name>`"  
- Include:
   - Rationale
   - Target removal release version
   - Replacement guidance
   - Deprecation date

### **Assignment & Tracking**

- Assign to relevant HAL engineering teams.

---

## **Step 4: Hard Removal**

> *A deprecated API may only be removed after at least one release cycle (or defined period) with no active consumers.*

### **Major Version Bump**

   - Increment HAL major version to signal breaking change (e.g. v5.0.0 → v6.0.0).
   - Document removal in unified Release Notes, and update the Deprecated APIs sections accordingly.

### **Code & Test Cleanup**

   - Fully remove declaration, implementation, and related HAL tests.

### **Verification**

   - HAL CI and build/test pass criteria validated post-removal.

---

## **Step 5: Final Verification & Ticket Closure**

### **Verification**

   - Ensure HAL layer builds and passes validation.

### **Ticket Resolution**

   - Close the Deprecation Ticket upon verification.

---

## **Step 6: Emergency Exceptions**

If urgent removal is necessary (e.g. security risks):

1. **Document Rationale** in the Deprecation Ticket.
2. **Obtain Explicit Sign-Off** from Principal Architect and QA.
3. **Accelerated Execution** of HAL removal.

---

## **Roles & Responsibilities**

| Role               | Responsibilities                                                                 |
|--------------------|----------------------------------------------------------------------------------|
| HAL Vendor Team    | Soft deprecation, warnings/logging, version bump, final removal and verification |
| QA/Test Team      | Update VTS/tests, enforce build/test pass criteria, maintain Deprecated APIs sections in release notes |
| Architecture & PM | Approve plan/changes, manage exceptions, track deprecation through ticketing     |
