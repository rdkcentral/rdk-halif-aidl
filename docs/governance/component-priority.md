# Component Priority List

The order in which HAL components are worked on. The [Release-Heatmap](https://github.com/rdkcentral/rdk-halif-aidl/wiki/Release-Heatmap) wiki page reads this file: one section per priority, one row per `Label`.

## Where the priority is kept

- A component is a directory with a `metadata.yaml`. Its tickets are those carrying `component:<directory>`, or the labels its `labels` field names instead (Boot's is `component:boot`, Sensor's are `component:motion_sensor` and `component:thermal_sensor`).
- Each component's `metadata.yaml` holds its `priority` (`P1`, `P2`, `P3`, or `~` when not yet set) and its `devices` (`stb`, `tv`, or both). The scripts read them from there; this page gives the reasons.
- A component with a `metadata.yaml` must carry the same priority here and there: `tests/scripts/test_release_heatmap.py` fails when they differ. Change both in the same PR.
- Rows here with no directory, such as Crypto, are not components yet: they appear on the heatmap only while a ticket carries their label. They, and the documentation and infrastructure rows, take their priority from this page alone.
- Within each priority, the heatmap lists the components used on both STB and TV first, then STB only, then TV only.

## How a ticket gets its priority

- A ticket or PR takes the priority of its highest-priority `component:*` label. One with no component label takes the priority of its `scope:infrastructure`, `scope:overview` or `documentation` row.
- Work with no clear directory to change, such as infrastructure, overview and documentation, is P1.
- `scripts/release_heatmap.py --set-priority` writes that priority into the [halif_aidl](https://github.com/orgs/rdkcentral/projects/41) project's `Priority` field for every open ticket and PR. Run it with `--dry-run` first, to see what will change.
- `P0 - Critical` is set by hand on a single ticket, and the script never changes it.
- On a ticket with no component label, the script fills in `Priority` only where it is empty. A value set by hand stays, so build tooling can be raised above P3 one ticket at a time.
- Components with no row here go under **Not yet prioritised**, and their tickets keep whatever `Priority` they already have.

## P1 – Critical priority

Worked on first.

| Component | Label | Priority | Scope |
| --- | --- | --- | --- |
| Audio Decoder | `component:audiodecoder` | P1 | Core audio playback. |
| Audio Mixer | `component:audiomixer` | P1 | Only what HDMI output needs; other routing is not required yet. |
| Audio Sink | `component:audiosink` | P1 | Audio output rendering for HDMI output. |
| AV Buffer | `component:avbuffer` | P1 | — |
| AV Clock (Audio Sync, Video Sync) | `component:avclock` | P1 | Audio and video synchronisation. |
| Boot | `component:boot` | P1 | Few issues, none significant. |
| Common | `component:common` | P1 | Structural changes, including dissolving Common, because they can affect every HAL. |
| Device Info | `component:deviceinfo` | P1 | Limited-impact issues. |
| DRM | `component:drm` | P1 | Needs further technical discussion. |
| Firmware Update | `component:firmwareupdate` | P1 | — |
| HDMI Output | `component:hdmioutput` | P1 | Every open ticket, as soon as possible: needed for platform qualification. |
| HDMI-CEC | `component:hdmicec` | P1 | — |
| Indicator | `component:indicator` | P1 | — |
| Plane Control | `component:planecontrol` | P1 | Graphics and video plane composition for HDMI output. |
| Ring Buffer | `component:ringbuffer` | P1 | — |
| Sensor (Motion, Thermal) | `component:motion_sensor` `component:thermal_sensor` | P1 | — |
| Video Decoder | `component:videodecoder` | P1* | Important to the core delivery. |
| Video Sink | `component:videosink` | P1 | Video output rendering for HDMI output. |
| VSI Linux Input | `component:vsi/linuxinput` | P1 | Committed to for this delivery. |
| General documentation | `documentation` | P1 | Documentation the delivery depends on. |
| Repository infrastructure and CI/CD | `scope:infrastructure` | P1 | Build tooling and CI the delivery depends on. |
| HAL overview | `scope:overview` | P1 | Work across the whole HAL, with no one directory to change. |
| HAL compatibility helper | `component:halcompat` | P1 | Shared client tooling, with no directory of its own. |

\* Video Decoder is P1 for its importance to the core delivery; its prioritisation is not yet complete.

## P2 – Medium priority

Worked on after P1.

| Component | Label | Priority | Scope |
| --- | --- | --- | --- |
| Broadcast | `component:broadcast` | P2 | Deferred behind P1 work. |
| Deep Sleep | `component:deepsleep` | P2 | Small, likely straightforward. |
| Video Capture | `component:videocapture` | P2 | Current platform limitations prevent it. |
| HAL architecture documentation | — | P2/P3 | Better documentation and examples, not at the expense of critical implementation work. |

## P3 – Low priority

Worked on after P2.

| Component | Label | Priority | Scope |
| --- | --- | --- | --- |
| Composite Input | `component:compositeinput` | P3 | Excluded from the immediate focus. |
| Crypto | `component:crypto` | P3 | Nothing in it is needed for the immediate work. |
| Far-Field Voice | `component:ffv` | P3 | — |
| HDMI Input | `component:hdmiinput` | P3 | Not needed for IP set-top-box. |
| Panel | `component:panel` | P3 | Not needed for set-top-box delivery. |
| RF4CE | `component:r4ce` | P3 | — |
| Secure Storage | `component:securestorage` | P3 | — |
| VSI Abstract File System | `component:vsi/abstractfilesystem` | P3 | Architecturally important; not all of it is needed yet. |
| VSI Bluetooth | `component:vsi/bluetooth` | P3 | Interface needs upgrading (status RED). |
| VSI File System | `component:vsi/filesystem` | P3 | Interface needs upgrading (status RED). |
| VSI Graphics | `component:vsi/graphics` | P3 | — |
| VSI Kernel | `component:vsi/kernel` | P3 | Interface needs upgrading (status RED). |
| VSI Wi-Fi | `component:vsi/wifi` | P3 | Interface needs upgrading (status RED). |

