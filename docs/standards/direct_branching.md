# **Core Development Guide: Branching for Direct Contributions**

## **Overview of Contributions**

We welcome contributions from all community members, including both **Core Development Teams** (direct access) and **Fork-Based Contribution Teams** (forked workflow). Your participation is vital to the project's success. Here's how you can get involved:

* **Code Contributions:** Whether you're proposing new features or fixing bugs, please follow the detailed steps below to ensure your contributions align with our standards.
* **Issue Reporting:** If you discover bugs or have suggestions for improvement, open a GitHub issue. These reports drive continuous enhancement.
* **Discussions and Ideas:** We encourage open discussions on technical ideas, design proposals, and development challenges. Your insights shape the evolution of the platform.

## **Access Levels and Workflows**

* **Core Development Teams (Direct Access):**
  These contributors have write access to the main repository. They follow a structured Git Flow branching model and are responsible for maintaining shared platform components. [See the Core Development Team Registration Process](./rdk_central_signup.md)

* **Fork-Based Contribution Teams (External Workflow):**
  These contributors do not have direct access. They develop via forks of the repository and submit their work through pull requests. This model supports deployment-specific customization and community-driven innovation. [See the Fork-Based Contribution Guide for detailed instructions](./forked_based_branching.md)

---

## **Contributor License Agreement (CLA)**

Before any code can be merged, you must sign the [RDK Contributor License Agreement (CLA)](https://wiki.rdkcentral.com/claagreement.action). This ensures legal clarity and freedom for the community to use your contributions. First-time contributors must complete this step before any merges can occur.

---

## **Getting Started with Git Collaboration**

### 1. **Clone the Repository**

```bash
git clone https://github.com/rdkcentral/ut-core.git
```

### 2. **Set Up Git Flow**

We use Git Flow to structure development:

```bash
git flow init -d
```

### 3. **Create a Feature Branch**

Start from `develop` and name your branch as `feature/gh<issue-number>_<description>`:

```bash
git flow feature start 123_add-logging-enhancements
```

> **Compliance Notice:** All branches must align with naming conventions and be traceable to a GitHub issue. Non-compliant branches are subject to removal if not corrected within 30 days.

### 4. **Implement Changes**

Follow coding standards and document your changes thoroughly.

### 5. **Commit Your Changes**

Use the [50/72 rule](../whitepapers/standardizing_git_commit_messages.md):

```bash
Fix #123: Update error handling in authentication module

This commit enhances error detection and adds comprehensive logging to address frequent issues reported by users.
```

### 6. **Push Changes**

```bash
git push origin feature/gh123_add-logging-enhancements
```

### 7. **Open a Pull Request**

Create a PR to the `develop` branch. Review will be auto-assigned via `CODEOWNERS`.

### 8. **Merge the Pull Request**

After approval:

```bash
git flow feature finish gh123_add-logging-enhancements
```

### 9. **Code Ownership and Releases**

`CODEOWNERS` ensure quality and manage release tagging:

```plaintext
*       @rdkcentral/ut-core_codeowner
```

---

## **Requirements for Contributions**

* Use Git Flow correctly.
* Write clear commit messages.
* Undergo and complete peer reviews.
* Participate in open discussions.

By following these practices, you contribute to a robust and transparent open-source platform. We appreciate your involvement in building a high-quality, maintainable codebase.
