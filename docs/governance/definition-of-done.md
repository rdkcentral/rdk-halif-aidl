# Definition of Done

Derived from the [HAL Delivery & Versioning SOP](versioning-sop.md). Each gate
must be satisfied before a component can advance.

> **TL;DR:** Three gates — (1) AIDL files + metadata ready → AMBER,
> (2) 14+5 review cycle complete, all reviewers signed off → GREEN
> ("Implementable"), (3) GREEN + generation > 0 + final sign-offs →
> frozen at AIDL Baseline 1.0.

**Gate indicators in `metadata.yaml`:**

| Gate | Indicated by |
|------|-------------|
| Gate 1 passed | `status: AMBER` (or `GREEN`) |
| Gate 2 passed | `status: GREEN` |
| Gate 3 passed | Version is AIDL integer (`1`, `2`, ...) instead of `0.x.y.z` |

---

## Gate 1: RED → AMBER

**Ready to enter review when:**

- [ ] AIDL interface file(s) exist in `<component>/current/`
- [ ] Interface is feature-complete enough for stakeholder feedback
- [ ] `metadata.yaml` is complete and valid (all required fields populated)
- [ ] Architecture team has approved the component for review entry

**On transition:**

- Set `status: AMBER` in `metadata.yaml`
- Start a review cycle: `./scripts/pr_cycle.sh <component> --start`
- Open a PR with the `component:<name>` label, assigned to the relevant GitHub review teams

---

## Gate 2: AMBER → GREEN ("Implementable")

**Ready to move to GREEN when:**

- [ ] A 14+5 review cycle has been completed (Phase A + Phase B)
- [ ] All mandatory reviewers have signed off (`reviewed`) or abstained: RTAB_Group, Architecture, Product_Architecture, VTS_Team
- [ ] Assigned domain reviewer has signed off (`reviewed`)
- [ ] All PR comments resolved, no unresolved blockers
- [ ] PR labelled appropriately (`breaking-change`, `documentation-change`, or none — see [version bump rules](versioning-sop.md#9-tooling--automation))

**On transition:**

- Set `status: GREEN` in `metadata.yaml`
- Update all reviewer states to their final values
- Clear lifecycle dates: `./scripts/pr_cycle.sh <component> --stop`
- Merge the PR to `develop`
- Regenerate the RAG report: `./scripts/generate_rag_report.sh`

---

## Gate 3: AIDL Baseline Freeze (Per-Component)

The freeze is **per-component** — a component that is ready should not be held
back because others are still iterating.

**Ready to freeze when:**

- [ ] Status is GREEN
- [ ] Pre-baseline version shows generation > 0 (e.g. `0.1.x.x` or higher — the interface has been through at least one full design cycle beyond initial definition)
- [ ] No unresolved `breaking-change` PRs pending against this component
- [ ] All mandatory and domain reviewers show `reviewed` or `abstained`
- [ ] VTS Team has validated test strategy
- [ ] RTAB Group has reviewed for system-level alignment
- [ ] Architecture confirms readiness for permanent commitment

**On freeze:**

- Version set to `1` (AIDL stable versioning replaces `0.x.y.z`)
- Post-Baseline rules take effect — **all future changes must be 100% backwards compatible**
- Breaking changes after freeze require a new component (e.g. `hdmiinput` → `hdmiinput_v2`)

**Full AIDL Baseline** is reached when every component has been individually
frozen. This is a milestone, not a gate.

---

## Quick Reference

| Transition | Key Question | Who Decides |
|------------|-------------|-------------|
| RED → AMBER | Is the interface ready for review? | Architecture |
| AMBER → GREEN | Have all reviewers signed off? | Architecture + all reviewers |
| Component freeze | Ready for permanent commitment? | RTAB_Group + Architecture |
