# HAL Interface RAG Status Report

| | |
|---|---|
| **Generated** | 2026-02-26 |
| **Branch** | `feature/338-task-add-versioning-sop` |
| **Version** | `0.13.1-21-g4893c8cf` |
| **Components** | 31 |
| 🟢 **GREEN** | 13 |
| 🟡 **AMBER** | 10 |
| 🔴 **RED** | 8 |

---

## Summary

| Status | Count | Meaning |
|--------|-------|---------|
| 🟢 GREEN | **13** | Reviewed & Approved — Interface stable on develop |
| 🟡 AMBER | **10** | Under Active Review — Design iteration in progress |
| 🔴 RED | **8** | Not Started / Blocked — Strategy or definition required |

---

## 🟢 GREEN — Reviewed & Approved

### SOC Components

| | Component | Version | Description | Owners |
|---|-----------|---------|-------------|--------|
| 🟢 | audiodecoder | 0.100.1 | Audio decoder resource management and codec format support | Architecture + AV_Architecture |
| 🟢 | audiosink | 0.100.1 | Audio output rendering and sink device management | Architecture + AV_Architecture |
| 🟢 | avbuffer | 0.100.1 | AV buffer allocation and secure video path management | Architecture + AV_Architecture |
| 🟢 | avclock | 0.100.1 | Audio/video clock synchronization and timing control | Architecture + AV_Architecture |
| 🟢 | hdmicec | 0.100.1 | HDMI CEC protocol messaging and device control | Architecture + AV_Architecture |
| 🟢 | hdmiinput | 0.100.1 | HDMI input port management and signal detection | Architecture + AV_Architecture |
| 🟢 | hdmioutput | 0.100.1 | HDMI output port configuration and display control | Architecture + AV_Architecture |
| 🟢 | videodecoder | 0.100.1 | Video decoder resource management and codec support | Architecture + AV_Architecture |
| 🟢 | videosink | 0.100.1 | Video output rendering and display sink management | Architecture + AV_Architecture |


### OEM Components

| | Component | Version | Description | Owners |
|---|-----------|---------|-------------|--------|
| 🟢 | compositeinput | 0.100.1 | Composite video input capture and control | Architecture + AV_Architecture |
| 🟢 | deviceinfo | 0.100.1 | Device information and platform capability reporting | Architecture + Kernel_Architecture |
| 🟢 | indicator | 0.100.1 | LED and visual indicator state management | Architecture + Graphics_Architecture |
| 🟢 | sensor | 0.100.1 | Hardware sensor data acquisition and monitoring | Architecture + Kernel_Architecture |


---

## 🟡 AMBER — Under Active Review

### SOC Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
| 🟡 | avbuffer *(SVP risk)* | 0.100.1 | 1 | Encrypted buffer (DRM/SVP) - Pending on DRM strategy | May change due to SVP changes from DRM which is being worked on | 5/5 | Architecture + AV_Architecture |
| 🟡 | audiomixer | 0.0.1 | 2 | PR under review | In Progress PR Review | 0/5 | VTS_Team + AV_Architecture |
| 🟡 | planecontrol | 0.0.1 | 3 | Re-review required | Discussions with MW team - Simplify design | 0/5 | Architecture + Graphics_Architecture |


### OEM Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
| 🟡 | common | 0.0.1 | 2 | Module being deprecated | Move PropertyValue per module, replace enums with HFP-defined strings for future expansion | 0/5 | Architecture + AV_Architecture |
| 🟡 | panel | 0.0.1 | 3 | Re-review required | Review PQ settings for multiple video and PQ panel mixing | 0/5 | Architecture + Graphics_Architecture |
| 🟡 | deepsleep | 0.0.1 | 4 | Feedback-loop review | Review design based on learnings from current platforms. Examine findings and investigation on Shutdown issue | 0/5 | Architecture |
| 🟡 | boot | 0.0.1 | 5 | Migrate -> Reboot Reason | Rename Module | 0/5 | Architecture + MW_Team |
| 🟡 | broadcast | 0.0.1 | 5 | PR under review | Review Required - Start the PR Review | 0/5 | VTS_Team + Broadcast_Team |
| 🟡 | flash | 0.0.1 | 5 | Migrate -> Image | Rename Module | 0/5 | Architecture + Kernel_Architecture |
| 🟡 | r4ce | 0.0.1 | 5 | API Definition in progress | Control Manager Team - API Definition started | 0/5 | Architecture + Control_Manager_Team |
| 🟡 | ffv | 0.0.1 | 8 | PR under review | Finalise PR Review, still platform specific proposal from control manager | 0/5 | Architecture + AV_Architecture |


---

## 🔴 RED — Not Started / Blocked

### SOC Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
| 🔴 | vsi/kernel | 0.0.1 | 1 | Strategy required | Not blocking progress - Architecture Strategy | 0/5 | Architecture |
| 🔴 | vsi/graphics | 0.0.1 | 6 | Docs required | Not blocking progress - Define Versions & write up vision and direction, Planning Out Evolution of the platform, RDK-M | 0/5 | Architecture + Graphics_Architecture |


### OEM Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
| 🔴 | cdm | 0.0.1 | 1 | Architecture strategy in progress | Architecture Strategy | 0/5 | Architecture + AV_Architecture |
| 🔴 | vsi/bluetooth | 0.0.1 | 6 | Docs required | Not blocking progress - Have discussions write up methodology, Discussions with Bluetooth Team | 0/5 | Architecture + Bluetooth_Architecture |
| 🔴 | vsi/linuxinput | 0.0.1 | 6 | Docs required | Not blocking progress - Write up methodology | 0/5 | Architecture + Kernel_Architecture |
| 🔴 | vsi/wifi | 0.0.1 | 6 | Docs required | Not blocking progress - Have discussions write up methodology, Discussions with WIFI Team | 0/5 | Architecture + Bluetooth_Architecture |
| 🔴 | vsi/abstractfilesystem | 0.0.1 | 7 | Requirements TBD | Not blocking progress - Discussion with MW Team, Review Requirements | 0/5 | Architecture |
| 🔴 | vsi/filesystem | 0.0.1 | 7 | Standards & layout | Not blocking progress - Review Documentation | 0/5 | Architecture |


---

## Review Status by Component

> ✅ Reviewed | ☐ Pending | ➖ Abstained | N/A Not assigned

### SOC Components

| | Component | Progress | Arch | VTS | AV | Broadcast | CtrlMgr | Graphics | BT/Net | Kernel |
|---|-----------|----------|------|-----|-----|-----------|---------|----------|--------|--------|
| 🟢 | audiodecoder | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | audiosink | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | avbuffer | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | avclock | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | hdmicec | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | hdmiinput | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | hdmioutput | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | videodecoder | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | videosink | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟡 | audiomixer | 0/5 | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A |
| 🟡 | planecontrol | 0/5 | ☐ | ☐ | N/A | N/A | N/A | ☐ | N/A | N/A |
| 🔴 | vsi/kernel | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🔴 | vsi/graphics | 0/5 | ☐ | ☐ | N/A | N/A | N/A | ☐ | N/A | N/A |

### OEM Components

| | Component | Progress | Arch | VTS | AV | Broadcast | CtrlMgr | Graphics | BT/Net | Kernel |
|---|-----------|----------|------|-----|-----|-----------|---------|----------|--------|--------|
| 🟢 | compositeinput | 5/5 | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A |
| 🟢 | deviceinfo | 5/5 | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | indicator | 5/5 | ✅ | ✅ | N/A | N/A | N/A | ✅ | N/A | N/A |
| 🟢 | sensor | 5/5 | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟡 | common | 0/5 | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A |
| 🟡 | panel | 0/5 | ☐ | ☐ | N/A | N/A | N/A | ☐ | N/A | N/A |
| 🟡 | deepsleep | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟡 | boot | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟡 | broadcast | 0/5 | ☐ | ☐ | N/A | ☐ | N/A | N/A | N/A | N/A |
| 🟡 | flash | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟡 | r4ce | 0/5 | ☐ | ☐ | N/A | N/A | ☐ | N/A | N/A | N/A |
| 🟡 | ffv | 0/5 | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A |
| 🔴 | cdm | 0/5 | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A |
| 🔴 | vsi/bluetooth | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | ☐ | N/A |
| 🔴 | vsi/linuxinput | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🔴 | vsi/wifi | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | ☐ | N/A |
| 🔴 | vsi/abstractfilesystem | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🔴 | vsi/filesystem | 0/5 | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |

---

## Reviewer Team Coverage

> **Note:** Architecture and Product_Architecture are the same organisational group reviewing as separate stakeholders, with members drawn from various teams.

| Team | Role |
|------|------|
| RTAB_Group | All components |
| Architecture | All components |
| Product_Architecture | All components |
| VTS_Team | All components |
| AV_Architecture | Audio/Video pipeline components |
| Broadcast_Team | Broadcast/tuner components |
| Control_Manager_Team | Remote control & input management |
| Graphics_Architecture | Graphics, display & composition |
| Bluetooth_Architecture | Bluetooth, Wi-Fi & connectivity |
| Kernel_Architecture | System, kernel, boot & platform |

---

### RAG Key

- 🟢 **GREEN** — Interface reviewed, approved and stable. Ready for implementation.
- 🟡 **AMBER** — Interface under active review. Design iteration in progress.
- 🔴 **RED** — Interface not yet started or blocked. Requires architecture strategy, AIDL definition, or team alignment.

---

*Report generated by `scripts/generate_rag_report.sh`*
