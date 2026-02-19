# HAL Feature Profile (HFP)

The HAL Feature Profile (HFP) is a YAML-based declaration provided by OEMs to define the capabilities of their vendor layer implementation. It serves critical functions:

* **Test Driver Configuration:** Enables the vendor test suite to perform targeted testing based on the declared feature set.
* **Capability Declaration:** Provides a comprehensive list of supported HAL features for verification against product requirements.

Each HAL component defines its own `hfp_xxx.yaml` within the vendor layer deliverables, typically located in a configuration directory (e.g., `vendor/<vendor_name>/<platform>/config/`).

## File Syntax and Schema

The HFP utilizes YAML syntax for structured data representation, this is an example format the actual format is defined with the components.

```yaml
hal:
  profile: "TV" # Profile Type
  platform: "Sky Glass" # Platform Identifier
  schema_version: "1.2.0" # HFP Schema Version

  components:
    kernel:
      version: "5.15.164"

    av_buffer:
      non_secure_heap_bytes: 1048576 # 1MB
      secure_heap_bytes: 524288 # 512KB

    video_decoder:
      resources:
        - id: 0
          codecs: ["H264", "HEVC"]
          max_resolution: "4K"
          max_fps: 60
          bit_depth: 10
        - id: 1
          codecs: ["MPEG2", "AV1"]
          max_resolution: "1080p"
          max_fps: 30
          bit_depth: 8

    cdm:
      mandatory: true
      resources:
        PlayReady:
          version: "4.4"
          mandatory: true
          secure_storage: true
          concurrent_sessions: 2
        WideVine:
          version: "L3"
          mandatory: false
          secure_storage: false
          concurrent_sessions: 1
        FairPlay:
          version: "4.0"
          mandatory: false

    audio_decoder:
      supported_formats: ["AAC", "MP3", "AC3", "DTS", "Dolby Digital"]
      max_channels: 8
      sample_rate: 192000

    tuner:
      type: "dvb-c"
      frequency_range: "50-860 MHz"
      modulation: ["QAM16", "QAM64", "QAM256"]
      bandwidth: 8

    display:
      resolution: "1920x1080"
      hdr_support: true
      interfaces: ["HDMI", "DisplayPort"]
      refresh_rate: 60
      color_space: "BT.2020"

    network:
      interfaces: ["Ethernet", "WiFi"]
      wifi_standards: ["802.11a", "802.11b", "802.11g", "802.11n", "802.11ac", "802.11ax"]
      ethernet_speed: "1Gbps"
      ipv6_support: true

    bluetooth:
      version: "5.2"
      profiles: ["A2DP", "HFP", "AVRCP", "BLE"]
      le_coded_phy: true

    input:
      devices:
        - name: "Remote Control"
          types: ["IR", "Bluetooth", "RF4CE"]
          features: ["Voice Control", "Navigation"]
        - name: "Keyboard"
          types: ["Bluetooth"]
          features: ["Text Input"]

    camera:
      resolution: "1920x1080"
      fps: 30
      auto_focus: true
      hdr: true

    mic:
      channels: 2
      noise_cancellation: true
      echo_cancellation: true

    graphics_compositor:
      layers: 4
      alpha_blending: true
      scaling: true
      rotation: true

    power_management:
      states: ["On", "Standby", "Deep Sleep"]
      wake_sources: ["Remote", "Network", "Timer"]
      power_consumption:
        standby: "0.5W"
        deep_sleep: "0.1W"

    telemetry:
      supported_metrics: ["CPU Usage", "Memory Usage", "Network Throughput", "Temperature"]
      reporting_interval: 60 # seconds
      logging_levels: ["Error", "Warning", "Info", "Debug"]

    drm_session_management:
      max_concurrent_sessions: 4
      secure_storage_types: ["TEE", "Secure Flash"]
      persistent_sessions: true
```

## Mandatory and Optional HALs and Features

The HFP explicitly lists all supported HAL components. Components or specific features within them can be marked as `mandatory` to indicate their requirement status. Any field not defined can be assumed to be `false` but for clarity can also be stated e.g. `mandatory: false`.

```yaml
hal:
  components:
    cdm:
      mandatory: true
      resources:
        PlayReady:
          version: "4.4"
          mandatory: true
        WideVine:
          version: "L3"
          mandatory: false
```

## HFP Versioning

The `schema_version` field adheres to semantic versioning (major.minor.patch) to ensure backward compatibility as the HFP schema evolves.

## Tooling

Dedicated tools are essential for creating and validating the HFP will be created:

* **Schema Validation:** Implements robust validation against a defined schema (e.g., JSON Schema).
* **HFP Generator:** Tool to help create HFP files.
