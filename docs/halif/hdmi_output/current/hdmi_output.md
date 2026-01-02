# HDMIOutput HAL Interface

## Overview

The `HDMIOutput` HAL interface manages the configuration and control of HDMI output ports on the platform. It provides abstraction over HDMI-specific signalling, capabilities negotiation (such as EDID, VICs, and HDCP), and output control modes. This interface ensures consistent interaction with higher layers (such as the RDK display manager or AV controller) while remaining agnostic to platform-specific HDMI PHY and driver implementations.

This HAL does not manage audio routing (delegated to `AudioSink`) or video plane composition (delegated to `PlaneControl`).

---

!!! info "References"
    |||
    | ------------------------------------ | ------------------------------------------------------------- |
    | **Interface Definition**             | [hdmioutput](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/hdmioutput/current/com/rdk/hal/hdmioutput) |
    | **HAL Interface Type**               | [AIDL and Binder](../../../introduction/aidl_and_binder.md)   |
    | **Initialization Unit**              | [systemd service](../../../vsi/systemd/current/systemd.md)    |

---

!!! tip "Related Pages"
    * [HAL Feature Profile](../../key_concepts/hal/hal_feature_profiles.md)
    * [HAL Interface Overview](../../key_concepts/hal/hal_interfaces.md)
    * [Display Pipeline Overview](../../display/architecture.md)

---

## Functional Overview

The `HDMIOutput` HAL provides control over:

* HDMI video output formats (VIC selection)
* Colorimetry and pixel formats
* HDCP capability negotiation and status reporting
* Output connection events (e.g., hotplug detection)
* SPD InfoFrame and AFD metadata
* Output modes, such as SDR/HDR

---

## Implementation Requirements

| #                    | Requirement                                                               | Comments                                          |
| -------------------- | ------------------------------------------------------------------------- | ------------------------------------------------- |
| **HAL.HDMIOutput.1** | The service shall support enumeration of connected HDMI outputs.          | Use `IHDMIOutputManager.getHDMIOutputIds()`       |
| **HAL.HDMIOutput.2** | The service shall allow clients to configure HDMI output via property-based API. | See `IHDMIOutputController.setProperty()`        |
| **HAL.HDMIOutput.3** | The service shall emit events on hotplug connect/disconnect.              | Via `IHDMIOutputControllerListener.onHotPlugDetectStateChanged()` |
| **HAL.HDMIOutput.4** | The implementation shall expose EDID capabilities through `Capabilities`. | See `getCapabilities()`                           |
| **HAL.HDMIOutput.5** | No HDCP re-authentication shall be triggered on VIC or colour mode switch. | HDCP state must persist across mode changes      |
| **HAL.HDMIOutput.6** | AVMUTE shall be asserted by HAL implementation according to HDMI and HDCP specifications. | Vendor layer responsibility                       |
| **HAL.HDMIOutput.7** | When outputting to a 4:3 aspect ratio sink display, 16:9 composited graphics and video shall be letterboxed inside the 4:3 output frame with appropriate AFD signalling. | AFD shall indicate 16:9 content in 4:3 frame      |
| **HAL.HDMIOutput.8** | HDCP authentication shall initiate automatically immediately after device connection following `open()`. | Negotiate highest supported version (2.x over 1.x) |
| **HAL.HDMIOutput.9** | HDCP Key Revocation List (KRL) management is the vendor layer responsibility, updated only via firmware update. | |
| **HAL.HDMIOutput.10** | The HAL shall provide EDID data to RDK Middleware for parsing.           | Includes aspect ratio, dimensions, HDR support, pixel formats, HDMI version |

---

## Interface Definitions

| AIDL File                              | Description                                                          |
| -------------------------------------- | -------------------------------------------------------------------- |
| `IHDMIOutput.aidl`                     | Main interface for querying output state and capabilities            |
| `IHDMIOutputController.aidl`           | Allows clients to control and configure HDMI output formats          |
| `IHDMIOutputManager.aidl`              | Resource discovery for multi-output devices                          |
| `IHDMIOutputEventListener.aidl`        | Event listener interface for HDMI-related events                     |
| `Capabilities.aidl`                    | Describes supported video formats, pixel formats, color spaces, etc. |
| `HDCPStatus.aidl`                      | Enum for HDCP authentication states                                  |
| `HDROutputMode.aidl`                   | HDR mode declaration                                                 |
| `SPDSource.aidl`                       | Enum for identifying SPD signal types                                |
| `VIC.aidl`                             | Enum for HDMI Video ID Codes                                         |
| `Property.aidl`, `PropertyKVPair.aidl` | General key-value properties and HDMI metadata support               |

---

## Initialization

The HAL service should be initialized via a systemd unit and must register with the Service Manager under the name defined in `IHDMIOutputManager.serviceName` ("hdmioutput"). It must be ready before middleware components attempt to query or bind.

---

## Product Customization

* Each HDMI port is exposed as a resource instance via `IHDMIOutputManager`
* Capabilities per resource are exposed via `Capabilities` and may vary per port (e.g., 4K vs 1080p support)
* SPD and AFD support are optional; presence is indicated in `Capabilities`

---

## System Context

```mermaid
flowchart TD
    Client --> IHDMIOutputController
    Client --> IHDMIOutput
    Client --> IHDMIOutputEventListener
    IHDMIOutputEventListener -->|Events| Client
    IHDMIOutput -->|Capabilities| Client
```

---

## Resource Management

* HDMI outputs are identified by logical IDs.
* Each output may have an independent controller and state.
* Event listeners can be registered/unregistered dynamically.

---

## Operation and Data Flow

* Clients query supported modes via `getCapabilities()`
* Desired mode is set using `IHDMIOutputController.setProperty()` with appropriate VIC and format properties
* EDID and HDCP status are read-only and polled or event-driven
* SPD InfoFrames and AFD metadata are queried or emitted if supported

---

## Modes of Operation

* SDR (Standard Dynamic Range)
* HDR10
* HLG (Hybrid Log-Gamma)
* Modes are applied per port and negotiated based on sink capabilities

---

## Event Handling

| Event       | Callback                         | Description                                          |
| ----------- | -------------------------------- | ---------------------------------------------------- |
| Hotplug     | `onHotPlugDetectStateChanged()`  | Notifies client when a cable is connected or removed |
| EDID Change | `onEDID()`                       | Indicates that sink EDID has changed                 |
| HDCP        | `onHDCPStatusChanged()`          | HDCP authentication state updates                    |

---

## State Machine / Lifecycle

1. **UNAVAILABLE**: No HDMI sink detected
2. **AVAILABLE**: Sink detected, capabilities read
3. **CONFIGURED**: VIC set and HDMI signal configured
4. **ERROR**: Error state due to HDCP failure or signal loss

---

## Data Format / Protocol Support

| Format | Use Case                   | Support Level |
| ------ | -------------------------- | ------------- |
| VIC    | HDMI video mode definition | Mandatory     |
| SPD    | Source Product InfoFrame   | Optional      |
| AFD    | Active Format Description  | Optional      |

---

## HDCP Authentication and Recovery

### HDCP State Machine

```mermaid
stateDiagram-v2
    [*] --> UNKNOWN: No Sink
    UNKNOWN --> UNAUTHENTICATED: HPD Asserted
    UNAUTHENTICATED --> AUTHENTICATION_IN_PROGRESS: start()
    AUTHENTICATION_IN_PROGRESS --> AUTHENTICATED: Success
    AUTHENTICATION_IN_PROGRESS --> AUTHENTICATION_FAILURE: Failure
    AUTHENTICATION_FAILURE --> UNAUTHENTICATED: Retry
    AUTHENTICATED --> AUTHENTICATION_FAILURE: Link Lost
    AUTHENTICATED --> UNAUTHENTICATED: HPD Lost
    UNAUTHENTICATED --> UNKNOWN: Cable Disconnect
```

### HDCP Protocol Version Negotiation

- The HAL shall always attempt to negotiate the highest HDCP version supported by both source and sink
- Negotiation order: HDCP 2.3 → HDCP 2.2 → HDCP 1.4 → HDCP 1.0
- Version downgrade is automatic if higher versions fail authentication
- Current and receiver versions are exposed via `getHDCPCurrentVersion()` and `getHDCPReceiverVersion()`

### Authentication Failure Recovery

**Automatic Retry Strategy:**

1. On authentication failure, the HAL shall automatically retry up to 3 times with exponential backoff
2. Retry intervals: 100ms, 500ms, 1000ms
3. If all retries fail, the HAL transitions to `AUTHENTICATION_FAILURE` state
4. The middleware is notified via `onHDCPStatusChanged(AUTHENTICATION_FAILURE, version)`

**Middleware Recovery Options:**

- **Standby Cycle**: Middleware may trigger standby/wake cycle to force re-initialization
- **Close/Reopen**: Middleware may close and reopen the HDMI output via `IHDMIOutput.close()` and `open()`
- **Content Handling**: DRM-protected content playback must be suspended during authentication failure

### No-Sink Behaviour

**When no HDMI sink is attached:**

- The output remains in `READY` state after `open()` completes
- Hot Plug Detect (HPD) state is reported as `false` via `onHotPlugDetectStateChanged(false)`
- HDCP status remains `UNKNOWN`
- Graphics and video refresh rates default to platform-defined fallback (typically 60Hz)
- No HDMI signal is transmitted on the physical output
- Upon sink connection, `onHotPlugDetectStateChanged(true)` is fired, followed by `onEDID()`

---

## Hot Plug Scenarios

### Connect Sequence (No DRM Content)

```mermaid
sequenceDiagram
    participant Sink
    participant HAL
    participant MW as Middleware
    participant App

    Sink->>HAL: Cable Connected (HPD Asserted)
    HAL->>MW: onHotPlugDetectStateChanged(true)
    HAL->>Sink: Read EDID
    Sink-->>HAL: EDID Data
    HAL->>MW: onEDID(edidData)
    MW->>MW: Parse EDID (capabilities)
    MW->>App: Notify Display Connected
    MW->>HAL: setProperty(VIC, ...)
    MW->>HAL: start()
    HAL->>Sink: Initiate HDCP
    Sink-->>HAL: HDCP Authenticated
    HAL->>MW: onHDCPStatusChanged(AUTHENTICATED, 2.2)
    HAL->>MW: onFrameRateChanged()
    App->>MW: Begin Content Playback
```

### Connect Sequence (DRM Content)

```mermaid
sequenceDiagram
    participant Sink
    participant HAL
    participant MW as Middleware
    participant DRM
    participant App

    Sink->>HAL: Cable Connected (HPD Asserted)
    HAL->>MW: onHotPlugDetectStateChanged(true)
    HAL->>Sink: Read EDID
    Sink-->>HAL: EDID Data
    HAL->>MW: onEDID(edidData)
    MW->>MW: Parse EDID
    MW->>HAL: start()
    HAL->>Sink: Initiate HDCP
    Sink-->>HAL: HDCP Authenticated
    HAL->>MW: onHDCPStatusChanged(AUTHENTICATED, 2.2)
    MW->>DRM: Verify HDCP Version
    DRM-->>MW: Playback Authorized
    MW->>App: Notify Ready for DRM Content
    App->>MW: Begin Encrypted Playback
```

### Disconnect Sequence

```mermaid
sequenceDiagram
    participant Sink
    participant HAL
    participant MW as Middleware
    participant App

    Note over Sink,App: Content Playing
    Sink->>HAL: Cable Disconnected (HPD Lost)
    HAL->>MW: onHotPlugDetectStateChanged(false)
    MW->>App: Stop Playback
    HAL->>MW: onHDCPStatusChanged(UNKNOWN, UNDEFINED)
    MW->>HAL: stop()
    MW->>App: Display Disconnected
```

---

## Compositor Integration

### Aspect Ratio and Scaling Pipeline

```mermaid
flowchart LR
    A[Video Decoder<br/>16:9 Frame] --> B[Plane Control<br/>Scaling/Positioning]
    C[Graphics Compositor<br/>16:9 UI] --> B
    B --> D{Sink Aspect<br/>Ratio}
    D -->|16:9| E[HDMI Output<br/>No Scaling]
    D -->|4:3| F[HDMI Output<br/>Letterbox + AFD]
    E --> G[Sink Display]
    F --> G
    
    style A fill:#4CAF50
    style C fill:#2196F3
    style B fill:#FF9800
    style E fill:#9C27B0
    style F fill:#9C27B0
    style G fill:#607D8B
```

**Scaling Responsibility:**

- **Plane Control HAL**: Handles video plane scaling and positioning within the compositor frame buffer
- **HDMI Output HAL**: Applies letterboxing when sink aspect ratio differs from compositor output
- **Middleware**: Configures appropriate VIC based on EDID and applies AFD metadata

**4:3 Display Handling:**

- Compositor produces 16:9 frame (e.g., 1920×1080)
- HDMI Output HAL selects 4:3 VIC (e.g., VIC 4: 720×480)
- Content is letterboxed with black bars top/bottom
- AFD InfoFrame indicates "16:9 content in 4:3 frame" for sink-side processing

---

## Platform Capabilities

Platform capabilities are defined in the HAL Feature Profile (HFP) and exposed at runtime via `IHDMIOutputManager.getCapabilities()` and per-resource `IHDMIOutput.getCapabilities()`.

### HAL Feature Profile Example

The HFP defines the maximum capabilities of the platform's HDMI output implementation. This is the reference for what the HAL API can deliver, though actual runtime capabilities may be constrained by hardware or sink limitations.

```yaml
hdmioutput:
  interfaceVersion: current

  resources:
    # Logical HDMI output port 0
    - id: 0

      # Supported HDMI specification versions
      supportedVersions:
        - HDMI_1_4
        - HDMI_2_0
        - HDMI_2_1

      # Supported Video ID Codes (VICs) - HDMI standardised video modes
      supportedVICs:
        - VIC4_1280_720_P_60_16_9         # 720p @ 60Hz
        - VIC16_1920_1080_P_60_16_9       # 1080p @ 60Hz
        - VIC97_3840_2160_P_60_16_9       # 4K UHD @ 60Hz

      # Colorimetry standards for colour space definition
      supportedColorimetries:
        - NO_DATA
        - SMPTE_170M           # BT.601 - Standard Definition
        - ITU_R_BT709          # BT.709 - High Definition
        - EXTENDED_COLORIMETRY # Signals use of ExtendedColorimetry field

      # Extended colorimetry values (when EXTENDED_COLORIMETRY is used)
      supportedExtendedColorimetry:
        - XV_YCC_601
        - XV_YCC_709
        - S_YCC_601
        - OP_YCC_601
        - OP_RGB
        - BT2020_C_YCC         # BT.2020 constant luminance
        - BT2020_RGB_YCC       # BT.2020 RGB or YCC
        - ADDITIONAL_COLORIMETRY_EXTENSION

      # Additional colorimetry extensions (DCI-P3)
      supportedAdditionalColorimetryExtensions:
        - DCI_P3_RGB_D65
        - DCI_P3_RGB_THEATER

      # Supported color bit depths
      supportedColorDepths:
        - 8
        - 10
        - 12

      # Pixel encoding formats
      supportedPixelFormats:
        - RGB_444    # Full RGB 4:4:4
        - YCBCR_422  # Chroma subsampled 4:2:2
        - YCBCR_444  # Full chroma 4:4:4
        - YCBCR_420  # Chroma subsampled 4:2:0

      # HDCP protocol versions for content protection
      supportedHDCPVersions:
        - VERSION_1_X  # HDCP 1.x (up to 1080p)
        - VERSION_2_X  # HDCP 2.x (4K and HDR)

      # High Dynamic Range output modes
      supportedHDROutputModes:
        - AUTO         # Automatic based on content
        - HLG          # Hybrid Log-Gamma (broadcast HDR)
        - HDR10        # HDR10 static metadata
        - HDR10_PLUS   # HDR10+ dynamic metadata
        - DOLBY_VISION # Dolby Vision

      # Content type signalling (AVI InfoFrame ITC/CN fields)
      supportedContentTypes:
        - UNSPECIFIED
        - GRAPHICS
        - PHOTO
        - CINEMA
        - GAME

      # Active Format Description values
      supportedAFD:
        - UNSPECIFIED
        - SAME_AS_PICTURE
        - CENTER_4_3
        - CENTER_16_9
        - CENTER_14_9

      # Scan information values
      supportedScanInformation:
        - NO_DATA
        - OVERSCAN
        - UNDERSCAN

      # Configurable properties via setProperty() API
      supportedProperties:
        - RESOURCE_ID
        - VIC
        - CONTENT_TYPE
        - AFD
        - HDR_OUTPUT_MODE
        - SCAN_INFORMATION

      # Source Product Description (SPD) InfoFrame source types
      supportedSPDSources:
        - DIGITAL_STB
        - DVD_PLAYER
        - D_VHS
        - HDD_VIDEORECORDER
        - DVC
        - DSC
        - VIDEO_CD
        - GAME
        - PC_GENERAL
        - BLU_RAY_DISC
        - SUPER_AUDIO_CD
        - HD_DVD

      # Advanced HDMI features
      supports3D: true           # Stereo 3D video support
      supportsFRL: true          # Fixed Rate Link (HDMI 2.1)
      supportsVRR: true          # Variable Refresh Rate
      supportsFreeSync: true     # AMD FreeSync
      supportsQMS: true          # Quick Media Switching
      supportsALLM: true         # Auto Low Latency Mode
      supportsQFT: true          # Quick Frame Transport

  # Platform-wide static capabilities
  platformCapabilities:
    maxSupportedResolution: "3840x2160"   # 4K UHD maximum
    maxFramerate: 60                       # Hz
    nativeFrameRate: 59.94                 # Territory-specific default (NTSC)
    freeSync: FREESYNC_PREMIUM             # AMD FreeSync tier
    supportsHotplugEvents: true            # HPD event delivery
    supportsAFD: true                      # Active Format Description signalling
    supportsSPDInfoFrame: true             # Source Product Description InfoFrame
```

### Capability Categories

**HDMI Version Support:**

* **HDMI Versions**: Supported HDMI specification versions (1.4, 2.0, 2.1)
* Determines available bandwidth and feature support (FRL, VRR, etc.)

**Video Mode Capabilities:**

* **VICs**: Standardised HDMI video modes (resolution, frame rate, aspect ratio)
* **Colorimetry**: Base colour space standards (SMPTE_170M/BT.601, ITU_R_BT709/BT.709, EXTENDED_COLORIMETRY)
* **Extended Colorimetry**: Advanced colour spaces (xvYCC, sYCC, opYCC, BT.2020, DCI-P3)
* **Additional Colorimetry**: DCI-P3 RGB variants (D65, Theater)
* **Color Depths**: Bits per color component (8, 10, 12, 16)
* **Pixel Formats**: Encoding formats (RGB_444, YCBCR_420/422/444)

**Content Protection:**

* **HDCP Versions**: Supported HDCP protocol versions (VERSION_1_X, VERSION_2_X)
* **KRL Management**: Key Revocation List handling (vendor layer responsibility)

**HDR Support:**

* **HDR Output Modes**: AUTO, HDR10, HDR10_PLUS, HLG, DOLBY_VISION
* **Properties**: VIC, CONTENT_TYPE, AFD, HDR_OUTPUT_MODE, SCAN_INFORMATION

**InfoFrame Support:**

* **Content Types**: GRAPHICS, PHOTO, CINEMA, GAME (AVI InfoFrame ITC/CN fields)
* **AFD**: Active Format Description for aspect ratio signalling (SAME_AS_PICTURE, CENTER_4_3, CENTER_16_9, CENTER_14_9)
* **Scan Information**: Overscan/underscan behaviour (OVERSCAN, UNDERSCAN)
* **SPD**: Source Product Description for device identification (DIGITAL_STB, DVD_PLAYER, GAME, etc.)

**Advanced HDMI 2.1 Features:**

* **3D Support**: Stereo 3D video output
* **FRL**: Fixed Rate Link for higher bandwidth
* **VRR**: Variable Refresh Rate for gaming
* **FreeSync**: AMD FreeSync support (with tier: FREESYNC, FREESYNC_PREMIUM, FREESYNC_PREMIUM_PRO)
* **QMS**: Quick Media Switching (VRR-based seamless format changes)
* **ALLM**: Auto Low Latency Mode for gaming
* **QFT**: Quick Frame Transport (Fast VActive signaling)

### Runtime Capability Discovery

**Platform-Level Query:**

```aidl
IHDMIOutputManager manager = /* get service */;
PlatformCapabilities platformCaps = manager.getCapabilities();
```

**Resource-Level Query:**

```aidl
IHDMIOutput.Id[] ids = manager.getHDMIOutputIds();
IHDMIOutput output = manager.getHDMIOutput(ids[0]);
Capabilities caps = output.getCapabilities();
```

**Example Platform Capabilities (Reference):**

* **HDMI Versions**: 1.4, 2.0, 2.1
* **Maximum resolution**: 3840×2160 (4K UHD)
* **Maximum frame rate**: 60Hz
* **Native frame rate**: 59.94Hz (NTSC) or 50Hz (PAL)
* **Colorimetry**: SMPTE_170M, ITU_R_BT709, EXTENDED_COLORIMETRY (BT.2020, DCI-P3)
* **Color depths**: 8, 10, 12-bit
* **Pixel formats**: RGB_444, YCBCR_420/422/444
* **HDR output modes**: AUTO, HDR10, HDR10_PLUS, HLG, DOLBY_VISION
* **HDCP versions**: VERSION_1_X, VERSION_2_X
* **Advanced features**: 3D, FRL, VRR, FreeSync (Premium tier), QMS, ALLM, QFT

---
