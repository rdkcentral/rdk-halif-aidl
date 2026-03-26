# Versioning & Impact Control

Changes are versioned based on their impact, controlled by PR labels:

| Change Type             | Label               | Version Impact    | Example             |
|-------------------------|----------------------|-------------------|---------------------|
| **Breaking Change**     | `breaking-change`   | Bumps generation  | 0.1.x.x → 0.2.0.0 |
| **Feature/Enhancement** | *(no label)*        | Bumps minor       | 0.1.0.0 → 0.1.1.0 |
| **Documentation Only**  | `documentation`     | Bumps patch       | 0.1.1.0 → 0.1.1.1 |

Version bumps are applied via the `release.sh` tooling at release time - ensuring consistent, auditable version history across all 32 components.
