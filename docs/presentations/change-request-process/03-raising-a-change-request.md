# Step 1: Raising a Change Request (Ticket)

All changes begin with a **GitHub Issue** using one of the **enforced issue templates**:

| Template     | Title Format                  | Required Fields                                        |
|--------------|-------------------------------|--------------------------------------------------------|
| **Bug**      | `Bug: {summary}`             | Problem statement, Steps to Reproduce, Expected vs Actual Behaviour |
| **Feature**  | `Feature: {summary}`         | Problem/Opportunity description, Proposed Solution     |
| **Task**     | `Task: {summary}`            | Clear goal statement for traceability                  |

Each ticket is labelled and assigned to the relevant **GitHub Project** for tracking:

| Field              | Purpose                                      |
|--------------------|----------------------------------------------|
| **Component Label**| `component:{name}` - links to HAL component |
| **Impact Label**   | `breaking-change` / `documentation` / minor  |
| **Scope Label**    | `scope:infrastructure` / `scope:overview`    |

Templates and engineering goal-setting methodology are documented at:
[Engineering-Oriented Goal Setting](https://rdkcentral.github.io/rdk-halif-aidl/0.13.0/whitepapers/engineering_goals/#engineering-oriented-goal-setting)

## Public Project - Internal & External Contributors

This is a **public open-source project**. Tickets are raised by both **internal and external teams** directly on GitHub. GitHub Issues are the **single source of truth** for each component's status.

## Optional: JIRA Mirroring

A JIRA ticket can optionally be auto-raised to mirror a GitHub Issue for internal tracking purposes. However, as a public project, JIRA may not accurately reflect the current status of a single component - external contributions, comments, and review activity happen on GitHub and may not sync in real time. **GitHub remains the authoritative record.**
