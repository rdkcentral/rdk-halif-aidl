# Step 1: Raising a Change Request (Ticket)

All changes begin with a **GitHub Issue** using **enforced issue templates**:

| Template    | Title Format           | Required Fields                                |
|-------------|------------------------|------------------------------------------------|
| **Bug**     | `Bug: {summary}`      | Problem, Steps to Reproduce, Expected/Actual   |
| **Feature** | `Feature: {summary}`  | Problem/Opportunity, Proposed Solution          |
| **Task**    | `Task: {summary}`     | Clear goal statement for traceability           |

Each ticket is labelled and assigned to a **GitHub Project**:

| Field              | Purpose                                      |
|--------------------|----------------------------------------------|
| **Component Label**| `component:{name}` - links to HAL component |
| **Impact Label**   | `breaking-change` / `documentation` / minor  |
| **Scope Label**    | `scope:infrastructure` / `scope:overview`    |

See: [Engineering-Oriented Goal Setting](https://rdkcentral.github.io/rdk-halif-aidl/0.13.0/whitepapers/engineering_goals/#engineering-oriented-goal-setting)
