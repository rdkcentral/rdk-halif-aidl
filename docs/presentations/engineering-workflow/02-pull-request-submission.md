# Step 3: Pull Request Submission

When a feature branch is ready, a **Pull Request** is raised:

- PR targets the **develop** branch
- Labels applied: `breaking-change`, `documentation`, or none
- **CODEOWNERS** auto-assigns the `rdk-halif-aidl-pr-review-team`
- Automated CI/CD checks triggered immediately

## Automated Gates on Every PR

| Gate                 | What It Checks                              |
|----------------------|---------------------------------------------|
| **CLA Verification** | Contributor has signed the licence agreement |
| **FOSSID Security**  | Open-source licence and security scan        |
| **BlackDuck Scan**   | Software composition analysis                |
| **Copyright Check**  | Correct copyright headers on all files       |
