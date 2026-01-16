# Whitepaper: Choosing the Right Format for the Right Job

- **Type**: Engineering Whitepaper
- **Audience**: Developers and Systems Architects integrating and maintaining code
- **Purpose**:- To establish a selection strategy for configuration formats (YAML, TOML, JSON, INI) that prioritises human-readable documentation and schema validation for maintainable system configuration

---

## Executive Summary

The selection of a configuration format is often treated as a secondary concern, yet it is a primary factor in a system's long-term maintainability. The "Right Format" is one that balances structural requirements with the human necessity for context. This paper argues that the ability to record intent via **native documentation** and **schema validation** is the critical differentiator in selecting a format for team-based environments.

## The Documentation Mandate

Configuration values are rarely self-explanatory. Whether you are managing an application's API keys or defining a **[Hardware Feature Profile (HFP)](../halif/key_concepts/hal/hal_feature_profiles.md)**, adding context through documentation is vital for maintainability.

* **Context and Intent:** Comments explain the "Why" (e.g., *“Voltage capped for thermal safety”*) and the "What" (e.g., *“Disables legacy pre-fetcher”*).
* **Team Onboarding:** Well-documented configuration acts as "living documentation," allowing new members to understand system logic without deep-diving into source code.
* **Error Prevention:** Prevents "blind edits" where a value is modified without understanding the broader system impact.

## Format Analysis: Strengths and Strategic Use

Every format has a "best job" it was designed to perform. Selecting the wrong one creates a "Context Gap" that teams must fill with external, often outdated, documentation.

* **⚙️ INI (.ini):** Best for simple, flat settings. Excellent documentation support (`;`), but incapable of representing complex hierarchies.
* **🌳 YAML (.yaml):** The standard for highly structured, human-edited configurations (e.g., CI/CD, K8s). It supports native comments and **JSON Schemas**, though its whitespace sensitivity requires care.
* **🚀 TOML (.toml):** Ideal for modern application metadata. It offers the documentation strength of YAML but with more explicit typing and a more robust structure for human editors.
* **📊 JSON (.json):** The gold standard for machine-to-machine data exchange. While it supports **Native Schemas** for validation, its lack of native comments makes it the least suitable for human-facing documentation.

---

## The Decision Matrix: The Right Format for the Job

| Requirement | Recommended Format | Native Documentation | Schema Support |
| --- | --- | --- | --- |
| **Simple/Flat Preferences** | **INI** | High (Native) | Low |
| **Complex Human-Edited** | **YAML** | High (Native) | High |
| **Explicit/Typed Metadata** | **TOML** | High (Native) | Moderate |
| **Machine Data Exchange** | **JSON** | None | **Native** |

---

## Conclusion: Selection Strategy

To ensure the "Right Format for the Right Job," follow this hierarchy:

1. **Prioritize Human Context:** If the file is manually edited—especially for sensitive tasks like **Hardware Feature Profiles**—use YAML or TOML to ensure intent is documented alongside the value.
2. **Leverage Schemas:** For YAML and JSON, always implement a schema. This provides the "guardrails" (IntelliSense and validation) that prevent syntax errors and misconfiguration.
3. **Reserve JSON for APIs:** Use JSON strictly for programmatic interfaces where performance and universal parsing are more important than human-readable context.

## Document History

| Date        | Author             | Comments                                              |
| ----------- | ------------------ | ----------------------------------------------------- |
| 16th January 2026 | G. Weatherup | Initial Revision |
