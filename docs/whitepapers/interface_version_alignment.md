# **White Paper: Interface Version Alignment**

## **Introduction**

### **Purpose of This White Paper**

This document outlines a structured approach for aligning **semantic versioning** of HAL interfaces with their corresponding **testing suites**, ensuring predictable release behaviour, traceable upgrades, and clear separation of breaking vs non-breaking changes.

It also recommends that **3rd Party Vendor Wrappers** align their versioning—specifically the **MAJOR** version—with the HAL interface to promote ecosystem compatibility and clarity.

### **Intended Audience**

* Software architects and HAL interface maintainers.
* Testing framework developers and validation engineers.
* Vendor teams producing downstream wrappers for HAL interfaces.

---

## **Versioning Philosophy**

### **Why Align Versions?**

To avoid interface drift, misaligned test coverage, and difficult upgrade paths, all HAL interface versions must follow a consistent versioning model, and the test suite must evolve with them.

Aligning the test suite and wrapper ecosystem to this model:

* Promotes interface stability across releases.
* Enables accurate test coverage per interface version.
* Avoids premature test failures due to feature lag.

### **Semantic Versioning Model**

We adopt the SemVer model with an additional `DOC` tag for non-functional documentation updates:

```
MAJOR.MINOR.BUGFIX[/DOC]
```

**Definitions**:

* **MAJOR** – Incompatible changes requiring rebuilds or consumer changes.
* **MINOR** – Backward-compatible functional enhancements.
* **BUGFIX/DOC** – Backward-compatible bug resolutions / Non-functional documentation-only changes.

---

## **Versioning Guidelines**

### **Interface Evolution**

* If a change **does not require** consumers to rebuild: increment **MINOR**.
* If a change **requires** a rebuild or breaks compatibility: increment **MAJOR**.

### **Bug Fixes and Documentation**

* Bug fixes increment **BUGFIX**.
* Editorial documentation updates increment **DOC**.

### **Vendor Wrapper Versioning**

* 3rd Party Vendors should **mirror the HAL interface MAJOR version** in their own releases to ensure consistency, even if additional minor features or abstraction layers are present.

---

## **Testing Suite Alignment**

### **Version Binding**

Test suites are tightly coupled to the interface via the **MAJOR.MINOR** version. A `1.3.x` test suite explicitly validates HAL Interface `1.3.0+`.

### **Backward Compatibility with AIDL**

All AIDL-based interfaces must be **100% backward-compatible** by design. However:

* A test suite for version `1.3.0` may not yet validate new features introduced in `1.3.0` at the time of interface release.
* Test suites must be updated **in parallel** to track new MINOR changes.

### **Cloning and Maintaining Test Suites**

To preserve version-specific coverage:

* Testing suites must be **cloned or branched** per `MAJOR.MINOR` version.
* Bug fixes can be backported to older suites using standard Git flows.

---

## **Example Workflows**

### **HAL Interface Upgrade**

1. Add a backward-compatible feature.
2. Increment version: e.g., `1.2.5 → 1.3.0`.
3. Prepare the `1.3.x` test suite with new validations.
4. Release both interface and tests.

### **HAL Test Suite Upgrade**

1. Extend coverage for features introduced in `1.3.0`.
2. Version the suite: `1.2.x → 1.3.0`.
3. Publish alongside HAL interface `1.3.0`.

### **Bug Fix in Test Suite**

1. Identify and fix a validation bug in version `1.3.0`.
2. Increment version: `1.3.0 → 1.3.1`.
3. Deploy `1.3.1` as the default test target for HAL `1.3.0`.

---

## **Benefits**

* **Clear Versioning Discipline**
  Version increments signal consumer impact and testing requirements.

* **Complete Coverage**
  Every interface version has an aligned, validated test suite.

* **Backward Compatibility by Design**
  AIDL enforces compatibility; tests enforce correctness.

* **Vendor Ecosystem Clarity**
  Downstream wrappers remain version-mapped and in sync.

---

## **Version History**

| **Version** | **Date**      | **Author**       | **Comments**                                                                             |
| ----------- | ------------- | ---------------- | ---------------------------------------------------------------------------------------- |
| Draft       | 8th July 2025 | Gerald Weatherup | Initial whitepaper draft aligned to internal documentation structure and best practices. |
