# Video Decoder Overview

The **Video Decoder HAL** service provides interfaces for passing compressed video to the vendor layer for decoding. If the service supports secure audio processing, it may also handle secure buffers.

The output of the video decoder can follow two paths:

- **Non-tunnelled mode** – The decoded video is returned to the RDK media pipeline as a video frame buffer along with metadata.
- **Tunnelled mode** – The decoded video is passed directly through the vendor layer.

The choice between tunnelled and non-tunnelled video does not affect the operational mode of the audio decoder. It is possible to have tunnelled video while using non-tunnelled audio.

The video decoder's operational mode can be selected by the client upon initialization.

The **RDK middleware GStreamer pipeline** includes a dedicated **RDK Video Decoder** element, specifically designed to integrate with the **Video Decoder HAL** interface.

