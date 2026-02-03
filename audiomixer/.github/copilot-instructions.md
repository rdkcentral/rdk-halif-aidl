# RDK Audio Mixer HAL - AI Coding Assistant Instructions

## Project Overview
This is an **Android AIDL-based HAL interface definition** for RDK (Reference Design Kit) audio mixer functionality. The codebase defines the contract between RDK middleware and vendor audio implementations—it contains **only interface definitions**, not implementations.

**Key architectural points:**
- This is a multi-module RDK HAL project; never invoke CMake at module level directly
- Interfaces follow Android HIDL/AIDL patterns with `@VintfStability` annotations
- Each mixer instance represents a logical/physical audio resource (MS12, DTS, system mixer)
- Supports both secure (DRM) and non-secure audio paths

## Directory Structure
```
current/
├── CMakeLists.txt              # AIDL compilation configuration
├── hfp-audiomixer.yaml         # HAL Feature Profile - platform capabilities
└── com/rdk/hal/audiomixer/     # AIDL interface definitions
    ├── IAudioMixerManager.aidl # Entry point - mixer enumeration
    ├── IAudioMixer.aidl        # Core mixer control interface
    ├── IAudioOutputPort.aidl   # Output port (HDMI, SPDIF) control
    └── [data types & enums]
```

## Critical Conventions

### AIDL File Organization
1. **Interfaces** (prefix `I`): Define service contracts
   - `IAudioMixerManager`: Entry point, discovers available mixers
   - `IAudioMixer`: Per-instance mixer control (routing, properties)
   - `IAudioOutputPort`: Port-specific control (volume, format)

2. **Parcelables**: Data structures for IPC (e.g., `Capabilities`, `Input`, `InputRouting`)

3. **Enums**: Type-safe constants with `@Backing(type="int")` annotations
   - Example: [ContentType.aidl](current/com/rdk/hal/audiomixer/ContentType.aidl) defines CLIP, STREAM, TTS

### Documentation Standards
- **ALL interfaces must have**:
  - `@brief` and `@details` doxygen-style comments
  - Multi-author attribution (Kennedy-Lamb, Stieglitz, Adler, Weatherup)
  - Copyright 2024/2025 RDK Management with Apache 2.0 license header

- **Function documentation includes**:
  - `@param[in]`/`@param[out]` for all parameters
  - `@return`/`@retval` for return values and success conditions
  - `@exception binder::Status` for error cases (e.g., `EX_ILLEGAL_ARGUMENT`)

Example from [IAudioMixer.aidl](current/com/rdk/hal/audiomixer/IAudioMixer.aidl#L108-L130):
```aidl
/**
 * @brief     Sets the audio source routing for one or more mixer inputs.
 * @details   Allows multiple audio [source -> mixer input] mappings...
 * @param[in] routing   Array of audio source to mixer input routing configurations.
 * @returns   Success status.
 * @retval true     All routing mappings were successfully applied.
 * @exception binder::Status EX_ILLEGAL_ARGUMENT if routing array contains invalid values.
 */
boolean setInputRouting(in InputRouting[] routing);
```

### Property-Based Design Pattern
Both `IAudioMixer` and `IAudioOutputPort` use property getters/setters:
- Properties are enum-indexed (see [Property.aidl](current/com/rdk/hal/audiomixer/Property.aidl))
- Values use shared `PropertyValue` union from `com.rdk.hal` common module
- Document access (read-only/read-write) and valid states for each property
- Example: `LATENCY_MS` is read-only, `ACTIVE_AQ_PROFILE` is read-write in READY/STARTED states

### HAL Feature Profile (HFP) Configuration
[hfp-audiomixer.yaml](current/hfp-audiomixer.yaml) defines **platform-specific capabilities**:
- Declares available mixer `resources` (secure/non-secure, input configurations)
- Lists `outputPorts` with supported properties, formats, and AQ processors
- Used by platform integrators, not typically modified during interface development
- Named inputs (main, assoc, pcm1, pcm2) correspond to mixer input indices

## Build System

### CMake Configuration
- Uses custom `compile_aidl()` function (defined at root level, not in this module)
- **Never run `cmake` directly in this directory**—always invoke from root
- Dependencies on external modules:
  - `COMMON_MODULE_PATH/${COMMON_VERSION}` for `PropertyValue.aidl`
  - `AUDIO_DECODER_MODULE_PATH/${AUDIO_DECODER_VERSION}` for `Codec.aidl`

From [CMakeLists.txt](current/CMakeLists.txt#L29-L31):
```cmake
set(AUDIO_DECODER_VERSION "current")
set(COMMON_VERSION "current")
```

### AIDL Compilation
Source files organized in `SRC` list:
1. Parcelables and enums first (dependencies)
2. Interfaces second
3. External dependencies last

Include paths point to sibling module directories for cross-module imports.

## Development Workflow

### Adding a New Interface Method
1. Update the interface file (e.g., `IAudioMixer.aidl`)
2. Add doxygen comments with `@brief`, `@param`, `@exception` tags
3. If adding new data types, update `SRC` list in CMakeLists.txt (parcelables before interfaces)
4. Ensure external dependencies (Codec, PropertyValue) are imported correctly

### Adding a New Property
1. Define enum value in [Property.aidl](current/com/rdk/hal/audiomixer/Property.aidl) or [OutputPortProperty.aidl](current/com/rdk/hal/audiomixer/OutputPortProperty.aidl)
2. Document: Type, Access (read-only/read-write), Valid states
3. If property should be platform-configurable, add to HFP YAML's `supportedProperties`

### Adding a New Enum/Parcelable
1. Create file in `com/rdk/hal/audiomixer/` with proper package declaration
2. Add `@VintfStability` annotation
3. For enums: use `@Backing(type="int")`
4. Add to CMakeLists.txt `SRC` list **before** any interfaces that use it
5. Update imports in dependent files

## Common Patterns

### Service Discovery Pattern
```aidl
// 1. Get manager singleton
IAudioMixerManager manager = IAudioMixerManager.fromBinder(...);

// 2. Enumerate mixers
IAudioMixer.Id[] ids = manager.getAudioMixerIds();

// 3. Acquire specific mixer
IAudioMixer mixer = manager.getAudioMixer(IAudioMixer.Id.MIXER_SYSTEM);
```

### Input Routing Pattern
See [IAudioMixer.aidl](current/com/rdk/hal/audiomixer/IAudioMixer.aidl#L108-L141):
- Use `InputRouting[]` array to map sources to mixer inputs
- Set `destinationInputIndex = -1` or `AudioSourceType.NONE` to disconnect
- Duplicate source/input indices in same call → error

### Nullable Return Values
Use `@nullable` for methods that may return null:
```aidl
@nullable IAudioMixer getAudioMixer(in IAudioMixer.Id id);
```
Common when resource is unavailable or not supported.

## Integration Points

### External Module Dependencies
1. **com.rdk.hal.PropertyValue** (common module): Universal property value union
2. **com.rdk.hal.audiodecoder.Codec** (audiodecoder module): Codec enum for format negotiation
3. Both resolved via `*_MODULE_PATH` CMake variables set at root level

### Cross-Component Communication
- Audio sources (decoders, HDMI input, app audio) route to mixer inputs via `setInputRouting()`
- Output ports (HDMI, SPDIF) retrieve mixed audio with format conversion/transcoding
- State transitions coordinated via `State` enum (UNINITIALIZED → READY → STARTED → STOPPED)

## Troubleshooting

### CMake Errors
- "Do not invoke module level CMake directly" → Run cmake at workspace root
- Missing external .aidl files → Check `*_MODULE_PATH` and `*_VERSION` variables

### AIDL Compilation Errors
- "Type not found" → Ensure import statements and include directories are correct
- "Parcelable forward reference" → Move parcelable definition before interface in `SRC` list

## Reference Examples
- Property-based interface: [IAudioOutputPort.aidl](current/com/rdk/hal/audiomixer/IAudioOutputPort.aidl#L36-L56)
- Enum with state validation: [Property.aidl](current/com/rdk/hal/audiomixer/Property.aidl#L42-L54) (ACTIVE_AQ_PROFILE)
- Routing validation logic: [IAudioMixer.aidl](current/com/rdk/hal/audiomixer/IAudioMixer.aidl#L108-L130) setInputRouting comments
