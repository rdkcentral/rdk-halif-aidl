# Naming Conventions for the Repository

To ensure consistency and maintainability across the repository, we adhere to the following naming conventions:

## Directory and File Naming for Documentation

* **Case:** All directory and file names MUST be lowercase.
* **Word Separation:** Use underscores (`_`) instead of hyphens (`-`) or camel case to separate words in directory and file names.
* **Rationale:** This convention aligns with Unix-like system structures, ensuring smooth integration, ease of navigation, and simplified automation processes.

Documentation will be located under the `docs` directory, split into interfaces `hal`. `vsi`, then split my module, following the convention below.

### Examples

**Good:**

```bash
docs/audio_decoder/introduction_information.md
```

**Bad:**

```bash
docs/audio-decoder/intro-information.md       (Hyphen used)
docs/audiodecoder/introinformation.md         (No separator)
docs/audiodecoder/introInformation.md         (Camel case used)
docs/AudioDecoder/intro_information.md        (Incorrect case in directory)
```

## Directory and File Naming for Interfaces

* **Case:** All directory and file names MUST be lowercase.
* **Camel case:** The filename will match the Class defination extended with `.aidl` the class defination is defined using Camcel case.
* **Rationale:** This convention aligns with coding standards used for C++ classes.

Source code will be located under the `src` directory, then split my module, following the convention below.

**Good:**

```bash
src/audiodecoder/IAudioDecoderInterface.aidl
```

**Bad:**

```bash
srcs/audio-decoder/intro-information.md      (Hyphen used)
src/audiodecoder/introinformation.md         (All lower case)
src/audiodecoder/introInformation.md         (Camel case used, but first letter of filename not capitals)
src/AudioDecoder/intro_information.md        (Underscore used)
```

## Service Naming

A HAL service registers with the Service Manager under its **interface descriptor**, followed by `/` and an **instance name**:

```text
<interface-descriptor>/<instance>
```

The descriptor is the fully qualified AIDL name, generated from the interface, so it cannot drift from the AIDL and two packages cannot collide. Interfaces do not declare a name constant of their own.

| Service | Registered as |
| --- | --- |
| Singleton or manager | `com.rdk.hal.audiodecoder.IAudioDecoderManager/default` |
| One of several instances | `com.rdk.hal.drm.IDrmFactory/widevine` |

Clients look a service up the same way. In C++, `halcompat::getService<I>()` does it for the `default` instance:

```cpp
auto decoders = halcompat::getService<com::rdk::hal::audiodecoder::IAudioDecoderManager>();
// looks up "com.rdk.hal.audiodecoder.IAudioDecoderManager/default"
```

### Manager or Service Manager instances

Two patterns are used, and each fits a different kind of service:

* **A manager vends resources.** Use this for resources that are pooled, created at run time or arbitrated between clients: decoders, AV buffers, planes, clocks. One manager registers as `default` and hands out resource objects through its methods. The Service Manager cannot allocate or arbitrate, so these resources are never registered on their own.
* **Service Manager instances.** Use this for services that are fixed, differ from one another, and are discovered independently. Each registers under its own instance name. DRM is the worked example: each DRM system registers `com.rdk.hal.drm.IDrmFactory/<instanceName>` (for example `clearkey`, `widevine`, `playready`), with the instance names declared in `hfp-drm.yaml`.

Where two services already have different interfaces, as the thermal sensor (`IThermalSensor`) and the motion sensor manager (`IMotionSensorManager`) do, their descriptors differ and both register as `default`.

The VINTF manifest can require that a manager exists, but it cannot see the resources the manager vends. That is expected: the pool is dynamic.

## Systemd Naming of Launch

Naming convention for [systemd](../../vsi/systemd/current/systemd.md) services follows the convention for documentation i.e. `hal-audio_decoder_manager.service`

## Additional Considerations

* **Abbreviations:** Avoid abbreviations unless they are extremely common and well-understood within the project (e.g., `HAL`, `API`, `RDK`).  Prefer full words for clarity.
* **Length:** Keep file and directory names reasonably short and descriptive.  Avoid excessively long names.
* **Special Characters:** Do not use special characters (e.g., spaces, punctuation) in file or directory names, except for underscores as separators.
* **File Extensions:** Use appropriate file extensions for each file type (e.g., `.md` for Markdown, `.aidl` for AIDL).
* **Directory Structure:**  Consider adding a brief description of the intended directory structure.  For example, what types of files go into the `docs` directory, `src` directory, etc.  This helps new contributors understand the organization of the repository.
* **Consistency Across Project:** If there are other repositories in the project, it may be a good idea to align naming conventions.

