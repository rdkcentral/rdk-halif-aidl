# Audio Decoder Overview

This document provides an overview of the Audio Decoder Hardware Abstraction Layer (HAL) service, which facilitates the decoding of compressed audio streams within the device. The HAL defines the interfaces through which the RDK (Reference Design Kit) middleware interacts with the vendor-specific audio decoding implementation.

## Functionality

The Audio Decoder HAL service accepts compressed audio data as input. This data can be provided in secure buffers if the underlying vendor implementation supports secure audio processing. This is crucial for premium content protection.

The decoded audio output can be delivered via two distinct paths:

- **Non-Tunnelled Mode:** In this mode, the decoded audio, typically in Pulse Code Modulation (PCM) format, is returned to the RDK media pipeline as a frame buffer along with associated metadata (e.g., sample rate, bit depth, number of channels). This allows for further processing within the RDK middleware, such as volume control, audio effects, or synchronization with other media streams.

- **Tunnelled Mode:** In this mode, the decoded audio is passed directly to the audio mixer through the vendor layer. This bypasses the RDK media pipeline for audio processing. Tunnelled mode is often preferred for performance reasons, especially in resource-constrained devices, as it reduces latency and CPU overhead. It's often used when the audio stream is simple, and the RDK post-processing isn't required.

## Operational Modes

The choice between tunnelled and non-tunnelled mode is made on a per-codec basis during the initialization of the audio decoder. This flexibility allows the system to optimize performance for different audio formats. It's important to note that the audio decoder can switch between these modes for different codec instances, but a single codec instance must operate in one mode or the other for the duration of its use. The operational mode of the audio decoder is independent of the video decoder's mode. This means that it is perfectly valid to have tunnelled video and non-tunnelled audio, or vice-versa.

## PCM Handling

Uncompressed PCM audio streams do not require decoding. Therefore, they bypass the Audio Decoder HAL entirely. Instead, they are routed directly to the [Audio Sink](../audio_sink/audio_sink_overview.md) service for mixing and playback. This is an important distinction to make for clarity.

## RDK Integration

The RDK Middleware leverages a GStreamer element specifically designed to interface with the Audio Decoder HAL. This element handles the communication with the HAL, manages the codec instances, and ensures proper synchronization with other media components within the pipeline. Specifying the GStreamer element is important for developers working with the RDK.

## Further Considerations

- **Codec Support:** The Audio Decoder HAL supports a range of audio codecs/  Refer to the [Codec Support](audio_decoder_codec_support.md) document for a complete and up-to-date list.

- **Error Handling:** The HAL implements robust error handling mechanisms to manage issues such as invalid audio data or unsupported codecs.  For detailed information on error reporting and recovery procedures, see the [Error Handling](audio_decoder_error_handling.md) documentation.

- **Security:**  Secure audio processing is a critical feature for protecting premium content.  The [Security Considerations](audio_decoder_security.md) document provides a comprehensive overview of the security mechanisms implemented in the Audio Decoder HAL, including key management and content protection strategies.

- **Performance Metrics:**  Performance is a key consideration in embedded systems.  The [Performance Metrics](audio_decoder_performance.md) document provides detailed information on typical latency and CPU utilization for different codecs and operational modes, enabling developers to optimize their applications.
