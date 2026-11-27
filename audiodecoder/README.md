# Audio Decoder HAL

AIDL interface for the RDK audio decoder HAL, in
[current/com/rdk/hal/audiodecoder/](current/com/rdk/hal/audiodecoder/).

The specification is [Audio Decoder](current/docs/audio_decoder.md). End-of-stream
signalling, including a `flush()` that interrupts a pending end-of-stream, is
in its [End of Stream Signalling](current/docs/audio_decoder.md#end-of-stream-signalling)
section.
