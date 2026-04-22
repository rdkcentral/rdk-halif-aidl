# HAL Interface RAG Status Report

| | |
|---|---|
| **Generated** | 2026-04-22 |
| **Components** | 32 |
| 🟢 **GREEN** | 14 |
| 🟡 **AMBER** | 15 |
| 🔴 **RED** | 3 |

---

## Summary

| Status | Count | Meaning |
|--------|-------|---------|
| 🟢 GREEN | **14** | Reviewed & Approved — Interface stable on develop |
| 🟡 AMBER | **15** | Under Active Ingestion — Will enter sprint review when ready |
| 🔴 RED | **3** | Not Started / Blocked — Strategy or definition required |

---

## 🟢 GREEN — Reviewed & Approved

### SOC Components

| | Component | Current Version | Description | Reviews | Owners |
|---|-----------|---------|-------------|---------|--------|
| 🟢 | audiodecoder | 0.1.0.0 | Audio decoder resource management and codec format support | 6/6 | Architecture + AV_Architecture |
| 🟢 | audiomixer | 0.1.0.1 | Audio mixing and routing for multi-stream output | 5/6 | Architecture + VTS_Team + AV_Architecture |
| 🟢 | audiosink | 0.1.0.0 | Audio output rendering and sink device management | 6/6 | Architecture + AV_Architecture |
| 🟢 | avbuffer | 0.1.0.0 | AV buffer allocation and secure video path management | 6/6 | Architecture + AV_Architecture |
| 🟢 | avclock | 0.1.0.0 | Audio/video clock synchronization and timing control | 6/6 | Architecture + AV_Architecture |
| 🟢 | hdmicec | 0.1.0.0 | HDMI CEC protocol messaging and device control | 5/6 | Architecture + AV_Architecture |
| 🟢 | hdmiinput | 0.1.0.0 | HDMI input port management and signal detection | 3/6 | Architecture + AV_Architecture |
| 🟢 | hdmioutput | 0.1.0.0 | HDMI output port configuration and display control | 3/6 | Architecture + AV_Architecture |
| 🟢 | videodecoder | 0.1.0.0 | Video decoder resource management and codec support | 6/6 | Architecture + AV_Architecture |
| 🟢 | videosink | 0.1.0.0 | Video output rendering and display sink management | 6/6 | Architecture + AV_Architecture |


### OEM Components

| | Component | Current Version | Description | Reviews | Owners |
|---|-----------|---------|-------------|---------|--------|
| 🟢 | compositeinput | 0.2.0.0 | Composite video input capture and control | 2/6 | Architecture + AV_Architecture |
| 🟢 | deviceinfo | 0.1.0.0 | Device information and platform capability reporting | 5/6 | Architecture + Kernel_Architecture |
| 🟢 | indicator | 0.1.0.0 | LED and visual indicator state management | 5/6 | Architecture + Graphics_Architecture |
| 🟢 | sensor | 0.1.0.0 | Hardware sensor data acquisition and monitoring | 5/6 | Architecture + Kernel_Architecture |


---

## 🟡 AMBER — Under Active Ingestion

### SOC Components

| | Component | Current Version | Priority | Detail | Action Required | Review Deadline | Target GREEN | Owners |
|---|-----------|---------|----------|--------|-----------------|-----------------|--------------|--------|
| 🟡 | avbuffer *(SVP risk)* | 0.1.0.0 | 1 | Encrypted buffer (DRM/SVP) - Pending on DRM strategy | May change due to SVP changes from DRM which is being worked on | — | — | Architecture + AV_Architecture |
| 🟡 | vsi/kernel | 0.0.0.1 | 1 | Strategy required | Not blocking progress - Architecture Strategy | — | — | Architecture |
| 🟡 | planecontrol | 0.1.0.0 | 3 | Re-review required | Discussions with MW team - Simplify design. Architecture requires simplified design and restructured review. | — | — | Architecture + Graphics_Architecture |
| 🟡 | vsi/graphics | 0.0.0.1 | 6 | Docs required | Not blocking progress - Define Versions & write up vision and direction, Planning Out Evolution of the platform, RDK-M | — | — | Architecture + Graphics_Architecture |


### OEM Components

| | Component | Current Version | Priority | Detail | Action Required | Review Deadline | Target GREEN | Owners |
|---|-----------|---------|----------|--------|-----------------|-----------------|--------------|--------|
| 🟡 | panel | 0.1.0.0 | 3 | Re-review required | Review PQ settings for multiple video and PQ panel mixing | — | — | Architecture + Graphics_Architecture |
| 🟡 | deepsleep | 0.1.0.0 | 4 | Feedback-loop review | Review design based on learnings from current platforms. Examine findings and investigation on Shutdown issue | — | — | Architecture |
| 🟡 | boot | 0.1.0.0 | 5 | Migrate -> Reboot Reason | Rename Module | — | — | Architecture + MW_Team |
| 🟡 | broadcast | 0.0.0.1 | 5 | PR under review | Review Required - Start the PR Review | 2026-03-18 | 2026-03-25 | VTS_Team + Broadcast_Team |
| 🟡 | flash | 0.1.0.0 | 5 | Migrate -> Image | Rename Module | — | — | Architecture + Kernel_Architecture |
| 🟡 | r4ce | 0.0.0.1 | 5 | API Definition in progress | Control Manager Team - API Definition started | — | — | Architecture + Control_Manager_Architecture |
| 🟡 | vsi/bluetooth | 0.0.0.1 | 6 | Docs required | Not blocking progress - Have discussions write up methodology, Discussions with Bluetooth Team | 2026-03-24 | 2026-03-31 | Architecture + Connectivity_Architecture |
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
| 🔴 | vsi/crypto | 0.0.0.1 | 1 | Security API definition required | HAL lower-layer requirement - define Security API contracts and integration boundaries | — | — | Architecture + Kernel_Architecture |
| 🔴 | vsi/keyvault | 0.0.0.1 | 1 | Encrypted storage architecture required | HAL lower-layer requirement - define Key Vault interface for encrypted storage | — | — | Architecture + Kernel_Architecture |


### OEM Components

| | Component | Current Version | Priority | Detail | Action Required | Review Deadline | Target GREEN | Owners |
|---|-----------|---------|----------|--------|-----------------|-----------------|--------------|--------|
| 🔴 | cdm | 0.0.0.1 | 1 | Architecture strategy in progress | Architecture Strategy | — | — | Architecture + AV_Architecture |


---

## Review Status by Component

> ✅ Reviewed | 🔍 In Review | 🔁 Changes Requested | 🔄 Recheck | ☐ Pending | ➖ Abstained | N/A Not assigned

### SOC — 🟢 GREEN

| | Component | Progress | RTAB | Arch | Prod | VTS | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|------|-----|-----|-----------|----------|----------|--------------|--------|--------|
| 🟢 | audiodecoder | 6/6 | ✅ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | audiomixer | 5/6 | ☐ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | audiosink | 6/6 | ✅ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | avbuffer | 6/6 | ✅ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | avclock | 6/6 | ✅ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | hdmicec | 5/6 | ☐ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | hdmiinput | 3/6 | ☐ | ✅ | ✅ | 🔄 | ✅ | N/A | N/A | N/A | N/A | N/A | 🔄 |
| 🟢 | hdmioutput | 3/6 | ☐ | ✅ | ✅ | 🔄 | ✅ | N/A | N/A | N/A | N/A | N/A | 🔄 |
| 🟢 | videodecoder | 6/6 | ✅ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |
| 🟢 | videosink | 6/6 | ✅ | ✅ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ |

### SOC — 🟡 AMBER

| | Component | Progress | RTAB | Arch | Prod | VTS | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|------|-----|-----|-----------|----------|----------|--------------|--------|--------|
| 🟡 | vsi/kernel | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | planecontrol | 0/7 | ☐ | ☐ | ☐ | ☐ | ☐ | N/A | N/A | ☐ | N/A | N/A | ☐ |
| 🟡 | vsi/graphics | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | ☐ | N/A | N/A | ☐ |

### SOC — 🔴 RED

| | Component | Progress | RTAB | Arch | Prod | VTS | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|------|-----|-----|-----------|----------|----------|--------------|--------|--------|
| 🔴 | vsi/crypto | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🔴 | vsi/keyvault | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |

### OEM — 🟢 GREEN

| | Component | Progress | RTAB | Arch | Prod | VTS | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|------|-----|-----|-----------|----------|----------|--------------|--------|--------|
| 🟢 | compositeinput | 2/6 | ☐ | ✅ | ✅ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |
| 🟢 | deviceinfo | 5/6 | ☐ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ | ✅ |
| 🟢 | indicator | 5/6 | ☐ | ✅ | ✅ | ✅ | N/A | N/A | N/A | ✅ | N/A | N/A | ✅ |
| 🟢 | sensor | 5/6 | ☐ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ✅ | ✅ |

### OEM — 🟡 AMBER

| | Component | Progress | RTAB | Arch | Prod | VTS | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|------|-----|-----|-----------|----------|----------|--------------|--------|--------|
| 🟡 | panel | 2/6 | ☐ | ✅ | ✅ | ☐ | N/A | N/A | N/A | ☐ | N/A | N/A | ☐ |
| 🟡 | deepsleep | 4/6 | ☐ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ | ✅ |
| 🟡 | boot | 4/6 | ☐ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ | ✅ |
| 🟡 | broadcast | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | ☐ | N/A | N/A | N/A | N/A | ☐ |
| 🟡 | flash | 4/6 | ☐ | ✅ | ✅ | ✅ | N/A | N/A | N/A | N/A | N/A | ☐ | ✅ |
| 🟡 | r4ce | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | ☐ | N/A | N/A | N/A | ☐ |
| 🟡 | vsi/bluetooth | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | ☐ | N/A | ☐ |
| 🟡 | vsi/linuxinput | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | vsi/wifi | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | ☐ | N/A | ☐ |
| 🟡 | vsi/abstractfilesystem | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | vsi/filesystem | 0/6 | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ | ☐ |
| 🟡 | ffv | 0/6 | ☐ | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |

### OEM — 🔴 RED

| | Component | Progress | RTAB | Arch | Prod | VTS | AV | Broadcast | Ctrl Mgr | Graphics | Connectivity | Kernel | Vendor |
|---|-----------|----------|------|------|------|-----|-----|-----------|----------|----------|--------------|--------|--------|
| 🔴 | cdm | 0/6 | ☐ | ☐ | ☐ | ☐ | ☐ | N/A | N/A | N/A | N/A | N/A | ☐ |

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
| Control_Manager_Architecture | Remote control & input management |
| Graphics_Architecture | Graphics, display & composition |
| Connectivity_Architecture | Bluetooth, Wi-Fi & connectivity |
| Kernel_Architecture | System, kernel, boot & platform |
| Vendor_Layer_Team | Vendor HAL implementation review |

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
