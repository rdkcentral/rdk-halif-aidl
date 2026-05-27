# Versioning & Impact Control

Changes are versioned based on their impact, signalled by PR labels:

| Change Type             | Label                 | Version Impact    | Example             |
|-------------------------|-----------------------|-------------------|---------------------|
| **Breaking Change**     | `breaking-change`     | Bumps generation  | 0.1.x.x → 0.2.0.0   |
| **Feature/Enhancement** | *(no specific label)* | Bumps minor       | 0.1.0.0 → 0.1.1.0   |
| **Documentation Only**  | `documentation`       | Bumps patch       | 0.1.1.0 → 0.1.1.1   |

Labels are applied automatically by `scripts/configure_pr.sh` from the PR title (`!:` marker → `breaking-change`) and changed files (all doc-like → `documentation`). The PR author bumps `metadata.yaml` `version:` in the same PR so the declaration matches the label.

The full operational rules — the **subsume rule** (multiple PRs in one release window batch into one bump), when snapshots are created (release time, not in feature PRs), and release cadence (milestone-driven + patch-on-demand) — are in [HAL Delivery & Versioning SOP §3](../../governance/versioning-sop.md#how-prs-drive-the-version-bump).
