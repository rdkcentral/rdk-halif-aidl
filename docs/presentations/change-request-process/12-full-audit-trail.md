# Full Audit Trail

Every change is **completely traceable** from requirement through to release:

- Every git commit is via a **named branch** (`feature/{issue#}_{synopsis}`)
- Branch naming enforced, **all changes linked to a tracked issue**
- All history is **auto-generated from the issues list**
- **Release notes** detail every change and commit since the last release
- Linked to **GitHub auto-generated history** and **auto-generated changelog**

| Artefact            | What It Records                             |
|---------------------|---------------------------------------------|
| **GitHub Issue**    | Original requirement, discussion, decisions |
| **Feature Branch**  | Named branch linking commits to the issue   |
| **Pull Request**    | Review comments, approvals, CI/CD results   |
| **Changelog**       | Auto-generated changes per release          |
| **Release Notes**   | Published with every GitHub Release         |
