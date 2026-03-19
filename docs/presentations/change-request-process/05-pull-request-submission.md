# Step 3: Pull Request Submission

When a feature branch is ready, a **Pull Request** is raised:

- PR targets the **develop** branch
- Appropriate labels are applied (`breaking-change`, `documentation`, or none)
- **CODEOWNERS** file automatically assigns the `rdk-halif-aidl-pr-review-team`
- Automated CI/CD checks are triggered immediately

## Automated Gates on Every PR

| Gate                    | What It Checks                              |
|-------------------------|---------------------------------------------|
| **CLA Verification**   | Contributor has signed the licence agreement |
| **FOSSID Security**    | Open-source licence and security scan       |
| **BlackDuck Scan**     | Software composition analysis               |
| **Copyright Check**    | All files carry correct copyright headers   |

**A PR cannot be merged until all automated gates pass.**
