# Full Audit Trail

Every change is **completely traceable** from requirement through to release:

## End-to-End Traceability

- Every git commit is referenced via a **named branch** (`feature/{issue#}_{synopsis}`)
- Branch naming is enforced, ensuring **all changes are linked to a tracked issue**
- All git commits are tracked and all history is **auto-generated from the issues list**
- **Release notes** detail every change and every commit since the last release
- Release notes are linked to the **GitHub auto-generated history** and **auto-generated changelog**

## Complete Chain of Evidence

| Artefact                | What It Records                                    |
|-------------------------|----------------------------------------------------|
| **GitHub Issue**        | Original requirement, discussion, and decisions    |
| **Feature Branch**      | Named branch linking all commits to the issue      |
| **Git Commits**         | Every code change tracked and attributed           |
| **Pull Request**        | Review comments, approvals, CI/CD results          |
| **metadata.yaml**       | Reviewer sign-off states, review dates, deadlines  |
| **RAG Status Report**   | Auto-generated component status (updated on merge) |
| **Changelog**           | Auto-generated record of all changes per release   |
| **Release Notes**       | Published with every GitHub Release, detailing what has changed since the last release |
| **FOSSID / BlackDuck**  | Security and licence compliance scan results       |

**The entire history from issue creation to release is fully traceable within GitHub.**
