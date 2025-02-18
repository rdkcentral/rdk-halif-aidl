# HAL Interface Overview

| Status | Description |
| ------- | ------| 
|✅ <span class="inline-success">Complete</span>|
|📝 <span class="inline-draft">Under Review</span>|
|⚠️ <span class="inline-warning">Warning</span>|
|❌ <span class="inline-danger">Needs work</span>|

The interfaces have to go through a few stages to version static interface for AIDL usage, whilst it's untested as a design, or there's major changes required, we cannot not approve first interface version.

- Phase 1, basic defined is completed, A/V up and running based on this 
- Phase 2, remove shared common area, upgrade `HAL Feature Profile (HPF)` based on Phase 1
- Phase 3, upgrades to interface from feedback
- Phase 4, approval for first release

## AV Components

This list provides an overview of various HAL components, their device profiles, and functionality within the system.


| HAL Component       | Device Profile | Description                                | Interface State (7/7)| Documentation State (6/7)|L1 Spec (0/7)|L2 Spec (0/7)|L3 Spec (0/7)|
| ------------------- | -------------- | ------------------------------------------ | ---------------|-------------------- |--------|--------|--------|
| [**Audio Decoder**](../../audio_decoder/current/audio_decoder.md)   | All            | Audio decoder control.               |✅ <span class="inline-success">Phase 1</span> [audio_decoder](/rdkcentral/rdk-halif-aidl/audiodecoder/current/com/rdk/hal/audiodecoder/)| **📝 Under Review** | X | X | X |
| [**Audio Sink**](../../audio_sink/current/audio_sink.md)      | All            | Audio sink and rendering control.          |✅ <span class="inline-success">Phase 1</span> | **📝 Under Review** | X | X | X |
| [**Audio Mixer**](../../audio_mixer/current/intro.md)     | All            | Audio mixing and transcoding control.      |✅ <span class="inline-success">Phase 1</span> | ❌"Not Started" | X | X | X |
| [**AV Buffer**](../../av_buffer/current/av_buffer.md)       | All            | A/V buffer and pool control.               |✅ <span class="inline-success">Phase 1</span> | **📝 Under Review** | X | X | X |
| [**AV Clock**](../../av_clock/current/av_clock.md)        | All            | Clock control for A/V playback.            |✅ <span class="inline-success">Phase 1</span> | **📝 Under Review** | X | X | X |
| [**Video Decoder**](../../video_decoder/current/video_decoder.md)   | All            | Video decoder control.                     |✅ <span class="inline-success">Phase 1</span> | **📝 Under Review**  | X | X | X |
| [**Video Sink**](../../video_sink/current/video_sink.md)      | All            | Video sink and rendering control.          |✅ <span class="inline-success">Phase 1</span> | **📝 Under Review**  | X | X | X |


## Non AV Components

This list provides an overview of various HAL components, their device profiles, and functionality within the system.

| HAL Component       | Device Profile | Description                                | Interface State (1/17) | Documentation State (0/17) |L1 Spec (0/17) |L2 Spec (0/17) |L3 Spec (0/17)|
| ------------------- | -------------- | ------------------------------------------ | ---------------|-------------------- |--------|--------|--------|
| [**Plane Control**](../../plane_control/current/plane_control.md)   | All            | Video and graphics plane control.          | ✅ <span class="inline-success">Phase 1</span> | **📝 Under Review** | X | X | X |

## Not Yet Documented

| HAL Component       | Device Profile | Description                                | Interface State| Documentation State |L1 Spec |L2 Spec |L3 Spec|
| ------------------- | -------------- | ------------------------------------------ | ---------------|-------------------- |--------|--------|--------|
| [**Composite Input**](../../composite_input/current/intro.md) | TV             | Composite A/V input control.               | ❌"Not Started"| ❌"Not Started" | X | X| X|
| [**FFV**](../../ffv/current/intro.md)             | TV             | Far field voice DSP control.               | ✅ <span class="inline-success">Phase 1</span>| ❌ "Not Started" | X | X| X|
| [**HDMI CEC**](../../cec/current/intro.md)        | All            | HDMI CEC message control.                  | ✅ <span class="inline-success">Phase 1</span>| ❌ "Not Started" | X | X| X|
| [**HDMI Input**](../../hdmi_input/current/intro.md)      | TV             | HDMI A/V input control.                    | ✅ <span class="inline-success">Phase 1</span>| !❌"Not Started" | X | X| X|
| [**HDMI Output**](../../hdmi_output/current/intro.md)     | STB            | HDMI A/V output control.                   | ✅ <span class="inline-success">Phase 1</span>| ❌ "Not Started"" | X | X| X|
| [**Secapi**](../../sec_api/current/intro.md)          | All            | Security API.                              | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X| X|
| [**Service Manager**](../../../vsi/service_manager/current/service_manager.md) | All            | Binder service registration and discovery. | ✅ <span class="inline-success">Phase 1</span>| **📝 Under Review** | X | X| X|
| [**Boot**](../../boot/current/intro.md)            | All            | Boot management and reset control.         | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |
| [**Broadcast**](../../broadcast/current/intro.md)       | All            | Digital TV broadcast control.             | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |
| [**CDM**](../../cdm/current/intro.md)             | All            | Content decryption module control for DRM. | ✅ <span class="inline-success">Phase 1 - To Be Removed</span>| ❌"Not Started" | X | X | X |
| [**Common**](../../common/current/intro.md)          | All            | Common HAL definitions.                    | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |
| [**Deep Sleep**](../../deep_sleep/current/intro.md)      | All            | Deep sleep control.                        | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |
| [**Device Info**](../../device_info/current/intro.md)     | All            | Device information.                        | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |
| [**Indicator**](../../indicator/current/intro.md)       | All            | Front panel LEDs and indicators.           | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |
| [**Panel Output**](../../panel/current/intro.md)    | TV             | TV display panel control.                  | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |
| [**Sensor**](../../sensor/current/intro.md)          | All            | Integrated sensor management.              | ✅ <span class="inline-success">Phase 1</span>| ❌"Not Started" | X | X | X |

## System Interfaces

The following 

| HAL Component       | Device Profile | Description                                | Interface State| Documentation State |L4 Testing |
| ------------------- | -------------- | ------------------------------------------ | ---------------|-------------------- |--------|
| [**Bluetooth**](../../../vsi/bluetooth/current/intro.md)       | All            | Bluetooth device control.                  | ⚠️ <span class="inline-warning">Warning</span>| ⚠️ <span class="inline-warning">Warning</span> | X |
| [**Filesystem**](../../../vsi/filesystem/current/intro.md)      | All            | Filesystem mounting.                       | ⚠️ <span class="inline-warning">Warning</span>| ⚠️ <span class="inline-warning">Warning</span> | X |
| [**Graphics**](../../../vsi/graphics/current/intro.md)        | All            | EGL, OpenGL ES and Vulkan graphics.       | ⚠️ <span class="inline-warning">Warning</span> | ⚠️ <span class="inline-warning">Warning</span> | X |
| [**Wi-Fi**](../../../vsi/wifi/current/intro.md)           | All            | Wi-Fi connection control.                  | ⚠️ <span class="inline-warning">Warning</span>| ⚠️ <span class="inline-warning">Warning</span>| X |
| [**Power Management**](../../../vsi/power_management/current/intro.md) | All | Power and energy efficiency control. | ⚠️ <span class="inline-warning">Warning</span>| ⚠️ <span class="inline-warning">Warning</span> | X |
| [**Network Management**](../../../vsi/network_management/current/intro.md) | All | Network configuration and monitoring. | ⚠️ <span class="inline-warning">Warning</span>| ⚠️ <span class="inline-warning">Warning</span> | X |



