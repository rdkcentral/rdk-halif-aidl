# HAL Interface Overview

| Status | Description |
| ------- | ------| 
|✅ <span class="inline-success">Complete</span>|
|📝 <span class="inline-draft">Under Review</span>|
|⚠️ <span class="inline-warning">Needs Work</span>|
|❌ <span class="inline-danger">Needs work</span>|

## Components

| HAL Component       | Device Profile | Description                                | Interface State | L1 Spec | L2 Spec | L3 Spec|
| ------------------- | -------------- | ------------------------------------------ | ------ | ---|---|---|
| [**Audio Decoder**](../halif/audio_decoder/audio_decoder_overview.md)   | All            | Audio decoder control.                     | **📝 Draft** | X | X | X |
| [**Audio Sink**](../halif/audio_sink/audio_sink_overview.md)      | All            | Audio sink and rendering control.          | !!! warning "In Progress" |
| [**Audio Mixer**](../halif/audio_mixer/intro.md)     | All            | Audio mixing and transcoding control.      | !!! info "Draft" |
| [**AV Buffer**]../(halif/av_buffer/intro.md)       | All            | A/V buffer and pool control.               | !!! success "Complete" |
| [**AV Clock**]../(halif/av_clock/intro.md)        | All            | Clock control for A/V playback.            | !!! warning "In Progress" |
| [**Boot**]../(halif/boot/intro.md)            | All            | Boot management and reset control.         | !!! success "Complete" |
| [**Broadcast**]../(halif/broadcast/intro.md)       | All            | Digital TV broadcast control.              | !!! info "Draft" |
| [**CDM**]../(halif/cdm/intro.md)             | All            | Content decryption module control for DRM. | !!! warning "In Progress" |
| [**Common**]../(halif/common/intro.md)          | All            | Common HAL definitions.                    | !!! success "Complete" |
| [**Deep Sleep**]../(halif/deep_sleep/intro.md)      | All            | Deep sleep control.                        | !!! success "Complete" |
| [**Device Info**]../(halif/device_info/intro.md)     | All            | Device information.                        | !!! warning "In Progress" |
| [**Indicator**]../(halif/indicator/intro.md)       | All            | Front panel LEDs and indicators.           | !!! danger "Not Started" |
| [**Panel Output**]../(halif/panel_output/intro.md)    | TV             | TV display panel control.                  | !!! success "Complete" |
| [**Plane Control**]../(halif/plane_control/intro.md)   | All            | Video and graphics plane control.          | !!! warning "In Progress" |
| [**Sensor**]../(halif/sensor/intro.md)          | All            | Integrated sensor management.              | !!! danger "Not Started" |
| [**Video Decoder**]../(halif/video_decoder/intro.md)   | All            | Video decoder control.                     | !!! success "Complete" |
| [**Video Sink**]../(halif/video_sink/intro.md)      | All            | Video sink and rendering control.          | !!! warning "In Progress" |


## Not Yet Documented

| HAL Component       | Device Profile | Description                                | Status |
| ------------------- | -------------- | ------------------------------------------ | ------ |
| [**Composite Input**]../(halif/composite_input/intro.md) | TV             | Composite A/V input control.               |  ❌"Not Started" |
| [**FFV**]../(halif/ffv/intro.md)             | TV             | Far field voice DSP control.               | ❌ "Not Started" |
| [**HDMI CEC**]../(halif/cec/intro.md)        | All            | HDMI CEC message control.                  | ❌ "In Progress" |
| [**HDMI Input**]../(halif/hdmi_input/intro.md)      | TV             | HDMI A/V input control.                    | !❌s "Complete" |
| [**HDMI Output**]../(halif/hdmi_output/intro.md)     | STB            | HDMI A/V output control.                   | ❌ "Draft" |
| [**Secapi**]../(halif/secapi/intro.md)          | All            | Security API.                              | ❌"Complete" |
| [**Service Manager**]../(halif/service_manager/intro.md) | All            | Binder service registration and discovery. | !❌ "Draft" |

## System Interfaces

| HAL Component       | Device Profile | Description                                | Status |
| ------------------- | -------------- | ------------------------------------------ | ------ |
| [**Bluetooth**](../vsi/bluetooth/intro.md)       | All            | Bluetooth device control.                  | !!! danger "Not Started" |
| [**Filesystem**](../vsi/filesystem/intro.md)      | All            | Filesystem mounting.                       | !!! danger "Not Started" |
| [**Graphics**](../vsi/graphics/intro.md)        | All            | EGL, OpenGL ES and Vulkan graphics.        | !!! danger "Not Started" |
| [**Wi-Fi**](../vsi/wifi/intro.md)           | All            | Wi-Fi connection control.                  | !!! danger "Not Started" |
| [**Power Management**](../vsi/power_management/intro.md) | All | Power and energy efficiency control. | !!! danger "Not Started" |
| [**Network Management**](../vsi/network_management/intro.md) | All | Network configuration and monitoring. | !!! danger "Not Started" |

This list provides an overview of various HAL components, their device profiles, and functionality within the system.

