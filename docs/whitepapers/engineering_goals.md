# **White Paper: Achieving Engineering Goals and Defining Requirements for Features and Tasks**

## **Executive Summary**

Effective goal setting and requirements definition are crucial for delivering high-quality, scalable, and maintainable software in an open-source community-driven development model. This white paper presents a structured methodology for defining features, tasks, and issues using GitHub, while ensuring visibility and alignment with long-term engineering objectives. While internal tracking tools such as JIRA may be used for high-level business goals, compliance, and reporting, the core development efforts remain transparent and community-accessible.

---

## **Introduction**

Community-driven software development, such as the one fostered within RDK Central, requires clear goal-setting mechanisms that ensure transparency, accountability, and effective collaboration among multiple contributing companies. The RDK Central development ecosystem is structured around **Tier 1** and **Tier 2** development teams, each with defined roles and contribution processes:

- **Tier 1 Developers** – These teams are responsible for core platform contributions and work collaboratively across multiple companies to define, develop, and maintain foundational components. Their work is closely tracked, with direct contributions managed following structured branching workflows. For more details, refer to the [Tier-1 Operator Guide: Branching for Direct Contributions](https://github.com/rdkcentral/ut-core/wiki/1.0.-Standards:-Tier-1-Operator-Guide:-Branching-for-Direct-Contributions).
- **Tier 2 Developers** – These contributors typically focus on feature development, customization, and extensions for specific deployments. They operate by extending or integrating components from Tier 1, ensuring that their contributions align with core platform developments. Contributions from Tier 2 developers follow a forking model for external contributions. For more details, refer to the [Tier-2 Operator Guide: Forking for External Contributions](https://github.com/rdkcentral/ut-core/wiki/1.0.1-Standards:-Tier-2-Operator-Guide:-Forking-for-External-Contributions).

This paper outlines a standardized process for tracking engineering work, documenting requirements, and structuring project management workflows using GitHub Issues, Milestones, and JIRA for high-level business tracking. These practices are actively in use within RDK Central to maintain visibility and collaboration across all development tiers.

---

## **Engineering-Oriented Goal Setting**

Drawing inspiration from *Management in 10 Words*, this methodology reframes business goals into engineering-centric principles:

1. **Trust** – Enable transparency and accountability in development.
2. **Truth** – Define clear and objective requirements.
3. **Clarity** – Ensure well-documented issues, features, and tasks.
4. **Balance** – Prioritize sustainable development over short-term fixes.
5. **Simplicity** – Minimize complexity and technical debt.
6. **Focus** – Align features with long-term platform scalability.
7. **Commitment** – Encourage ownership of tasks and quality delivery.
8. **Adaptability** – Support evolving requirements with a flexible architecture.
9. **Standards** – Follow industry best practices for consistency and compliance.
10. **Excellence** – Strive for high reliability and maintainability.

---

## **Requirements Breakdown**

### **Epics (Internal, JIRA-Based)**

All work is driven **business requirements** which in turn generates **development work**. To manage this effectively, we categorize work into two distinct types:  

1. **Program Management Epics (JIRA - Business-Driven)**
    - Define the **"what"** in product development, originating from business requirements.  
    - Comcast and Sky drive **business requirements and architectural alignment** with third parties to ensure feature development benefits all stakeholders.  
    - A **Program Management Epic** may require multiple **Development Features** to be completed before it can be resolved.  

2. **Development Work (GitHub Features - Community-Contributed)**  
    - Define the **"how"** in software development, driven by contributions from the development community.  
    - Contain sub-features, tasks, and bugs that contribute to completing the **Development Work**.  
    - Development is a **collaborative effort**, where contributors have their own business drivers, but the **source code evolves for the benefit of all parties involved**.  
    - Tracked in GitHub to facilitate open collaboration and shared progress across multiple contributors.  

Since development work is community-contributed, tracking is adapted accordingly. **Program Management Epics** remain internal to JIRA, ensuring alignment with business objectives, while **Development Work** exist in GitHub as a shared development space where work progresses collectively. This structure ensures that Comcast and Sky provide the necessary guidance and coordination while allowing the development community to contribute effectively.

All work is driven by **business requirements**, which in turn generates **development work**. Some layers, or even parts of layers, may be internal, with internal tasks optionally tracked in JIRA. However, since **all source code is likely to be hosted in GitHub in the future**, it is advisable to adopt a **common GitHub tracking model** for both internal and external work.  

Since **development work** consists of changes to a **Git repository**, whether it be **code, documentation, test results, or any other modifications**, all tracking should be done within **GitHub**.

This approach ensures:

- **Consistency in development tracking** across all contributors, whether internal or external, since every change is inherently part of the Git history.  
- **Better visibility and collaboration**, eliminating the need for manual synchronization between separate tracking systems.  
- **Unified tracking of all artifacts**, including source code, documentation updates, test results, and CI/CD workflows, ensuring full traceability of changes.  
- **Flexibility for internal teams** to organize their work using **GitHub’s organizational units** while still maintaining alignment with broader development efforts.  
- **Automatic generation of documentation and change logs** through versioning, ensuring updates are systematically captured within the repository itself.  
- **Direct traceability between tasks, issues, and features**, as every commit, pull request, and merge request is linked with URLs and full version history.  

This structure enforces **GitHub as the single source of truth** for all development tracking, ensuring transparency, efficiency, and seamless collaboration across internal and external teams.  

### **Example**

**Overall Business (Jira Epic): Enable Personalized Bluetooth LE Audio Broadcast**

- **Goal:** Deliver a feature enabling users to connect multiple Bluetooth LE Audio headphones with personalized audio streams for an enhanced viewing experience.

**Layer Requirements:**

- **Vendor Layer (Internal Github Feature): BlueZ LE Audio Broadcast Support**
    - **Goal:** Integrate and provide a stable, functional Bluetooth LE Audio Broadcast stack with personalized stream capabilities.
    - **Tasks:**
        - Update BlueZ to support LE Audio Broadcast with personalized audio streams.
        - Develop and test necessary APIs and drivers.
        - Provide comprehensive API documentation.
- **Middleware Layer (External Github Feature): LE Audio Stream Management**
    - **Goal:** Provide a robust middleware layer that manages and abstracts the vendor-provided Bluetooth functionality for the application.
    - **Tasks:**
        - Integrate with the updated BlueZ APIs.
        - Develop and test APIs for the application layer.
        - Implement stream management logic (creation, configuration, routing).
        - Provide documentation.
- **Application Layer (Internal Github Feature): Personalized Audio Stream UI/UX**
    - **Goal:** Create an intuitive and user-friendly interface for managing personalized Bluetooth audio streams.
    - **Tasks:**
        - Design and implement the UI for headphone discovery, connection, and stream management.
        - Develop and test the application logic for controlling audio settings per stream.
        - Implement real-time stream status display.
        - Create UI/UX documentation.

---

## **Feature Requests, Bug Reporting, and Task Tracking**

All feature requests, bug reports, and tasks are tracked in **GitHub Issues** within the **RDK Central open tracking system**. This ensures complete visibility of work progress, fosters collaboration among contributors, and aligns with the community-driven development model. These GitHub-based tracking mechanisms are publicly accessible and help maintain transparency across all contributions.

!!! Tip
    The following templates are already enabled in RDK Central

### **Features**

Feature requests should be well-defined to ensure clarity in their purpose, scope, and impact. The following feature request template is actively used within RDK Central:

#### **Feature Request Template**

- **Title Format:** `Feature:<Short summary of the problem>`
- **Issue Type:** Set as `FEATURE`
- **Labels:** Apply relevant labels such as `Documentation`, `Enhancement`, `Bug`, etc.
- **Project Field:** Assign to an appropriate project. Example project templates can be found [here](https://github.com/orgs/rdkcentral/projects/28/views/1)

#### **Description**

- **Problem/Opportunity:** Describe the user need or problem this feature solves/improves.
- **Proposed Solution:** Explain your idea for the feature and how it addresses the problem/opportunity.

#### **Acceptance Criteria (Optional)**

- Specific condition 1
- Specific condition 2
- ...

#### **Additional Notes (Optional)**

- Mockups, sketches, wireframes, etc.

### **Tasks**

Tasks encompass all actionable work within GitHub Issues, including feature development, improvements, maintenance, and refactoring. To align with RDK Central's best practices, tasks should follow the recommended template, which is already in use within the community:

#### **Task Template**

- **Title Format:** `Task:<Short summary of the problem>`
- **Issue Type:** Set as `TASK`
- **Labels:** Apply relevant labels, such as `documentation` or `enhancement`
- **Project Field:** Assign to an appropriate project. Example project templates can be found [here](https://github.com/orgs/rdkcentral/projects/28/views/1)

#### **Description**

- Clearly state the goal of the task for better understanding and traceability.

#### **Notes (Optional)**

- Include any helpful information, such as environment details or relevant links.

### **Bug Reporting**

Bugs should be reported following a standardized format to ensure clarity, traceability, and reproducibility. The following bug template is actively used within RDK Central:

#### **Bug Template**

- **Title Format:** `Bug:<Short summary of the problem>`
- **Issue Type:** Set as `BUG`
- **Labels:** Apply relevant labels, such as `Bug`
- **Project Field:** Assign to an appropriate project. Example project templates can be found [here](https://github.com/orgs/rdkcentral/projects/28/views/1)

#### **Description**

- **Problem:** Clearly stating the problem upfront is crucial for understanding the issue.
- **Steps to Reproduce:** If applicable, this is essential for bugs, allowing others to replicate the problem and verify solutions.
- **Expected Behaviour:** Explain what should happen instead of the current behaviour.
- **Actual Behaviour:** Describe what is currently happening, highlighting the discrepancy with the expected behaviour.

#### **Notes (Optional)**

- Include any helpful information, such as environment details, links, screenshots, error messages, console logs, or relevant code snippets.

---

## **Why Attach a GitHub Project to Tasks?**

Attaching a GitHub Project to tasks provides a structured approach to tracking development progress, status control, and workflow automation. GitHub Projects are used to:

- **Track the development of features** in use in GitHub, ensuring clear visibility of work status.
- **Provide control over task progress** by defining statuses (e.g., To Do, In Progress, Completed).
- **Enable tracking configurations** for workflow automation and management.
- **Support timeframes, estimates, and planning**, ensuring that work is executed within expected delivery schedules.

More information on GitHub Projects can be found [here](https://docs.github.com/en/issues/planning-and-tracking-with-projects/learning-about-projects/about-projects).

---

## **Conclusion**

By structuring work in an open, organized, and transparent manner, engineering teams can achieve long-term scalability, reduce maintenance overhead, and manage technical debt effectively. This approach fosters a sustainable development model while maintaining alignment with broader business and compliance goals.

This white paper aims to guide community-driven open-source software development efforts, ensuring efficient goal setting, transparent progress tracking, and effective collaboration.

---

**Author**: *Gerald Weatherup*  
**Date**: *20 March 2025*

For questions or suggestions on implementing branching strategies, please contact the Architecture team.