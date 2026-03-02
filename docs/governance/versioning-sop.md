# HAL Delivery & Versioning Standard Operating Procedure

## 1. Structural Architecture: Self-Contained Components

To eliminate ambiguity, every HAL is managed as a self-contained component. All code, documentation, and metadata reside within the same versioned subdirectory. This ensures that the **Latest Version** is always distinct from **Legacy** snapshots, allowing vendors to consume code in a stable, production-like environment.

> **Note on Migration:** A full review to the current directory structure is underway to align with this componentised model. All existing HALs will be migrated into this versioned subdirectory format to ensure global consistency across the repository.

## 2. Versioning & RAG Status Logic

We utilize a two-tier numbering scheme based on the maturity of the interface. Metadata files within each folder act as the **Single Source of Truth**.

| Phase | Versioning | Meaning for Stakeholders |
| --- | --- | --- |
| **Development** | **0.1, 0.2, 0.3 ...** | Active iteration phases. Follows the "14+5" cycle. |
| **Formal Release** | **1, 2, 3, 4 ...** | Production baselines. Follows Google numbering schemes. |

### RAG Definitions (Status Field)

* **🟢 GREEN:** Baseline complete. SoC vendors start/continue implementation.
* **🟡 AMBER:** Review window active or feedback being integrated. High-priority focus.
* **🔴 RED:** Significant issues or foundational drafting. Not ready for external review.

---

## 3. The "14 + 5" Accelerated Delivery Cycle

To drive velocity and set simple expectations, all HAL updates move through a strictly time-boxed lifecycle.

### Phase A: The 14-Day Open Review Window

* **Action:** The Pull Request is published to reviewers (SoC Vendors, VTS, RTAB, Architecture, MW), everyone comments directly on the reviews.
* **Expectation:** All technical feedback must be submitted within 14 calendar days.
* **Policy:** **Silence equals consent.** If no feedback is provided within the window, the component moves to Phase B as "accepted."

### Phase B: The 5-Day "Resolution & Baseline"

Immediately following the 14-day review, the component enters a **5-business-day** finalization sprint:

1. **Days 1–3 (Implementation):** The HAL Lead triages feedback and implements required changes.
2. **Day 4 (Sanity Check):** The updated component is re-shared for a final 24-hour verification. No new feature requests are permitted.
3. **Day 5 (The Merge):** The `metadata.yaml` is updated to **GREEN**, the folder is "locked," and the code is merged.

---

## 4. Stakeholder Management & Roles

* **HAL Lead:** Final decision authority on feedback. Drives the 5-day resolution window.
* **SoC Vendors:** Must provide feasibility feedback during the 14-day window. They consume **GREEN** baselines as production-ready.
* **Middleware (MW) Team:** The HAL is the **Control Plane**. MW must react and adapt to the HAL definition once it reaches **AMBER/GREEN** status.
* **Architecture & RTAB:** Ensure high-level system alignment and provide visibility for stakeholders above the engineer level.

---

## 5. Consumption & Monitoring

* **Production Snapshots:** The Git repository serves as a live production environment. Vendors can "pin" their builds to a specific version directory to ensure stability.
* **Automated Status:** The .yaml files allow for an automated dashboard to present the RAG status of the entire HAL suite, providing a clear picture for executive-level management.
* **Load Monitoring:** Review command load is managed ensuring the feedback loop is driven differently to avoid "too slow" delivery.

This is a "Short-term Pain, Long-term Gain" strategy. To get from a confused state to a high-velocity production model, we need to draw a line in the sand.

---

# Transition Plan: The Sprint to the New Model

We will execute this in two distinct stages: the **Review Liquidation** (3 weeks) and the **Structural Migration** (1 week).

## Stage 1: Review Liquidation (Weeks 1–3)

**Objective:** Close all "Zombie" review requests and push as many HALs as possible to a **Green (0.x)** state.

* **Week 1: Triage & Ownership.** Assign every outstanding issue to a specific owner
* **Week 2: The "Hammer" Week.** Force decisions on all pending feedback. If a stakeholder hasn't responded by the end of this week, their input is waived.
* **Week 3: Final Resolution.** Apply the **5-Day Resolution** logic to the entire backlog. Any feedback that isn't implemented now is moved to a future version.

---

## Stage 2: Repository Re-Architecture (Week 4)

**Objective:** Physically move the code and documentation into the new self-contained versioned structure.

* **Directory Setup:** Create the `0.x` subdirectories for every component.
* **Artifact Migration:** Move `src/`, `docs/` into their respective versioned <component> folders.
* **Metadata Injection:** Drop the `metadata.yaml` into every folder.
* **Baseline Flip:** Formally flip the RAG status of the components to **Green (0.x)**.

---

## Stage 3: The "Go-Live" Announcement (Week 5)

Once the repo is restructured and the backlog is clear, we present the "New World Order" to the stakeholders.

> **The Message to Stakeholders:**
> *"We have cleared the legacy review backlog. The repository has been restructured for production stability. Moving forward, we are operating on a strict 14+5 day delivery cycle. If it is in a versioned folder and marked Green in the manifest, it is ready for implementation."*

---

## 🏗️ SoC Bring-Up: HAL Interface Confidence Dashboard

**Baseline:** New Architectural Era (**0.100.x**)

### 🟢 GREEN: Production Ready

*SoC vendors can behind to implement.*

| HAL Component | **New Version** | Status |
| --- | --- | --- |
| **Video Decoder** |**0.100.0** | Release Candidate 1, Clear Playback |
| **Video Sink** | **0.100.0** | Release Candidate 1, Clear Playback  |
| **Audio Decoder** | **0.100.0** | Release Candidate 1, Clear Playback  |
| **Audio Sink** | **0.100.0** | Release Candidate 1, Clear Playback  |
| **AV Clock** | **0.100.0** | Release Candidate 1  |
| **HDMI CEC** | **0.100.0** | Release Candidate 1 |
| **HDMI Input** | *0.100.0** | Release Candidate 1 |
| **HDMI Output** | **0.100.0** | Release Candidate 1 |
| **Composite Input** | **0.100.0** | Release Candidate 1 |

## OEM Functions

| HAL Component | **New Version** | Status |
| --- | --- | --- |
| **Indicator** |  **0.100.0** | Release Candidate 1 |
| **Panel** | **0.100.0** | Release Candidate 1 (Multi-View Changes Required) |
| **Motion** | **0.100.0** | Release Candidate 1 |
| **Thermal** | **0.100.0** | Release Candidate 1|
| **Device Info** | **0.100.0** | Release Candidate 1 |

---

### 🟡 AMBER: Under Active Review

*Feature complete. Within the **14+5 Day Review Window**. Implementation for early access only.*

| HAL Component | **Target Version** | Key Requirement |
| --- | --- | --- |
| **AV Buffer** | **0.100.0** | Encrypted buffer discussion required with DRM / SVP inputs |
| **Audio Mixer** | **0.100.0** | Under Review On PR |
| **Broadcast** | **0.100.1** | Under Review On PR  |
| **FFV** | **0.100.0** | Under Review On PR |
| **Deep Sleep** | **0.100.0** | Feedback Loop review required from current platform experiences |
| **Plane Control** | **0.100.0** | Re-review required |
| **Boot** | **0.100.0** | Release Candidate 1, Migrate name to RebootReason |
| **Flash** | **0.100.0** | Release Candidate 1, Migrate name to Image |

| OEM System Interfaces | Target Era | Status |
| --- | --- | --- |
| **Graphics Libraries** | **0.100.x** | Standard Linux Feature, OpenGLES /Vulcan etc.  Documentation Required|
| **Bluetooth** | **0.100.x** | Standard Linux Feature, Documentation Required |
| **WPA Supplicant** | **0.100.x** | Standard Linux Feature, Documentation Required |
| **File System** | **0.100.x** | Standard Linux Feature, Layout documentation and usage standards need reviewing |
| **Abstract File System** | **0.100.x** | Standard Linux Feature, Documentation Required, DMCrypt, eCrypFS etc |
| **Linux Input** | **0.100.x** | Standard Linux Feature, Documentation Required |
| **Kernel** | **0.100.x** | Standard Linux Feature, Strategy Required, Use current kernels |

---

### 🔴 RED: Not for Implementation

*Further Inputs required*

| HAL Component | Target Era | Status |
| --- | --- | --- |
| **DRM** | 0.100.x | HAL Interface Requirements Gathering |
| **Crypto** | 0.100.x | HAL Interface Requirements Gathering |

---

## Codebase Metadata

Every HAL and VSI component directory contains a `metadata.yaml` file that drives the [RAG Status Report](../../RAG_STATUS_REPORT.md). This file captures:

- **Component identity** — name, version, and generation number
- **RAG status** — RED, AMBER, or GREEN reflecting review readiness on develop
- **Lifecycle tracking** — review start date, 14-day review deadline, and target GREEN date (14+5 rule)
- **Scope** — high-level architectural responsibilities of the interface
- **Notes** — priority, current status detail, required actions, and owners
- **Reviewers** — the teams responsible for sign-off (mandatory teams plus component-specific team)
- **Impact** — flags for breaking changes and multi-view sync requirements

When a component's status changes (e.g. a new PR lands on develop that moves it from AMBER to GREEN), the `metadata.yaml` should be updated accordingly and the RAG report regenerated.
