# **White Paper: Standardizing Git Commit Messages with the 50/72 Rule**

## **Executive Summary**

In collaborative software development, the quality of version control history directly impacts maintainability, traceability, and communication across teams. This white paper introduces the 50/72 rule — a proven standard for formatting Git commit messages — and outlines its importance in automated changelog generation, release documentation, and long-term project governance.

---

## **Introduction**

Git commit messages are the primary medium for recording the history and intent of code changes. Yet in many projects, they are inconsistently written, poorly structured, or devoid of useful context. This impairs collaboration, delays debugging, and undermines transparency.

The 50/72 rule addresses this problem by providing a simple, standardized format for commit messages that is both human-readable and machine-parseable. This white paper explains the rule, its rationale, and how to apply it effectively.

---

## **Why Message Structure Matters**

Commit messages form the **source of truth** for version history. When formatted consistently:

* They provide a **narrative** for every decision made in the codebase.
* They **accelerate onboarding** for new developers by making history easier to follow.
* They enable **automated tooling** — such as changelog generators, release note systems, and CI/CD integrations — to extract structured insights from the commit log.

In RDK and similar development environments, structured commit messages feed into systems that automatically generate:

* Changelogs
* Deployment summaries
* Auditable histories
* Issue-linked release notes

Without a consistent standard, this automation becomes unreliable or meaningless.

---

## **The 50/72 Rule Explained**

### **1. Subject Line (≤ 50 Characters)**

* Use the **imperative mood**: "Add", "Fix", "Update".
* Be **concise** but **specific**.
* Use **present tense**, describing what the commit does now.
* Avoid filler language (e.g., “some changes”, “misc tweaks”).

**Examples:**

```
Add API for Bluetooth device pairing
Fix crash when handling empty config files
Update CI workflow for multi-arch testing
```

### **2. Blank Line Separator**

Always insert a **blank line** between the subject and body. This is essential for proper parsing by Git tools and changelog scripts.

### **3. Body (≤ 72 Characters Per Line, Optional)**

The body provides context and reasoning:

* Explain the **motivation** behind the change.
* Describe **edge cases**, limitations, or downstream impacts.
* Wrap text at 72 characters per line for readability in terminals and diff tools.

**Example:**

```bash
Fix #101: Prevent race condition in device state manager

The update adds locking logic to avoid state mismatch when multiple
threads attempt to modify device power states concurrently.
This prevents a rare but reproducible failure in CI pipelines.
```

---

## **Common Verbs for Commit Subjects**

Standardizing verbs helps teams quickly understand the nature of each change. Recommended actions include:

* `Add`: Introduce new functionality or files
* `Fix`: Correct a bug or unintended behavior
* `Update`: Apply minor improvements or changes
* `Remove`: Eliminate unused code, files, or dependencies
* `Refactor`: Restructure code without changing behavior
* `Improve`: Enhance readability, performance, or documentation
* `Test`: Add or modify tests
* `Clean`: Remove extraneous files or temporary artifacts
* `Merge`: Integrate branches or resolve divergent histories

---

## **Benefits of Adopting the 50/72 Rule**

### **1. Readability**

Well-structured commit logs are easier to review, audit, and understand.

### **2. Maintainability**

Future developers can trace *why* a change occurred—not just what changed.

### **3. Collaboration**

Peer reviewers, QA teams, and release managers benefit from consistent and meaningful messages.

### **4. Automation Compatibility**

Tools can automatically generate changelogs, link to issue trackers, and build documentation from standardized commit messages.

---

## **Best Practices for Teams**

* **Enforce via commit hooks** or linting tools.
* **Reference issue numbers** when applicable (e.g., `Fix #456`).
* **Keep commits focused**, representing one logical change per commit.
* **Review messages** as part of code review — just like code quality.

---

## **Example: Real-World Message**

```bash
Fix #237: Address memory leak in audio service

Added cleanup logic to release buffers in the audio stream teardown
path. Leak was triggered by rapid stream restarts during live
channel switching. Also added unit test to validate buffer cleanup.
```

---

## **Conclusion**

Standardized Git commit messages are more than a formatting preference — they are a foundational element of software quality, traceability, and automation readiness. The 50/72 rule offers a lightweight, high-impact way to improve every team’s development workflow. By adopting this practice across your engineering organization, you promote clearer communication, smoother collaboration, and more maintainable systems.

---

**Author:** Gerald Weatherup  
**Date:** 19th May 2025
