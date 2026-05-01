# HAL Delivery & Versioning Standard Operating Procedure

> **See also:** [Definition of Done](definition-of-done.md) — checklists for
> each gate transition (RED→AMBER, AMBER→GREEN, Baseline 1.0 freeze,
> post-baseline changes).

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

#### OEM Components (18)

| Component | Description |
|-----------|-------------|
| `boot` | Boot reason tracking and reboot management |
| `broadcast` | Broadcast tuner and RF frontend interface |
| `cdm` | Content decryption module and DRM key management |
| `common` | Common types, enumerations, and shared interface definitions |
| `compositeinput` | Composite video input capture and control |
| `deepsleep` | Deep sleep and low-power state management |
| `deviceinfo` | Device information and platform capability reporting |
| `ffv` | Far-field voice capture and mic array processing |
| `flash` | Firmware image storage and update management |
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
pipeline. The automated [RAG Status Report](../../RAG_STATUS_REPORT.md) provides
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

Breaking changes are signalled via the `breaking-change` label on the PR or
issue at creation time. This is visible to reviewers immediately and drives
review prioritisation. When the change is merged and the component is released,
the version is bumped accordingly (generation bump for pre-baseline, new module
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

The [RAG Status Report](../../RAG_STATUS_REPORT.md) is auto-generated from all
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
| `breaking-change` | Breaking interface change — bumps generation |
| `documentation-change` | Documentation-only change — no interface change, bumps patch |
| `scope:infrastructure` | Repo tooling, CI/CD, governance |
| `scope:overview` | Tracking ticket spanning multiple components |

The label determines the version bump category at release time:

| Label | Version bump | Example |
|-------|-------------|---------|
| `breaking-change` | Bump generation, reset minor + patch | `0.1.2.1` → `0.2.0.0` |
| *(no label)* | Bump minor, reset patch | `0.1.0.0` → `0.1.1.0` |
| `documentation-change` | Bump patch | `0.1.1.0` → `0.1.1.1` |

Release-time execution (manual):

```bash
# Preview component version bumps since the previous release tag
./scripts/release.sh

# Apply updates to component metadata.yaml files
./scripts/release.sh --apply
```

All other state (RAG status, reviewer sign-off, lifecycle dates) is tracked in
`metadata.yaml` — the Single Source of Truth. PRs are assigned directly to
GitHub teams for review.
