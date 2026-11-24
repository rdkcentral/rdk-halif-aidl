# Component Priority List

The order in which HAL components are worked on, set by the core IP set-top-box delivery on Broadcom XI1. The [Release-Heatmap](https://github.com/rdkcentral/rdk-halif-aidl/wiki/Release-Heatmap) wiki page reads this file: one section per priority, one row per `Label`.

## Where the priority is kept

- A component is a directory with a `metadata.yaml`. Its tickets are those carrying `component:<directory>`, or the labels its `labels` field names instead (Boot's is `component:boot`, Sensor's are `component:motion_sensor` and `component:thermal_sensor`).
- Each component's `metadata.yaml` holds its `priority` (`P1`, `P2`, `P3`, or `~` when not yet set) and its `devices` (`stb`, `tv`, or both). The scripts read them from there; this page gives the reasons.
- A component with a `metadata.yaml` must carry the same priority here and there: `tests/scripts/test_release_heatmap.py` fails when they differ. Change both in the same PR.
- Rows here with no directory, such as Crypto, are not components yet: they appear on the heatmap only while a ticket carries their label. They, and the documentation and infrastructure rows, take their priority from this page alone.
- Within each priority, the heatmap lists the components used on both STB and TV first, then STB only, then TV only.

## How a ticket gets its priority

- A ticket or PR takes the priority of its highest-priority `component:*` label. One with no component label takes the priority of its `scope:infrastructure` or `documentation` row.
- `scripts/release_heatmap.py --set-priority` writes that priority into the [halif_aidl](https://github.com/orgs/rdkcentral/projects/41) project's `Priority` field for every open ticket and PR. Run it with `--dry-run` first, to see what will change.
- `P0 - Critical` is set by hand on a single ticket, and the script never changes it.
- On a ticket with no component label, the script fills in `Priority` only where it is empty. A value set by hand stays, so build tooling can be raised above P3 one ticket at a time.
- Components with no row here go under **Not yet prioritised**, and their tickets keep whatever `Priority` they already have.

## P1 – Critical priority

Components and changes needed for core IP set-top-box functionality, particularly Broadcom XI1.

| Component | Label | Priority | Scope |
| --- | --- | --- | --- |
| Audio Decoder | `component:audiodecoder` | P1 | Core audio playback. |
| Audio Mixer | `component:audiomixer` | P1 | Only what HDMI output needs; other routing is not required yet. |
| Audio Sink | `component:audiosink` | P1 | Audio output rendering for HDMI output. |
| AV Buffer | `component:avbuffer` | P1 | — |
| AV Clock (Audio Sync, Video Sync) | `component:avclock` | P1 | Audio and video synchronisation. |
| Common | `component:common` | P1 | Structural changes, including dissolving Common, because they can affect every HAL. |
| DRM | `component:drm` | P1 | Needs further technical discussion. |
| HDMI-CEC | `component:hdmicec` | P1 | — |
| HDMI Output | `component:hdmioutput` | P1 | Every open ticket, as soon as possible: needed for platform qualification. |
| Indicator | `component:indicator` | P1 | — |
| Plane Control | `component:planecontrol` | P1 | Graphics and video plane composition for HDMI output. |
| Ring Buffer | `component:ringbuffer` | P1 | — |
| Sensor (Motion, Thermal) | `component:motion_sensor` `component:thermal_sensor` | P1 | — |
| Video Decoder | `component:videodecoder` | P1* | Important to the core delivery. |
| Video Sink | `component:videosink` | P1 | Video output rendering for HDMI output. |

\* Video Decoder is P1 for its importance to the core delivery; its prioritisation is not yet complete.

## P2 – Medium priority

Required work that can be deferred or delivered after higher-priority functionality.

| Component | Label | Priority | Scope |
| --- | --- | --- | --- |
| Boot | `component:boot` | P2 | Few issues, none significant. |
| Broadcast | `component:broadcast` | P2 | Deferred behind IP set-top-box work. Check the chosen XI1 variant supports the features. |
| Deep Sleep | `component:deepsleep` | P2 | Small, likely straightforward. |
| Device Info | `component:deviceinfo` | P2 | Limited-impact issues. |
| Firmware Update | `component:firmwareupdate` | P2 | — |
| VSI Abstract File System | `component:vsi/abstractfilesystem` | P2* | Architecturally important; not all of it is needed for XI1. |
| HAL architecture documentation | — | P2/P3 | Better documentation and examples, not at the expense of critical implementation work. |

\* VSI is P2 or P3, depending on how much of it the current delivery needs.

## P3 – Low priority

Outside the current Broadcom IP set-top-box requirements, or the lowest priority.

| Component | Label | Priority | Scope |
| --- | --- | --- | --- |
| Composite Input | `component:compositeinput` | P3 | Excluded from the immediate focus. |
| Crypto | `component:crypto` | P3* | Nothing in it is needed for the immediate work. |
| HDMI Input | `component:hdmiinput` | P3 | Not needed for IP set-top-box. |
| Panel | `component:panel` | P3 | Not needed for set-top-box delivery. |
| RF4CE | `component:r4ce` | P3 | — |
| Secure Storage | `component:securestorage` | P3 | — |
| Video Capture | `component:videocapture` | P3 | Current XI1 limitations prevent it. |
| General documentation | `documentation` | P3 | The existing GStreamer and Polaris diagrams serve; improvements go in their own tickets. |
| Repository infrastructure and CI/CD | `scope:infrastructure` | P3* | Below build tooling needed for development. |

\* Deprioritised for now. Build tooling that development depends on is raised to P1 or P2 on its own ticket.
