# HAL Interface Overview

| Status | Description |
| ------- | ------| 
|✅ <span class="inline-success">Complete</span>|
|📝 <span class="inline-draft">Under Review</span>|
|⚠️ <span class="inline-warning">Warning</span>|
|❌ <span class="inline-danger">Needs work</span>|

## Components

This list provides an overview of various HAL components, their device profiles, and functionality within the system.

| HAL Component       | Device Profile | Description                                | Interface State | L1 Spec | L2 Spec | L3 Spec|
| ------------------- | -------------- | ------------------------------------------ | ------ | ---|---|---|
| [**Audio Decoder**](../halif/audio_decoder/current/audio_decoder.md)   | All            | Audio decoder control.                     | **📝 Under Review** | X | X | X |
| [**Audio Sink**](../halif/audio_sink/current/audio_sink.md)      | All            | Audio sink and rendering control.          | **📝 Under Review** | X | X | X |
| [**Audio Mixer**](../halif/audio_mixer/current/intro.md)     | All            | Audio mixing and transcoding control.      | **📝 Draft** | X | X | X |
| [**AV Buffer**](../halif/av_buffer/current/intro.md)       | All            | A/V buffer and pool control.               | **📝 Under Review** | X | X | X |
| [**AV Clock**](../halif/av_clock/current/intro.md)        | All            | Clock control for A/V playback.            | **📝 Under Review** | X | X | X |
| [**Boot**](../halif/boot/current/intro.md)            | All            | Boot management and reset control.         | **📝 Draft** | X | X | X |
| [**Broadcast**](../halif/broadcast/current/intro.md)       | All            | Digital TV broadcast control.             | **📝 Draft** | X | X | X |
| [**CDM**](../halif/cdm/current/intro.md)             | All            | Content decryption module control for DRM. | **📝 Draft** | X | X | X |
| [**Common**](../halif/common/current/intro.md)          | All            | Common HAL definitions.                    | **📝 Draft** | X | X | X |
| [**Deep Sleep**](../halif/deep_sleep/current/intro.md)      | All            | Deep sleep control.                        | **📝 Draft** | X | X | X |
| [**Device Info**](../halif/device_info/current/intro.md)     | All            | Device information.                        | **📝 Draft** | X | X | X |
| [**Indicator**](../halif/indicator/current/intro.md)       | All            | Front panel LEDs and indicators.           | **📝 Draft** | X | X | X |
| [**Panel Output**](../halif/panel_output/current/intro.md)    | TV             | TV display panel control.                  | **📝 Draft** | X | X | X |
| [**Plane Control**](../halif/plane_control/current/intro.md)   | All            | Video and graphics plane control.          | **📝 Draft** | X | X | X |
| [**Sensor**](../halif/sensor/current/intro.md)          | All            | Integrated sensor management.              | **📝 Draft** | X | X | X |
| [**Video Decoder**](../halif/video_decoder/current/intro.md)   | All            | Video decoder control.                     | **📝 Draft** | X | X | X |
| [**Video Sink**](../halif/video_sink/current/intro.md)      | All            | Video sink and rendering control.          | **📝 Draft** | X | X | X |


## Not Yet Documented

| HAL Component       | Device Profile | Description                                | Interface State | L1 Spec | L2 Spec | L3 Spec|
| ------------------- | -------------- | ------------------------------------------ | ------ | ---|---|---|
| [**Composite Input**](../halif/composite_input/current/intro.md) | TV             | Composite A/V input control.               |  ❌"Not Started" | X | X| X|
| [**FFV**](../halif/ffv/current/intro.md)             | TV             | Far field voice DSP control.               | ❌ "Not Started" | X | X| X|
| [**HDMI CEC**](../halif/cec/current/intro.md)        | All            | HDMI CEC message control.                  | ❌ "In Progress" | X | X| X|
| [**HDMI Input**](../halif/hdmi_input/current/intro.md)      | TV             | HDMI A/V input control.                    | !❌s "Complete" | X | X| X|
| [**HDMI Output**](../halif/hdmi_output/current/intro.md)     | STB            | HDMI A/V output control.                   | ❌ "Draft" | X | X| X|
| [**Secapi**](../halif/secapi/current/intro.md)          | All            | Security API.                              | ❌"Complete" | X | X| X|
| [**Service Manager**](../halif/service_manager/current/intro.md) | All            | Binder service registration and discovery. | !❌ "Under Review" | X | X| X|

## System Interfaces

| HAL Component       | Device Profile | Description                                | Interface State | L1 Spec | L2 Spec | L3 Spec|
| ------------------- | -------------- | ------------------------------------------ | ------ | ---|---|---|
| [**Bluetooth**](../vsi/bluetooth/current/intro.md)       | All            | Bluetooth device control.                  | **📝 Draft** | X | X | X |
| [**Filesystem**](../vsi/filesystem/current/intro.md)      | All            | Filesystem mounting.                       | **📝 Draft** | X | X | X |
| [**Graphics**](../vsi/graphics/current/intro.md)        | All            | EGL, OpenGL ES and Vulkan graphics.        | **📝 Draft** | X | X | X |
| [**Wi-Fi**](../vsi/wifi/current/intro.md)           | All            | Wi-Fi connection control.                  | **📝 Draft** | X | X | X |
| [**Power Management**](../vsi/power_management/current/intro.md) | All | Power and energy efficiency control. | **📝 Draft** | X | X | X |
| [**Network Management**](../vsi/network_management/current/intro.md) | All | Network configuration and monitoring. | **📝 Draft** | X | X | X |



