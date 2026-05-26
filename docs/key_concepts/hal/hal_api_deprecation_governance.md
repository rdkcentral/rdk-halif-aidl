# **HAL API Deprecation Governance Process**

## Document History

| Date | Author | Comments |
| --- | --- | --- |
| 06 June 2025 | G.Weatherup | Draft Revision |
| 12 March 2026 | G.Weatherup | Rewrite for AIDL HAL model — deprecate and keep forever, aligned with Android AIDL stable versioning |

## **Scope**

This document defines the deprecation governance process for **AIDL-based HAL interfaces** as defined in this repository.

AIDL stable versioning is **additive-only** — each frozen interface version is a permanent, backwards-compatible contract. Methods are never modified or removed within a version. This follows the same model used by Android/Google for AIDL stable interfaces.

> **TL;DR:**
>
> 1. **Deprecate, never remove** — deprecated methods remain in the interface permanently; they are never deleted
> 2. **Mark deprecated** — add `@deprecated` to the AIDL doc comment with date, reason, and replacement
> 3. **New version** — add replacement methods in a new interface version (additive-only)
> 4. **Update docs & tests** — update documentation, release notes, and VTS to cover both old and new methods
> 5. **Track** — create a deprecation ticket for visibility and migration tracking

## **Objective**

This document defines the governance process for deprecating HAL API methods. Deprecated methods are **marked and kept permanently** — they are never removed from the interface. This follows the AIDL stable versioning contract: once a method is part of a frozen interface version, it exists forever for backward compatibility.

The goal is to provide clear guidance on how to signal that a method should no longer be used, how to introduce replacements, and how to communicate these changes to downstream consumers (SoC vendors, OEMs, and integration teams) who may be outside our direct control.

---

## **Why Deprecate and Keep Forever?**

Unlike traditional C-based HAL APIs where deprecated functions can eventually be removed, AIDL stable interfaces require a different approach:

* **Frozen versions are immutable** — once an AIDL interface version is frozen and released, its methods are a permanent contract.
* **Versioning is additive-only** — new methods can be added in a new version, but existing methods persist unchanged across all versions.
* **We don't control all consumers** — SoC vendor partners implement these interfaces independently. We cannot guarantee that all partners will migrate away from a deprecated method on our timeline. Removing a method would break their implementations.
* **This matches Android's model** — Android/Google uses the same approach for AIDL stable interfaces: deprecated methods are annotated but never removed.

Deprecated methods remain callable but should not be used in new implementations. Over time, they become effectively unused — but the contract guarantees they are always available.

---

## **Step 1: Mark Deprecated**

### **AIDL Annotation**

* Add `@deprecated` to the method's doc comment in the `.aidl` file with:
  * **Deprecation date** (e.g. `Deprecated since 2026-03-01`)
  * **Reason** for deprecation
  * **Replacement method** if available
  * Example:

    ```aidl
    /**
     * @deprecated Deprecated since 2026-03-01. Use doTaskV2() instead.
     * Reason: doTask() does not support async completion callbacks.
     */
    void doTask();
    ```

* This allows IDEs with AIDL support to highlight deprecated methods automatically, warning consumers to migrate.

### **Module Documentation**

* Update the HAL module's Markdown documentation to clearly mark the method as deprecated.
* Provide guidance on the replacement method and migration path.

---

## **Step 2: Add Replacement Methods**

### **New Interface Version**

* Add the replacement method(s) in a new AIDL interface version (additive-only — no changes to existing methods).
* Bump the `minor` field in `metadata.yaml` (see [Versioning SOP](../../governance/versioning-sop.md)).
* The deprecated method remains in the interface unchanged.

### **Migration Guide**

* Document the mapping from deprecated method(s) to their replacements.
* Include any behavioural differences between old and new methods.

---

## **Step 3: Update Validation & Documentation**

### **VTS Adjustment**

* VTS tests for the deprecated method **must be retained permanently** — the method is still part of the interface contract.
* Add VTS tests for the new replacement method.
* Mark deprecated method tests with a comment indicating the method is deprecated and which test covers the replacement.

### **HAL Release Notes**

* Add a **Deprecated APIs** section in the HAL Release Notes listing:
  * Method name
  * Deprecation date
  * Replacement method (if available)
  * Reason for deprecation

### **Communicate Deprecation**

* Inform all relevant engineering stakeholders and downstream SoC/OEM partners.

---

## **Step 4: Deprecation Ticketing**

### **Deprecation Ticket**

* Title: "Deprecate `<Method Name>` in `<Component>`"
* Include:
  * Rationale for deprecation
  * Replacement method and migration guidance
  * Deprecation date
  * List of known consumers (if available)

### **Assignment & Tracking**

* Assign to relevant HAL engineering teams.
* The ticket remains open for tracking consumer migration progress but is not gated on removal — the method stays forever.

---

## **Roles & Responsibilities**

| Role | Responsibilities |
| --- | --- |
| HAL Vendor Team | Mark deprecated, add replacement methods, version bump |
| QA/Test Team | Retain VTS for deprecated methods, add VTS for replacements, maintain release notes |
| Architecture & PM | Approve deprecation plan, manage exceptions, track migration through ticketing |

## Checklists for Pasting into PR Reviews

---

```markdown
### **HAL API Deprecation Checklist**

* [ ] `@deprecated` annotation added to AIDL doc comment with date, reason, and replacement
* [ ] Replacement method added in new interface version (if applicable)
* [ ] Minor version bumped in metadata.yaml
* [ ] HAL module Markdown documentation updated to reflect deprecation
* [ ] Migration guide documenting old-to-new method mapping
* [ ] HAL Release Notes updated with Deprecated APIs section
* [ ] Relevant engineering teams and downstream partners notified
* [ ] Deprecation Ticket created with rationale and migration guidance
```

---

```markdown
### **VTS Deprecation Checklist**

* [ ] VTS tests for deprecated method retained (must remain permanently)
* [ ] VTS tests for replacement method added
* [ ] Deprecated method tests annotated with deprecation notice
* [ ] VTS Release Notes updated with Deprecated APIs section
* [ ] VTS Markdown documentation updated with deprecation notice
```
