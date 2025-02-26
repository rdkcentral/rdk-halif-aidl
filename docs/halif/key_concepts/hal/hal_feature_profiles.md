# HAL Feature Profile (`HFP`)

The HAL Feature Profile (`HFP`) is a crucial declaration provided by the OEM when delivering a vendor layer implementation. It serves two primary purposes:

- **Test Driver:** The `HFP` informs the vendor test suite, enabling it to conduct targeted testing based on the declared feature set.
- **Capability Declaration:** The `HFP` lists all supported HAL features, allowing for verification against product requirements.

## File Syntax and Schema

The `HFP` is structured as a YAML file.  It resides within the vendor layer deliverables, typically in a designated configuration directory (e.g., `vendor/<vendor_name>/<platform>/config/hal_feature_profile.yaml`).

```yaml
hal_profile: "TV"        # Product/Platform identifier
hal_version: "1.0.0"     # HFP schema version
components:              # List of HAL components

  - name: "kernel"        # Component name
    version: "5.15.164"  # Version of the component

  - name: "avbuffer"      # Component name
    aidl_version: 1       # AIDL interface version
    non_secure_heap_bytes: 1048576 # Example: 1MB non-secure heap
    secure_heap_bytes: 524288   # Example: 512KB secure heap

  - name: "videodecoder"  # Component name
    aidl_version: 1       # AIDL interface version
    resources:            # Resource-specific information
      - id: 0             # Resource identifier
        codecs: ["H264", "HEVC"] # Supported codecs for this resource
      - id: 1             # Resource identifier
        codecs: ["MPEG2", "AV1"]  # Supported codecs for this resource

  - name: "cdm"           # Component name (Content Decryption Module)
    resources:            # Supported CDMs and their versions
      - name: "PlayReady"
        version: "4.4"
      - name: "Widevine"
        version: "L3" # Example: Security Level
      - name: "Fairplay"
        version: "4.0" # Example Version

  - name: "audio_decoder"
    aidl_version: 2
    supported_formats: ["AAC", "MP3", "AC3"]

  - name: "tuner"
    type: "dvb-c" # Example: Cable tuner
    frequency_range: "50-860 MHz"

  - name: "display"
    resolution: "1920x1080"
    hdr_support: true
    interfaces: ["HDMI", "DisplayPort"]

  - name: "network"
    interfaces: ["Ethernet", "WiFi"]
    wifi_standards: ["802.11a/b/g/n/ac/ax"]

  - name: "bluetooth"
    version: "5.2"
    profiles: ["A2DP", "HFP", "AVRCP"]

  - name: "input"
    devices: ["Remote Control", "Keyboard"]
    types: ["IR", "Bluetooth", "RF4CE"]
```

## Mandatory and Optional HALs and Features

The HFP explicitly lists all HAL components present in the vendor implementation.  While all listed components are considered *supported*, the HFP can also indicate whether a component or a specific feature within a component is *mandatory* or *optional*. This distinction is crucial for product compliance testing.  This can be achieved by adding properties to the component definition, for example:

```yaml
  - name: "cdm"
    mandatory: true # CDM is a mandatory component
    resources:
      - name: "PlayReady"
        version: "4.4"
        mandatory: true # PlayReady is mandatory
      - name: "Widevine"
        version: "L3"
        optional: true # Widevine is optional
```

## HFP Versioning

The `hal_version` field in the HFP specifies the version of the HFP schema itself.  This allows for future evolution of the HFP structure while maintaining backward compatibility.  The versioning scheme should follow semantic versioning (major.minor.patch).

## Tooling

Tools should be developed to parse and validate the HFP file.  This tooling will be essential for both the vendor test suite and for product requirements verification.  The tool should be able to:

- Validate the HFP against the schema.
- Check for mandatory components and features.
- Compare the HFP against product requirements.
- Generate reports summarizing the supported features.
