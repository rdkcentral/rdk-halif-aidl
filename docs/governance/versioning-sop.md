# HAL Delivery & Versioning Standard Operating Procedure

## 1. Goal: AIDL Baseline 1.0

This repository contains all RDK HAL interface definitions written in AIDL. The
objective is to drive every interface through a structured review process until
every component is frozen at **AIDL Baseline** — the production-ready release
that SoC vendors and OEMs implement against. Components are frozen
individually as they become ready; the full baseline is reached when all
components have been frozen.

The lifecycle has two distinct phases:

| Phase | Versions | What is happening |
|-------|----------|-------------------|
| **Pre-Baseline** (current) | `0.<gen>.<minor>.<patch>` | Interfaces are being defined, reviewed, and iterated. Breaking changes are expected — that is the point of this phase. Each component moves RED → AMBER → GREEN through 14+5 review cycles. |
| **Post-Baseline** | AIDL version `1`, `2`, `3`... | Interfaces are **frozen**. All changes are 100% backwards compatible (AIDL stable versioning). A breaking change requires creating an entirely new module. |

We are currently in the **Pre-Baseline** phase. Getting the interfaces right
now is critical — once a component is frozen and moves to AIDL versioning,
its contract is permanent.

---

## 2. Component Structure

Every HAL is managed as a self-contained component. All code, documentation, and
metadata reside within a versioned subdirectory:

```text
<component>/
  metadata.yaml            # Single Source of Truth (component-level)
  current/
    <ComponentName>.aidl   # Interface definition(s)
    docs/                  # Component-level documentation
```

For VSI (Virtual System Interface) components, the structure nests under `vsi/`:

```text
vsi/<component>/metadata.yaml
```

The `metadata.yaml` file sits at the component root (not inside `current/`)
because it describes component-level state — RAG status, reviewer sign-off,
lifecycle dates — rather than a specific version snapshot. It is the **Single
Source of Truth** for every component.

---

## 3. Versioning Scheme

> **Important:** The component version in `metadata.yaml` tracks the
> **interface contract** for that individual component. It is independent of
> the git repository version, which tracks changes across all 33 components
> via commits and tags. A single git commit may update one component's version
> without affecting any other.

### Pre-Baseline: `0.<generation>.<minor>.<patch>`

During pre-baseline, version numbers use a 4-part scheme. Breaking changes are
expected and normal during this phase — the purpose is to iterate until the
interface is right.

| Field | Meaning | Bumped when |
|-------|---------|-------------|
| `0` | Pre-baseline prefix (always `0` until AIDL freeze) | Never — changes to `1` at freeze |
| `generation` | Architectural era | Breaking change to the interface |
| `minor` | ABI-compatible enhancement counter | Non-breaking feature or method added |
| `patch` | Documentation or trivial fix counter | No interface change |

**Examples:**

- `0.0.0.1` — Initial definition (generation 0), first revision
- `0.1.0.0` — Entered generation 1 (first full design cycle complete)
- `0.1.1.0` — ABI-compatible enhancement added to generation 1
- `0.1.1.1` — Documentation fix (no interface change)
- `0.2.0.0` — Breaking change since generation 1 → new generation

**Rules:**

- A breaking change (method signature change, removed method, changed semantics)
  bumps the generation and resets minor + patch to `0.0`
- A non-breaking addition (new method, new enum value) bumps minor and resets
  patch to `0`
- A documentation-only change bumps patch

### How PRs Drive the Version Bump

Pre-baseline component versions advance one PR at a time. The bump that each
PR implies is signalled by **labels on the PR**. `scripts/configure_pr.sh`
applies them automatically from the PR title and changed files; reviewers may
add or correct them as needed.

Every PR carries **exactly one change-class label**. The label is the
single signal of intent — there is no implicit-default class. An
unlabelled PR is an unfinished PR.

The label names mean what the version fields mean — the label tier IS the
field it bumps:

| PR label | Implied bump | Applied when |
| --- | --- | --- |
| `Major Change` | **Major** (`0.g.m.p` → `0.(g+1).0.0`) | Breaking interface change — conventional-commit `!:` marker in the PR title (e.g. `feat(avclock)!: ...`): renames, removals, signature changes, design re-direction. Auto-applied by `configure_pr.sh` on the `!:` marker. |
| `Minor Change` | **Minor** (`0.g.m.p` → `0.g.(m+1).0`) | Backwards-compatible addition — the default for real interface work: new methods, new fields appended to parcelables, new enum values added with fallback handling, new sub-interfaces. |
| `documentation` | **Bugfix** (`0.g.m.p` → `0.g.m.(p+1)`) | The interface surface is untouched — doc tweaks, metadata corrections, HFP YAML changes, comment-only refactors, trivial non-interface fixes. Auto-applied by `configure_pr.sh` when every changed file is doc-like (see `is_doc()`). |

A PR that carries **no** change-class label but whose linked (closing)
issue is GitHub type **`Bug`** implies the bugfix bump — the native issue
type carries the signal, no label needed. An explicit change-class label
always wins over the issue type (a bug whose fix changes the interface
surface carries `Minor Change` or `Major Change` accordingly, and the
structural audit checks the declared class either way).

The `Breaking Change` label is retired — breaking IS the major bump, so a
separate label was redundant. `scripts/release.sh` still accepts it as a
deprecated alias of `Major Change` while historical and in-flight PRs
migrate; do not apply it to new PRs.

If multiple change-class labels are accidentally applied to a single
PR, `scripts/release.sh` resolves by severity: `Major Change` >
`Minor Change` > `documentation`. Reviewers should still clean the
labelling so each PR carries exactly one.

The PR author edits the component's `metadata.yaml` `version:` to the new
value as part of the PR's diff. Reviewers check that the version bump matches
the label and the actual change.

#### The `CR` Label (independent — not a change-class)

`CR` (Change Request) marks an **ABI change** that must go through wider review
and deliberate scheduling. It is a **process/governance** label, **independent**
of the change-class above. The change-class answers *"how does the version
number move?"*; `CR` answers a **different** question — *"is this an ABI change
that needs wider review and separate scheduling?"* The two axes are orthogonal,
so a `CR` carries a change-class label alongside it (an ABI change carries
`Major Change`).

A PR/issue tagged `CR` requires:

1. **Wider review sign-off on approval** — beyond the default CODEOWNERS review
   team, the relevant `team:*` architecture reviewers must sign off.
2. **Separate release scheduling** — it is not folded into the normal cohort
   release sweep; it is scheduled into a release deliberately.

`CR` does **not** affect the version bump — `scripts/release.sh` never reads it.
It is therefore *not* a change-class: `Major Change` remains the class that
drives the major bump, and conflating the two would break the label-driven
bump logic.

#### The Subsume Rule

Between releases, `metadata.yaml` `version:` represents the **intent for the
next release** — the highest bump that has been declared since the last
release tag. A PR bumps `version:` *only if its change is more significant
than what is already pending.*

| Last released | Already pending on `develop` | This PR is… | Action |
|---|---|---|---|
| `0.1.0.0` | `0.1.0.0` (unchanged since release) | patch | bump → `0.1.0.1` |
| `0.1.0.0` | `0.1.0.0` | minor | bump → `0.1.1.0` |
| `0.1.0.0` | `0.1.0.0` | breaking | bump → `0.2.0.0` |
| `0.1.0.0` | `0.1.1.0` (a prior PR already bumped minor) | another minor | **no bump — already covered** |
| `0.1.0.0` | `0.1.1.0` | patch (smaller than pending) | **no bump — subsumed by minor** |
| `0.1.0.0` | `0.1.1.0` | breaking | bump → `0.2.0.0` (subsumes the minor) |
| `0.1.0.0` | `0.2.0.0` (a prior PR already bumped breaking) | minor or patch | **no bump — already covered** |
| `0.1.0.0` | `0.2.0.0` | another breaking | **no bump** (one generation tick per release window) |
| new component (no prior release) | `0.1.0.0` | anything | no bump — first release is `0.1.0.0` regardless of how many PRs accumulate |

**Net rule:** `next_version = max(current_pending, this_PR_would_imply)`. The
release version is the aggregate delta since the last tag, not a per-PR
count. Multiple breaking changes in a single release window batch into one
generation; multiple feature additions batch into one minor; multiple
docs-only changes batch into one patch.

This is **human-side discipline**, not script-enforced. Reviewers verify
that the bump (or non-bump) is appropriate for the PR's change.

#### When the Snapshot is Created

`metadata.yaml` `version:` is a **forward-looking declaration** of what the
next release will tag the component as. The `<component>/<version>/`
snapshot directory is **not** created in feature PRs. It is materialised at
release time by the top-level `./release.sh`, which reads `metadata.yaml`
and copies `current/` to `<version>/`.

Feature PRs touch `current/` only:

- `current/com/.../*.aidl` — authored AIDL source
- `current/docs/<component>.md` — documentation
- `current/CMakeLists.txt`, `current/interface.yaml`, `current/hfp-*.yaml` —
  build wiring + manifest + hardware feature profile

The toolchain-generated C++ bindings (`current/include/*.h` and
`current/src/*.cpp`) are not in this list — see
[Generated Code is Not Committed in `current/`](#generated-code-is-not-committed-in-current) below.

Multiple PRs can accumulate bumps on `develop` without any of them creating
snapshot directories. The next release event (`release.sh` run during
release prep) materialises all of the snapshots together and the repo is
tagged.

#### Pre-Tag Structural Audit

The release flow enforces the structural audit itself: every stage and
`--apply` invocation first audits the components being written and refuses
to proceed while their structural class, PR labels and `metadata.yaml`
disagree. The full-repo sweep is available at any time:

```bash
./scripts/release.sh --audit   # every component; non-zero exit on any flag
```

For **every** component — including ones untouched since the last release —
the audit dumps the canonical AIDL surface of the last frozen snapshot and
of `current/` (binder toolchain `aidl_ops dump-surface`), classifies the
structural difference (`diff-surface` emits `breaking` / `major` / `none`,
where `major` means additive and the audit displays it as such;
surface-identical trees whose sources still differ count as doc-only), and
cross-checks three signals per component:

| Signal     | Source                                         |
|------------|------------------------------------------------|
| Structural | what the AIDL actually changed (code truth)    |
| Label      | the change class PR labels imply               |
| Declared   | `metadata.yaml` `version:` (pre-bumped by PRs) |

A row is flagged when the label class contradicts the structural class,
when `metadata.yaml` declares a version the structural class doesn't
support, or when an era ≥ 1 component classifies breaking (forbidden — a
breaking change there requires a new component). Flagged rows print the
exact structural diff (method/field level) so the fix — relabel the PR,
correct `metadata.yaml`, or revert the AIDL — is evident from the output.
Release tagging proceeds only on a clean `--audit --strict` pass.

#### Generated Code is Not Committed in `current/`

`current/include/*.h` and `current/src/*.cpp` are toolchain output —
regenerated from the module's AIDL by `./build_modules.sh` (or the
underlying linux_binder_idl) on every build. They are **`.gitignore`d
under `current/`** and never tracked in git on develop.

Generated bindings only enter the repo when `./release.sh` freezes a
cohort — at release time, the script regenerates each module's bindings
and commits them into the new immutable `<module>/<version>/include/`
and `<module>/<version>/src/` directories alongside the snapshot's
AIDL. Frozen `<version>/` snapshots are the consumption artifact;
consumers pin to them (`common@0.1.0.0`), not to `current/`.

##### The rule

> Feature PRs touch only AIDL, docs, and manifest/HFP under `current/`.
> They never `git add` files in `current/include/` or `current/src/`.
> The build regenerates those locally; the `.gitignore` keeps them out
> of commits.

##### Why this model

Treating generated output as a versioned artifact in `current/`
conflated two distinct concerns and caused a class of recurring
problems:

1. **Drift between committed bindings and the AIDL** that produced
   them (#564) — a stale committed `.h` paired with a freshly-
   regenerated `.cpp` mid-rebuild produced cryptic "no declaration
   matches" errors. The toolchain silently rewrote headers at build
   time, so a successful build was not proof that the committed
   snapshot was consistent.
2. **Cascade-commit discipline per PR** — every AIDL change had to
   regenerate every downstream module's bindings and commit them.
   Fragile, easily forgotten.
3. **Noisy PR diffs** — 10 lines of authored AIDL produced ~200 lines
   of regenerated bindings. Reviewers lost focus on the actual
   surface change.

The new model eliminates all three: there is no committed `current/`
binding to drift from, no per-PR cascade because the regen happens at
build time locally, and PR diffs show only authored content.

##### What's still committed where

- `current/com/.../*.aidl` — authored AIDL ✅ committed
- `current/docs/`, `current/CMakeLists.txt`, `current/interface.yaml`,
  `current/hfp-*.yaml` — authored config ✅ committed
- `current/include/`, `current/src/` — toolchain output ❌
  `.gitignore`d, regenerated locally on every build
- `<module>/<version>/com/`, `<module>/<version>/include/`,
  `<module>/<version>/src/`, etc. — frozen snapshot ✅ committed
  (write-once at release time by `./release.sh`)

##### Enforcement

- **Local:** `./tests/smoke/smoke_test.sh` asserts no files are tracked
  under `*/current/include/` or `*/current/src/` after
  `[1/4] ./build_modules.sh all --clean`. Any regression (someone
  bypassing `.gitignore` with `git add -f`, or a new generator
  output not covered by the rule) trips the check.
- **Release:** `./release.sh` is the only entry point that may
  commit generated bindings, and only into frozen `<version>/`
  directories. Invocation: `./scripts/release.sh --apply --release-version X.Y.Z` runs the full pipeline — per-component `metadata.yaml`
  bumps, per-bumped-component snapshot creation (regen-during-freeze,
  then `cp -r current/` to `<version>/`), `mkdocs.yml` nav update,
  and `release/X.Y.Z` branch with matching `X.Y.Z` tag. No-op when
  no component is bumped (no branch, no tag, no doc edits). Suppress
  individual steps for testing with `--no-snapshot`, `--no-mkdocs`,
  or `--no-git`. Implemented in #513.

This separation means a single coherent release contains all of the
component changes from the release window batched into one set of new
snapshots — see [Release Cadence](#release-cadence) below.

#### Release Cadence

Releases are **milestone-driven** with **patch releases on demand**:

- A new milestone (e.g. `0.20.0 - Convergance`) closes when its content is
  complete. A release is then cut from `develop` to `main`, `release.sh`
  materialises all the pending component snapshots, and the repo is tagged.
- An urgent fix that cannot wait for the next milestone is shipped as a
  patch release (e.g. `0.15.1`) using the same release ceremony.

Releases are **not** cut on every PR merge. Multiple changes batch into one
coherent release narrative. See the [0.20.0](../releases/0.20.0.md) and
[0.15.0](../releases/0.15.0.md) release notes for the pattern.

### Post-Baseline: AIDL Stable Versioning

Once a component reaches AIDL Baseline and is frozen, it follows **AIDL
stable interface versioning**. This is a fundamentally different model:

| Rule | Detail |
|------|--------|
| **Version = single integer** | `1`, `2`, `3`, `4`... |
| **100% backwards compatible** | Every version must be fully backwards compatible with all previous versions. Existing methods, signatures, and semantics cannot change. |
| **Additive only** | New methods and types can be added. Nothing can be removed or modified. |
| **Breaking change = new module** | If a breaking change is unavoidable, a new module is created (e.g. `hdmi_input` → `hdmi_input_v2`). The original module continues to exist. |

**This is why getting interfaces right pre-baseline is critical.** Once frozen,
the interface contract is permanent. A mistake after freeze means carrying a new
module indefinitely.

---

## 4. RAG Status & What It Means

Each component carries a RAG status in its `metadata.yaml`:

| Status | Meaning | Who acts |
|--------|---------|----------|
| 🔴 **RED** | Not ready for review. Requirements gathering, strategy decisions, or foundational drafting still in progress. | Architecture team defines scope and direction. |
| 🟡 **AMBER** | Under active ingestion. The interface is being defined and iterated. It will enter a 14+5 sprint review cycle as soon as it is ready. | Architecture drives design iteration; reviewers prepare for the sprint window. |
| 🟢 **GREEN** ("Implementable") | Reviewed and approved. The interface is stable on `develop`. SoC vendors and OEMs can begin or continue implementation. | SoC/OEM teams consume the interface. Changes require a new review cycle. |

### The Journey to GREEN

```text
RED  ──────────>  AMBER  ──────────>  GREEN
                    │                    │
 Requirements       │   14+5 Review     │   Stable on develop.
 & strategy         │   Cycle(s)        │   SoC implementation
 decisions          │                    │   can proceed.
                    │                    │
                    └── may cycle ──────>┘
                        multiple times
```

A component may go through multiple AMBER review cycles before reaching GREEN.
Feedback from one cycle may require design iteration and a subsequent cycle.

---

## 5. The "14+5" Accelerated Delivery Cycle

All HAL interface changes move through a strictly time-boxed review lifecycle.

### Phase A: 14-Day Open Review Window

- A Pull Request is published and assigned to the mandatory reviewers plus the
  relevant domain team.
- All technical feedback must be submitted within **14 calendar days**.
- **Silence equals consent.** If no feedback is provided within the window, the
  component progresses to Phase B as "accepted."

### Phase B: 5-Business-Day Resolution Sprint

Immediately following the 14-day review:

| Day | Activity |
|-----|----------|
| Days 1–3 | **Implementation.** The HAL Lead triages feedback and implements required changes. |
| Day 4 | **Sanity check.** Updated interface is re-shared for a final 24-hour verification. No new feature requests permitted. |
| Day 5 | **The Merge.** `metadata.yaml` is updated to GREEN, code is merged to `develop`. |

### Lifecycle Tracking in Metadata

The `lifecycle` section in `metadata.yaml` records the active cycle dates:

```yaml
lifecycle:
  review_started: 2026-03-10      # Day the PR was opened for review
  review_deadline: 2026-03-24     # review_started + 14 calendar days
  target_green_date: 2026-03-31   # review_deadline + 5 business days
```

When no cycle is active, all dates are set to `~` (null). The
`scripts/pr_cycle.sh` tool manages these dates:

```bash
# Start a review cycle (defaults to today)
./scripts/pr_cycle.sh <component> --start [YYYY-MM-DD]

# End a cycle (clear dates for one component)
./scripts/pr_cycle.sh <component> --stop

# Mass reset all lifecycle dates
./scripts/pr_cycle.sh --clear
```

Only lifecycle dates are changed — RAG status and reviewer states are managed
separately through the PR and merge process.

---

## 6. Pre-Baseline: The Path to AIDL Baseline 1.0

### Current State

The repository contains **33 components** across two responsibility types:

| Type | Responsibility |
|------|---------------|
| **SOC** | SoC vendor implements the interface |
| **OEM** | OEM/platform team implements the interface |

#### SOC Components (15)

| Component | Description |
|-----------|-------------|
| `audiodecoder` | Audio decoder resource management and codec format support |
| `audiomixer` | Audio mixing and routing for multi-stream output |
| `audiosink` | Audio output rendering and sink device management |
| `avbuffer` | AV buffer allocation and secure video path management |
| `avclock` | Audio/video clock synchronization and timing control |
| `hdmicec` | HDMI CEC protocol messaging and device control |
| `hdmiinput` | HDMI input port management and signal detection |
| `hdmioutput` | HDMI output port configuration and display control |
| `planecontrol` | Graphics and video plane composition control |
| `videodecoder` | Video decoder resource management and codec support |
| `videosink` | Video output rendering and display sink management |
| `vsi/crypto` | HAL lower-layer cryptography and security API requirements |
| `vsi/graphics` | Graphics subsystem and display pipeline interface |
| `vsi/kernel` | Kernel interface strategy and system abstraction |
| `vsi/keyvault` | HAL lower-layer key vault and encrypted storage requirements |

#### OEM Components (17)

| Component | Description |
|-----------|-------------|
| `boot` | Boot reason tracking and reboot management |
| `broadcast` | Broadcast tuner and RF frontend interface |
| `common` | Common types, enumerations, and shared interface definitions |
| `compositeinput` | Composite video input capture and control |
| `deepsleep` | Deep sleep and low-power state management |
| `deviceinfo` | Device information and platform capability reporting |
| `ffv` | Far-field voice capture and mic array processing |
| `firmwareupdate` | Update lifecycle for multiple firmware types at multiple locations across the system |
| `indicator` | LED and visual indicator state management |
| `panel` | Front panel display and button control |
| `r4ce` | RF4CE remote control protocol and pairing |
| `sensor` | Hardware sensor data acquisition and monitoring |
| `vsi/abstractfilesystem` | Abstract file system interface and storage abstraction |
| `vsi/bluetooth` | Bluetooth stack integration and profile support |
| `vsi/filesystem` | File system layout standards and partition management |
| `vsi/linuxinput` | Linux input subsystem and event handling |
| `vsi/wifi` | Wi-Fi driver integration and network management |

Each component is independently tracked through the RED → AMBER → GREEN
pipeline. The automated [RAG Status Report](https://github.com/rdkcentral/rdk-halif-aidl/blob/develop/RAG_STATUS_REPORT.md) provides
a live view of overall progress.

### What "GREEN at 0.x" Means

GREEN is the status referred to externally as **"Implementable"** — the interface
is ready for SoC/OEM implementation.

A GREEN component at version `0.x.y.z` means:

1. The interface has been reviewed and approved by all assigned stakeholder teams
2. It is stable on the `develop` branch
3. SoC vendors and OEMs **can begin implementation**
4. The interface definition is **not yet frozen** — it may still evolve through
   further review cycles if required, but the current design is considered
   production-viable

GREEN at `0.x` is not the same as frozen. Breaking changes are still possible
(bumping the generation number). This flexibility is deliberate — we need to
get the interfaces right before the permanent freeze.

### Freezing a Component at AIDL Baseline

The freeze happens **per-component**, not as a monolithic repo-wide event. A
component that is ready should not be held back because others are still
iterating. This means the repository will contain a mix of pre-baseline
(`0.x.y.z`) and frozen (AIDL integer) components at the same time.

**A component is ready to freeze when:**

1. **Status is GREEN** — the interface has been reviewed and approved
2. **Generation > 0** — the interface has been through at least one full
   design cycle (not still at initial definition)
3. **No unresolved breaking change flags** — the current design is considered
   final
4. **VTS alignment confirmed** — the VTS Team has validated test strategy
5. **RTAB sign-off** — the RTAB Group has reviewed for system-level alignment
6. **Architecture sign-off** — Architecture confirms the interface is ready
   for permanent commitment

**On freeze:**

- The component's AIDL version is set to `1` (AIDL stable versioning)
- The pre-baseline `0.x.y.z` version in `metadata.yaml` is replaced by the
  AIDL version integer
- Post-Baseline rules take effect for that component — all future changes must
  be 100% backwards compatible, or a new module must be created (see Section 7)

**Full AIDL Baseline** is reached when every component in the repository has
been individually frozen. This is the milestone, not a gate.

---

## 7. Post-Baseline: Maintaining AIDL After Freeze

Once a component is frozen at AIDL Baseline, it follows AIDL stable
interface versioning. The rules are strict and non-negotiable.

### Permitted Changes (Additive Only)

All changes after freeze must be **100% backwards compatible**:

- Add new methods to an existing interface
- Add new types, enums, or parcelables
- Add new interfaces within the same module
- Documentation updates

These go through a standard 14+5 review cycle. The AIDL version integer is
incremented (e.g. version `1` → `2`). The component remains GREEN.

### Breaking Changes: New Module Required

If a change cannot be made backwards-compatibly, the original interface
**cannot be modified**. Instead:

1. A new module is created alongside the original
   (e.g. `hdmi_input` → `hdmi_input_v2`)
2. The original module continues to exist and must remain supported
3. The new module goes through the full RED → AMBER → GREEN lifecycle as a
   new component
4. SoC vendors and OEMs are notified and must support both versions during
   the transition period

This is by design — it forces careful interface design pre-baseline and ensures
that deployed implementations are never broken by upstream changes.

### Breaking Changes

Breaking changes are signalled via the `Major Change` label on the PR or
issue at creation time. This is visible to reviewers immediately and drives
review prioritisation. When the change is merged and the component is released,
the version is bumped accordingly (major bump for pre-baseline, new module
for post-baseline).

---

## 8. Stakeholder Management & Roles

### Mandatory Reviewers (all components)

| Team | Responsibility |
|------|---------------|
| **Architecture** | Final decision authority on feedback. Drives the 5-day resolution window. |
| **RTAB_Group** | System-level alignment and stakeholder visibility above the engineering level. |
| **Product_Architecture** | Cross-component alignment and product-level sign-off. |
| **VTS_Team** | Validation and test strategy review for all components. |

### Domain Reviewers (assigned per component)

| Team | Domain |
|------|--------|
| **AV_Architecture** | Audio/Video pipeline components |
| **Broadcast_Team** | Broadcast and tuner components |
| **Control_Manager_Architecture** | Remote control and input management |
| **Graphics_Architecture** | Graphics, display, and composition |
| **Connectivity_Architecture** | Bluetooth, Wi-Fi, and connectivity |
| **Kernel_Architecture** | System, kernel, boot, and platform |

### Reviewer Status Values

Each reviewer team's sign-off is tracked in `metadata.yaml`:

| Value | Icon | Meaning |
|-------|------|---------|
| `pending` | ☐ | Review not yet started |
| `in_review` | 🔍 | Actively reviewing during the 14-day window |
| `changes_requested` | 🔁 | Feedback given, awaiting resolution in the 5-day sprint |
| `recheck` | 🔄 | Previously reviewed, needs re-verification |
| `reviewed` | ✅ | Signed off and approved |
| `abstained` | ➖ | Not applicable (interface outside this team's domain) |

### External Stakeholders

- **SoC Vendors:** Must provide feasibility feedback during the 14-day review
  window. They consume GREEN baselines as production-ready interfaces.
- **Middleware (MW):** The HAL is the control plane. MW must adapt to the HAL
  definition once it reaches AMBER/GREEN status.

---

## 9. Tooling & Automation

### metadata.yaml — Single Source of Truth

Every component directory contains a `metadata.yaml` that captures:

- **Component identity** — name, version, generation, type (SOC/OEM)
- **RAG status** — RED, AMBER, or GREEN
- **Lifecycle dates** — review start, deadline, and target GREEN date
- **Scope** — high-level architectural responsibilities
- **Notes** — priority, status detail, required actions, risk, owners
- **Reviewers** — per-team sign-off status
- **Impact** — breaking change and multi-view sync flags

### RAG Status Report

The [RAG Status Report](https://github.com/rdkcentral/rdk-halif-aidl/blob/develop/RAG_STATUS_REPORT.md) is auto-generated from all
`metadata.yaml` files:

```bash
./scripts/generate_rag_report.sh
```

It provides:

- Overall progress summary (GREEN/AMBER/RED counts)
- Per-team review status columns for GREEN components
- Lifecycle deadline tracking for AMBER components
- Priority-ordered action items for AMBER and RED components

### PR Cycle Manager

```bash
./scripts/pr_cycle.sh
```

Manages 14+5 lifecycle dates. See Section 5 for usage.

### GitHub Labels

```bash
./scripts/setup_labels.sh [--dry-run]
```

Creates labels on GitHub and cleans up any legacy labels from earlier versions.
Idempotent — safe to re-run.

| Label | Purpose |
|-------|---------|
| `component:<name>` | Maps PRs to a specific HAL/VSI component (auto-detected from metadata.yaml) |
| `Major Change` | Breaking interface change — bumps major |
| `Minor Change` | Additive, backwards-compatible interface change — bumps minor (the default for real work) |
| `documentation` | Doc-only / metadata-only / comment-only change — bumps bugfix |
| `CR` | Change Request — ABI change needing wider review sign-off + separate release scheduling (independent of change-class; no bump effect) |
| `scope:infrastructure` | Repo tooling, CI/CD, governance |
| `scope:overview` | Tracking ticket spanning multiple components |

Every PR carries **exactly one** of `Major Change` / `Minor Change` /
`documentation`. The label signals the bump intent; the PR author bumps
`metadata.yaml` `version:` accordingly as part of the PR diff (see
[How PRs Drive the Version Bump](#how-prs-drive-the-version-bump) above
for the full subsume rule and snapshot-timing model):

| Label | Version bump | Example |
|-------|-------------|---------|
| `Major Change` | Bump major, reset minor + bugfix | `0.1.2.1` → `0.2.0.0` |
| `Minor Change` | Bump minor, reset bugfix | `0.1.0.0` → `0.1.1.0` |
| `documentation` | Bump bugfix | `0.1.1.0` → `0.1.1.1` |

Release-time execution (manual):

```bash
# Snapshot every component whose metadata.yaml version: differs from
# its currently-released <module>/<version>/ directory. Idempotent.
./release.sh
```

`./release.sh` reads `metadata.yaml` `version:` verbatim — it does not
compute bumps; that's the PR author's job, signalled by the label and
validated by reviewers. Snapshots materialise only at release time, never
in feature PRs.

All other state (RAG status, reviewer sign-off, lifecycle dates) is tracked
in `metadata.yaml` — the Single Source of Truth. PRs are assigned directly
to GitHub teams for review.
