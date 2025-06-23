# HAL Feature Profile (`HFP`)

The **HAL Feature Profile (HFP)** is a structured, YAML-based declaration provided by OEMs to define the supported feature set for their vendor layer implementation. It serves as both a **machine-readable contract** and **validation reference** between the platform and RDK middleware.

---

## Document Version Information

| Version | Date        | Author       | Comment         |
| ------- | ----------- | ------------ | --------------- |
| 1.2     | 23 Jun 2025 | G. Weatherup | Improved format |
| 1.1     | 24 Mar 2025 | G. Weatherup | Added clarity   |
| 1.0     | 17 Feb 2025 | G. Weatherup | First revision  |

---

## Purpose and Runtime Role

The HAL Feature Profile (HFP) defines the platform's supported HAL interfaces and capabilities in a structured, machine-readable format. It plays a foundational role in platform validation, runtime capability discovery, and certification.

### Key Functions

* **Test Driver Configuration**
  Guides the Vendor Test Suite (VTS) in dynamically tailoring test coverage. Declared resources, capabilities, and constraints drive targeted validation based on the actual platform configuration.

* **Interface Capability Declaration**
  Serves as a machine-readable contract between the platform vendor and RDK middleware. Enables runtime introspection of supported features using methods such as `getCapabilities()` and `getPlatformCapabilities()`.

* **Operational Semantics and Return Values**
  Clarifies expected runtime behaviours, especially where AIDL definitions return abstract or variable feature sets. For example, codec support or event types may be enumerated here even if not explicitly codified in the interface.

* **Compliance and Certification**
  Acts as the authoritative reference for determining mandatory versus optional feature support. Used by QA and certification pipelines to assert conformance with product requirements.

Maintaining the HFP in sync with the actual HAL implementation and runtime behaviour is essential for reliable system integration, middleware compatibility, and accurate feature negotiation.

---

## HFP Location and Delivery

Each platform is expected to define and maintain its own HAL Feature Profile (`HFP`) tailored to its **driver configuration** and **hardware capabilities**. The responsibility for creating and updating the HFP lies with the **OEM or platform integrator**.

The examples provided in the HAL repository serve as **reference templates** only. They illustrate the expected **format**, **schema**, and **field usage**, but are not exhaustive or mandatory definitions.

### Standard File Locations

```text
vendor/<vendor_name>/<platform>/config/hal_feature_profile.yaml
```

Component-level fragments may be stored in:

```text
vendor/<vendor_name>/<platform>/config/components/<component>.yaml
```

These may be merged via include directives, YAML anchors, or pre-processing scripts.

---

## File Structure

The HFP consists of:

* A **top-level metadata block** (`hal`) with platform and schema version
* A **list of HAL components**, either embedded or included
* **Per-component declarations** that define interface versions, resources, and feature sets

### Parent File Example

```yaml
hal:
  profile: "TV"
  platform: "Sky Glass"
  schema_version: "1.2.0"

  components:
    - include: "audio_decoder.yaml"
    - include: "videodecoder.yaml"
    - include: "panel.yaml"
```

---

## Component Schema

Each HAL component follows a consistent and extensible structure:

```yaml
<component_name>:                  # e.g., videodecoder, audiosink
  interfaceVersion: current        # AIDL interface version

  - id: 0                          # Resource ID (multi-instance support)
    <field1>: <value>              # E.g., supportsSecure: true
    <field2>:                      # Optional list field
      - VALUE_A
      - VALUE_B

  platformCapabilities:            # Optional key-value metadata
    systemMixerSampleRateHz: 48000

  events:                          # Event callbacks supported by listener
    - onStarted
    - onError
```

### Example: `videodecoder.yaml`

```yaml
videodecoder:
  interfaceVersion: current

  - id: 0
    supportedCodecs:
      - H264
      - HEVC
    supportsSecure: true

  - id: 1
    supportedCodecs:
      - MPEG2
      - AV1
    supportsSecure: false

  platformCapabilities:
    maxResolution: "4K"
    maxFramerate: 60

  events:
    - onDecoderError
    - onFrameReady
```

---

## Mandatory and Optional HALs and Features

The HFP must explicitly list all supported HAL components. Each HAL or resource block can be marked as `mandatory: true` or `optional: true`.

Fields that are not supported may be omitted, but explicit negation is recommended for clarity:

```yaml
cdm:
  interfaceVersion: current
  mandatory: true

  - id: 0
    name: "PlayReady"
    version: "4.4"
    mandatory: true

  - id: 1
    name: "Widevine"
    version: "L3"
    optional: true
```

---

## Tooling and Automation

Tooling for HFP consumption and validation should support:

* **YAML Schema Validation**: Ensure integrity of the file structure
* **Test Vector Generation**: Generate test coverage based on capability matrix
* **Gap Detection**: Report missing mandatory components or undeclared features
* **Compliance Reporting**: Output summaries for QA, integrators, or certification

---

## Versioning and Schema Evolution

The `schema_version` field under the `hal` root must follow [semantic versioning](https://semver.org):

* **MAJOR** – Breaking changes to the schema or logic
* **MINOR** – Backwards-compatible enhancements or field additions
* **PATCH** – Minor metadata updates or clarifications

This ensures that both platform teams and automation tooling can safely track and adopt schema changes over time.
