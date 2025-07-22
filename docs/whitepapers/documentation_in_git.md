# **White Paper: Documentation in Git**

## **Executive Summary**

Modern software development requires a dependable system for managing both source code and its accompanying documentation. When code and documentation reside in separate repositories or locations, they can quickly fall out of sync, leading to confusion and technical debt. By **co-locating** design and specification documents alongside the code itself using Doxygen-based comments and Markdown-based documentation (compiled by tools like MkDocs) teams can:

- **Maintain Consistency**: All interfaces, testing suites, and documentation evolve together, eliminating discrepancies.  
- **Enable Full Control & Versioning**: Every change is tracked through Git’s history, ensuring a transparent record of updates for code and docs alike.  
- **Enforce Peer-Reviewed Quality**: Documentation changes are reviewed just as rigorously as code changes.  
- **Streamline Releases**: A tag-based publishing process ensures that released documentation accurately matches stable code.

This white paper outlines an approach to achieving a “single source of truth” for software projects, leveraging Git-based workflows whether in private, enterprise, or open-source settings.

---

## **1. Purpose of This White Paper**

This document details how to organise and maintain design, specification, and testing documentation **within** the same repository as the source code. By doing so, teams ensure:

- **Synchronisation** of all technical details with implementation and test suites.  
- **Traceability** and transparency of updates through Git commit history.  
- **Easy Automation** of documentation generation and publishing processes.  

### **Intended Audience**

- **Engineering Teams & Architects**: Responsible for code, interface definitions, and system design.  
- **Technical Writers**: Creating, maintaining, and publishing comprehensive documentation.  
- **DevOps/CI Specialists**: Implementing controlled release processes for both code and docs.  
- **Product Stakeholders**: Requiring reliable, up-to-date release information.

Although written with internal teams in mind, these practices translate seamlessly to open source projects, promoting a collaborative and transparent environment.

---

## **2. Documentation Strategy**

### **Why a Single Source of Truth?**

Best practices recommend treating documentation with the same discipline as source code often called “documentation as code.” By placing:

- **Interfaces** (e.g., HAL or API specs)  
- **Test Suites** validating these interfaces  
- **Documentation** (architecture overviews, usage guides, etc.)

in the **same repository**, you gain:

- **Version Control**: Code, tests, and docs share the same commit history, simplifying rollbacks and issue tracking.  
- **Discoverability**: Developers and reviewers find all relevant information in one place.  
- **Consistency**: Docs remain updated alongside code changes.  
- **Collaboration**: Contributions to both code and documentation occur through a unified workflow.  
- **Automation**: Tools such as Doxygen, Sphinx, and MkDocs can automatically generate documentation from in-code comments and Markdown.

### Where to Store Documentation

- **Within the Same Repo**: Primary approach for coupling code and docs.  
- **Separate Repos:** If code or testing suites are maintained in their own repositories, then the associated documentation must also reside within those repositories. This approach ensures each codebase or test suite remains a single source of truth, preserving consistency and discoverability across the project.

This integrated approach ensures that interface definitions, test coverage, and user-facing documentation evolve in tandem.

---

## **3. Version Control, Documentation Generation, and Component Stability**

This section outlines the necessary tools and processes for a robust, code-and-docs-aligned strategy.

### Tools and Workflow

- **Git**: Handles version control for both code and documentation.  
- **MkDocs**: Builds human-readable docs from Markdown sources.  
- **Doxygen**: Generates reference API documentation directly from annotated code comments.  
- **CI Pipelines**: Automate generation and deployment whenever relevant changes are made.

### Branching and Versioning Strategy

Any standard branching workflow Git Flow, Trunk-Based Development, GitHub Flow, etc. can support documentation as code (See [White Paper: Branching Strategies for Modern Software Delivery](./branching_strategies.md)) . The key is ensuring that **documentation updates are committed and merged alongside code changes**. Automated builds or merges can trigger:

- **Preview Deployments**: So reviewers can see updated docs before they merge.  
- **Semantic Versioning (SemVer)**: `major.minor.bugfix/doc` increments for each release, including doc-only updates.  
- **Release Tagging**: Ensures published documentation always matches a stable code tag.

---

### Component Versioning

Each component or interface/implementation follows a **fixed version consumption model**, adhering to strict Semantic Versioning (SemVer):

- **Major** – Incremented for incompatible changes.  
- **Minor** – Incremented when adding functionality in a backwards-compatible manner.  
- **Bugfix/Doc** – Incremented for backwards-compatible fixes or documentation enhancements.

This ensures code and documentation remain aligned at every release milestone.

#### Exception – AIDL Interfaces

AIDL interfaces are **incrementally versioned** for all changes. By design, these interfaces are fully backwards compatible, allowing older clients to continue functioning without recompilation unless they explicitly opt into newer features. If a truly incompatible change becomes necessary, a separate interface component is introduced rather than modifying the existing one.

### Applicability: Internal vs. Open Source

- **Internal Projects**: Keep all docs, code, and tests in private repositories; stable releases or tags still govern which doc versions are published.  
- **Open Source Projects**: Follow the same process publicly, allowing external contributors to benefit from accurate, versioned docs.

---

## 4. Proposed Solution Overview

### Centralised Documentation

#### 1. **Store Documentation Alongside Source Code**

- Maintain architecture, interface definitions, and specs in a `docs/` folder.  
- Annotate code with Doxygen to generate reference-level documentation automatically.

#### 2. **Mandatory Documentation Peer Reviews**

- Treat doc changes as a critical part of each pull request or merge request.  
- Maintain consistent style and completeness.

#### 3. **Use MkDocs for Aggregated Documentation**

- Write explanatory docs in Markdown, generate a static site.  
- Embed or link Doxygen API docs for deeper technical references.

### Publishing to GitHub Pages (or Equivalent)

- **Automated Build Scripts**: Build scripts to setup all requirements and trigger builds see [build_docs.sh](../build_docs.sh) to compile MkDocs, run Doxygen, and deploy to `gh-pages`.  
- **Hosting Configuration**: For both open source and internal github pages can be used.

### Script-Driven Documentation Releases

- **Tag-Based Process**: Once code is tagged (e.g., `v1.2.0`), a CI job builds and publishes docs tied exactly to that tag.  
- **Manual or Automatic**: Teams may manually trigger the script or let CI handle it upon new tags.

---

## 5. Detailed Workflow

### Repository Structure

```
myproject/
├── docs/
│   ├── index.md
│   ├── architecture.md
│   ├── api_docs.md
│   ├── build_docs.sh
│   └── ...
│   
├── src/
│   ├── interfaces/
│   │   └── hal_xyz.cpp
│   ├── tests/
│   │   └── test_hal_xyz.cpp
│   └── ...
├── Doxyfile
├── mkdocs.yml
```

### Generating API Documentation (Doxygen)

- **Doxyfile Configuration**: Point `INPUT` to source directories (e.g. `./src`) and `OUTPUT_DIRECTORY` to `./docs/doxygen`.  
- **In-Source Comments**: Use robust style guidelines to ensure clarity and completeness.  

### **5.3 Building the MkDocs Site**

- **mkdocs.yml**: Defines the site structure (navigation, themes, plugins).  
- **Mermaid Diagrams**: Add visual clarity with Markdown-based sequence or flow diagrams.  
- **Embedding Doxygen Outputs**: Link or embed the generated HTML to unify all doc types.

---

## **6. Incorporating External Markdown**

If some aspects of the product exist in separate modules or repositories, a custom script can:

- Clone or pull relevant markdown files.  
- Merge them into the main `docs/external_content` folder.  
- Build a consolidated site, ensuring completeness across all components.

---

## **7. Best Practices**

### 1. **Co-locate Everything**

- Keep code, interfaces, tests, and docs in one place for easy discovery and consistent versioning.

### 2. **Enforce Documentation Reviews**

- Build quality docs by reviewing them alongside code changes.

### 3. **Use a Shared Style Guide**

- Maintain consistent Doxygen annotations and Markdown formatting.
- See [White paper: Doxygen Code Documentation](./doxygen_code_documentation.md)

### 4. **Version Docs with Releases**

- Ensure stable doc sets exist for each official code tag.
- Tools like “mike” can help preserve older versions for historical reference.

### 5. **Automate Where Possible**

- Scripts and CI pipelines reduce manual effort and prevent oversights.

### 6. **Adapt to Your Branching Model**

- Whether Git Flow, trunk-based, or otherwise ensure doc updates follow the same workflow as code.
- See [White Paper: Branching Strategies for Modern Software Delivery](./branching_strategies.md)

---

## **8. Conclusion**

Treating documentation as code is essential for maintaining **accuracy, consistency, and traceability** throughout the software lifecycle. By co-locating source code, interface specifications, tests, and Markdown-based documentation in a single repository and automating the build and release processes organisations can:

- **Streamline Collaboration**: Both code and documentation become peer-reviewed deliverables.  
- **Ensure Synchronisation**: Changes to functionality are always reflected in the docs.  
- **Reduce Fragmentation**: A single source of truth eliminates confusion and duplication.  
- **Support Varied Release Models**: Regardless of branching strategy or open/closed sourcing, a unified approach to version control ensures reliable documentation.

This white paper provides a guiding framework for introducing or refining a documentation-in-Git approach, fitting teams of varying sizes, complexities, and deployment requirements. By adopting these practices, engineering and documentation teams can deliver high-quality, up-to-date references that align perfectly with the code they describe.

---

**Author**: *Gerald Weatherup*  
**Date**: *03 March 2025*

For questions or suggestions on implementing branching strategies, please contact the Architecture team.