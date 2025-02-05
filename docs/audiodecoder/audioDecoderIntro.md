# Audio Decoder Overview

## Overview

The Audio Decoder HAL service provides the interfaces for compressed audio to be passed to the vendor layer for decoding.  It may be passed secure buffers if it indicates support for secure audio processing.

The output of an audio decoder can take 2 routes; non-tunnelled it comes back to the RDK media pipeline as a PCM audio frame buffer with metadata or tunnelled through the vendor layer directly to the mixer.

The choice of whether audio is tunnelled or non-tunnelled has no impact on the operational mode of the video decoder.  It is possible to have tunnelled video and non-tunnelled audio.

The audio decoder can choose whether to operate in tunnelled or non-tunnelled mode when it is opened for a specific codec and does not need to always use the same mode.

PCM audio does not need decoding and therefore never passes into an audio decoder, but is routed to the [Audio Sink](../audiosink/intro.md) for mixing.

The RDK Middleware GStreamer pipeline contains an RDK Audio Decoder element designed specifically to work with the Audio Decoder HAL interface.