# Contributing to This Repository

Thank you for your interest in contributing! This project follows the [Achieving Engineering Goals](https://rdkcentral.github.io/rdk-halif-aidl/whitepapers/engineering_goals/).

Your contribution workflow depends on whether you're a Tier 1 or Tier 2 developer.

## Tier 1 Developers

Tier 1 developers use a **shared branching model** within the main repository.

1. **Branching**
   Create branches directly in the main repo using the format:  

   ```
   feature/<issueid>-<short-description>  
   ```

   These are short-lived branches for active development.

2. **Integration**  
   - Open a **pull request** targeting the appropriate short-lived branch.
   - Review, test, and merge after approvals.

3. **Responsibility**  
   - Ensure CI passes before merge.
   - Validate on supported hardware.
   - Maintain branch hygiene (delete merged branches, etc).

---

## Tier 2 Developers

Tier 2 developers use a **forking model**.

1. **Fork**  
   Fork the main repository to your own namespace.

2. **Branching**  
   In your fork, create a branching methodology that works for you, example of which is :-

   ```
   feature/<issueid>-<short-description>  
   ```

3. **Development**  
   - Develop and test changes locally or on provided platforms.

4. **Pull Request**  
   - Submit a PR from your forked branch to the appropriate long-lived branch of the upstream repo.
   - Coordinate with the `.github/CODEOWNERS` team for review and merge.

---

## Common Guidelines (All Contributors)

### Commit Messages

Use consistent and meaningful messages:

```
<type>: <summary>
```

Examples:

```
fix: prevent crash on null pointer dereference  
feature: add support for Dolby Vision
```

### Code & Quality

- Follow project style guides and formatting.
- Include tests and documentation where applicable.
- Validate changes before submitting PRs.

### Licensing

Ensure code complies with repository licensing terms. Don’t include third-party code without proper review.
