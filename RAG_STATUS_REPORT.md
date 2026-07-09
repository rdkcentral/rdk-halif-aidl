# HAL Interface RAG Status Report

| | |
|---|---|
| **Generated** | 2026-07-10 |
| **Components** | 30 |
| 🟢 **GREEN** | 18 |
| 🟡 **AMBER** | 12 |
| 🔴 **RED** | 0 |

---

## Summary

| Status | Count | Meaning |
|--------|-------|---------|
| 🟢 GREEN | **18** | Reviewed & Approved — Interface stable on develop |
| 🟡 AMBER | **12** | Under Active Ingestion — Will enter sprint review when ready |
| 🔴 RED | **0** | Not Started / Blocked — Strategy or definition required |

---

## 🟢 GREEN — Reviewed & Approved

### SOC Components

| | Component | Current Version | Description | Reviews | Owners |
|---|-----------|---------|-------------|---------|--------|
| 🟢 | audiodecoder | 0.2.0.0 | Audio decoder resource management and codec format support | 3/4 | Architecture + AV_Architecture |
| 🟢 | audiosink | 0.2.0.0 | Audio output rendering and sink device management | 3/4 | Architecture + AV_Architecture |
| 🟢 | avbuffer | 0.2.0.0 | AV buffer allocation and secure video path management | 4/4 | Architecture + AV_Architecture |
| 🟢 | avclock | 0.2.0.1 | Audio/video clock synchronization and timing control | 3/4 | Architecture + AV_Architecture |
| 🟢 | drm | 0.1.0.0 | DRM plugin and crypto plugin interfaces for content protection | 3/4 | Architecture + AV_Architecture |
| 🟢 | hdmicec | 0.1.0.0 | HDMI CEC protocol messaging and device control | 4/4 | Architecture + AV_Architecture |
| 🟢 | hdmiinput | 0.1.0.0 | HDMI input port management and signal detection | 3/4 | Architecture + AV_Architecture |
| 🟢 | hdmioutput | 0.1.0.0 | HDMI output port configuration and display control | 3/4 | Architecture + AV_Architecture |
| 🟢 | planecontrol | 0.2.0.0 | Graphics and video plane composition control | 4/5 | Architecture + Graphics_Architecture |
| 🟢 | videodecoder | 0.2.0.1 | Video decoder resource management and codec support | 3/4 | Architecture + AV_Architecture |
| 🟢 | videosink | 0.2.0.0 | Video output rendering and display sink management | 3/4 | Architecture + AV_Architecture |


### OEM Components

| | Component | Current Version | Description | Reviews | Owners |
|---|-----------|---------|-------------|---------|--------|
| 🟢 | bootreason | 0.1.0.0 | Boot reason tracking and reboot management | 3/4 | Architecture + MW_Team |
| 🟢 | compositeinput | 0.2.0.0 | Composite video input capture and control | 2/4 | Architecture + AV_Architecture |
| 🟢 | deepsleep | 0.1.0.0 | Deep sleep and low-power state management | 3/4 | Architecture |
| 🟢 | deviceinfo | 0.1.0.0 | Device information and platform capability reporting | 4/4 | Architecture + Kernel_Architecture |
| 🟢 | firmwareupdate | 0.2.0.0 | Update lifecycle for multiple firmware types at multiple locations across the system | 0/4 | Architecture + Kernel_Architecture |
| 🟢 | indicator | 0.1.0.0 | LED and visual indicator state management | 4/4 | Architecture + Graphics_Architecture |
| 🟢 | sensor | 0.2.0.0 | Hardware sensor data acquisition and monitoring | 4/4 | Architecture + Kernel_Architecture |


---

## 🟡 AMBER — Under Active Ingestion

### SOC Components

| | Component | Current Version | Priority | Detail | Action Required | Review Deadline | Target GREEN | Owners |
|---|-----------|---------|----------|--------|-----------------|-----------------|--------------|--------|
| 🟡 | audiomixer | 0.3.0.0 | — | AQ parameter API in review | Land AQ processor API (PR #573) + OutputPortType BLUETOOTH→CAPTURE rename (#708) — both batch into one 0.4.0.0 major bump (0.23.0). Flip to GREEN when shipped. | — | — | Architecture + Vendor_Layer_Team + AV_Architecture |
| 🟡 | vsi/kernel | 0.0.0.1 | 1 | Strategy required | Not blocking progress - Architecture Strategy | — | — | Architecture |
| 🟡 | vsi/graphics | 0.0.0.1 | 6 | Docs required | Not blocking progress - Define Versions & write up vision and direction, Planning Out Evolution of the platform, RDK-M | — | — | Architecture + Graphics_Architecture |


### OEM Components

| | Component | Current Version | Priority | Detail | Action Required | Review Deadline | Target GREEN | Owners |
|---|-----------|---------|----------|--------|-----------------|-----------------|--------------|--------|
| 🟡 | panel | 0.1.0.0 | 3 | Breaking change in flight: #688 PQ capability normalization (0.2.0.0) in review; GREEN when shipped | PQ capability work tracked in #674, #497, #516, #276 | — | — | Architecture + Graphics_Architecture |
| 🟡 | broadcast | 0.1.0.0 | 5 | Not integrated into the AIDL build - blocked on FMQ (#494) | Blocked: needs the android.hardware.common.fmq AIDL package in the binder SDK (linux_binder_idl#18); then add broadcast/current/interface.yaml - see #494. | — | — | Vendor_Layer_Team + Broadcast_Team |
| 🟡 | r4ce | 0.0.0.1 | 5 | API Definition in progress | Control Manager Team - API Definition started | — | — | Architecture + Control_Manager_Architecture |
| 🟡 | vsi/bluetooth | 0.0.0.1 | 6 | Docs required | Not blocking progress - Have discussions write up methodology, Discussions with Bluetooth Team | — | — | Architecture + Connectivity_Architecture |
| 🟡 | vsi/linuxinput | 0.0.0.1 | 6 | Docs required | Not blocking progress - Write up methodology | — | — | Architecture + Kernel_Architecture |
| 🟡 | vsi/wifi | 0.0.0.1 | 6 | Docs required | Not blocking progress - Have discussions write up methodology, Discussions with WIFI Team | — | — | Architecture + Connectivity_Architecture |
| 🟡 | vsi/abstractfilesystem | 0.0.0.1 | 7 | Requirements TBD | Not blocking progress - Discussion with MW Team, Review Requirements | — | — | Architecture |
| 🟡 | vsi/filesystem | 0.0.0.1 | 7 | Standards & layout | Not blocking progress - Review Documentation | — | — | Architecture |
| 🟡 | ffv | 0.0.0.1 | 8 | PR under review | Finalise PR Review, still platform specific proposal from control manager | — | — | Architecture + AV_Architecture |


---

## 🔴 RED — Not Started / Blocked

### SOC Components

| | Component | Current Version | Priority | Detail | Action Required | Review Deadline | Target GREEN | Owners |
|---|-----------|---------|----------|--------|-----------------|-----------------|--------------|--------|


### OEM Components

| | Component | Current Version | Priority | Detail | Action Required | Review Deadline | Target GREEN | Owners |
|---|-----------|---------|----------|--------|-----------------|-----------------|--------------|--------|


---

## Review Status by Component

**Column key:** Arch = Architecture · Prod = Product Architecture · AV = AV Architecture · Broadcast = Broadcast Team · Ctrl Mgr = Control Manager Architecture · Graphics = Graphics Architecture · Connectivity = Connectivity Architecture · Kernel = Kernel Architecture · Vendor = Vendor Layer Team. (Architecture and Product Architecture are the same organisational group reviewing as separate stakeholders.)

> ✅ Reviewed | 🔍 In Review | 🔁 Changes Requested | 🔄 Recheck | ☐ Pending | ➖ Abstained | N/A Not assigned

### SOC — 🟢 GREEN

| | Component | Progress | Arch | Prod | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|-----|-----------|----------|----------|--------------|--------|--------|
| 🟢 | audiodecoder | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟢 | audiosink | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟢 | avbuffer | 4/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | avclock | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟢 | drm | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟢 | hdmicec | 4/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | hdmiinput | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | 🔄 |
| 🟢 | hdmioutput | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | 🔄 |
| 🟢 | planecontrol | 4/5 | ✅ | ✅ | ✅ | N/A | N/A | ✅ | N/A | N/A | ☐ |
| 🟢 | videodecoder | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟢 | videosink | 3/4 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ |

### SOC — 🟡 AMBER

| | Component | Progress | Arch | Prod | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|-----|-----------|----------|----------|--------------|--------|--------|
| 🟡 | vsi/kernel | 0/4 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | vsi/graphics | 0/4 | ☐ | ☐ | N/A | N/A | N/A | ☐ | N/A | N/A | ☐ |
| 🟡 | audiomixer | 0/4 | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |

### SOC — 🔴 RED

| | Component | Progress | Arch | Prod | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|-----|-----------|----------|----------|--------------|--------|--------|

### OEM — 🟢 GREEN

| | Component | Progress | Arch | Prod | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|-----|-----------|----------|----------|--------------|--------|--------|
| 🟢 | bootreason | 3/4 | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ | ✅ |
| 🟢 | compositeinput | 2/4 | ✅ | ✅ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟢 | deepsleep | 3/4 | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ | ✅ |
| 🟢 | deviceinfo | 4/4 | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ | ✅ |
| 🟢 | firmwareupdate | 0/4 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟢 | indicator | 4/4 | ✅ | ✅ | N/A | N/A | N/A | ✅ | N/A | N/A | ✅ |
| 🟢 | sensor | 4/4 | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ | ✅ |

### OEM — 🟡 AMBER

| | Component | Progress | Arch | Prod | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|-----|-----------|----------|----------|--------------|--------|--------|
| 🟡 | panel | 2/4 | ✅ | ✅ | N/A | N/A | N/A | ☐ | N/A | N/A | ☐ |
| 🟡 | broadcast | 0/4 | ☐ | ☐ | N/A | ☐ | N/A | N/A | N/A | N/A | ☐ |
| 🟡 | r4ce | 0/4 | ☐ | ☐ | N/A | N/A | ☐ | N/A | N/A | N/A | ☐ |
| 🟡 | vsi/bluetooth | 0/4 | ☐ | ☐ | N/A | N/A | N/A | N/A | ☐ | N/A | ☐ |
| 🟡 | vsi/linuxinput | 0/4 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | vsi/wifi | 0/4 | ☐ | ☐ | N/A | N/A | N/A | N/A | ☐ | N/A | ☐ |
| 🟡 | vsi/abstractfilesystem | 0/4 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | vsi/filesystem | 0/4 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | ffv | 0/4 | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |

### OEM — 🔴 RED

| | Component | Progress | Arch | Prod | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|-----|-----------|----------|----------|--------------|--------|--------|

---

## Reviewer Team Coverage

> **Note:** Architecture and Product_Architecture are the same organisational group reviewing as separate stakeholders, with members drawn from various teams.

| Team | Role | GitHub Team (add members here) |
| ---- | ---- | ------------------------------ |
| Architecture | All components | [hal-arch-reviewers](https://github.com/orgs/rdkcentral/teams/hal-arch-reviewers) |
| Product_Architecture | All components | [hal-product-arch-reviewers](https://github.com/orgs/rdkcentral/teams/hal-product-arch-reviewers) |
| AV_Architecture | Audio/Video pipeline components | [hal-av-arch-reviewers](https://github.com/orgs/rdkcentral/teams/hal-av-arch-reviewers) |
| Broadcast_Team | Broadcast/tuner components | [hal-broadcast-reviewers](https://github.com/orgs/rdkcentral/teams/hal-broadcast-reviewers) |
| Control_Manager_Architecture | Remote control & input management | [hal-control-manager-reviewers](https://github.com/orgs/rdkcentral/teams/hal-control-manager-reviewers) |
| Graphics_Architecture | Graphics, display & composition | [hal-graphics-arch-reviewers](https://github.com/orgs/rdkcentral/teams/hal-graphics-arch-reviewers) |
| Connectivity_Architecture | Bluetooth, Wi-Fi & connectivity | [hal-connectivity-arch-reviewers](https://github.com/orgs/rdkcentral/teams/hal-connectivity-arch-reviewers) |
| Kernel_Architecture | System, kernel, boot & platform | [hal-kernel-arch-reviewers](https://github.com/orgs/rdkcentral/teams/hal-kernel-arch-reviewers) |
| Vendor_Layer_Team | Vendor HAL implementation review | [rdk-halif-aidl-pr-review-team](https://github.com/orgs/rdkcentral/teams/rdk-halif-aidl-pr-review-team) |

---

### Version Key

Pre-baseline versions use the format `0.<generation>.<minor>.<patch>`:

| Field | Meaning | Bumped when |
|-------|---------|-------------|
| `0` | Pre-baseline prefix | Changes to AIDL integer at freeze |
| `generation` | Architectural era (0 = initial, 1+ = full design cycle) | Breaking interface change |
| `minor` | ABI-compatible enhancement counter | Non-breaking feature added |
| `patch` | Documentation or trivial fix counter | No interface change |

Post-baseline (frozen) versions use AIDL stable versioning: `1`, `2`, `3`... (100% backwards compatible, additive only).

---

### RAG Key

- 🟢 **GREEN** — Interface reviewed, approved and stable. Ready for implementation.
- 🟡 **AMBER** — Interface under active ingestion. Will enter sprint review when ready.
- 🔴 **RED** — Interface not yet started or blocked. Requires architecture strategy, AIDL definition, or team alignment.

---

*Report generated by `scripts/generate_rag_report.sh`*
