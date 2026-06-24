# Audio Decoder HAL

AIDL interface for the RDK audio decoder HAL. This document covers the
end-of-stream (EOS) lifecycle. See the `.aidl` files under
[current/com/rdk/hal/audiodecoder/](current/com/rdk/hal/audiodecoder/) for the full interface.

## EOS model: single metadata-carrying path

EOS rides entirely on the framework metadata parcelables on both sides of
the interface. No separate signal methods, no dedicated listener callbacks.

| Side | Signal |
|---|---|
| **Input** | `InputBufferMetadata.endOfStream = true` on the final call to `IAudioDecoderController.decodeBufferWithMetadata()` |
| **Output** | `FrameMetadata.endOfStream = true` on the final `IAudioDecoderControllerListener.onFrameOutput()` callback |

Audio EOS is always application-driven. No supported audio elementary
stream (MP3, AAC, AC-3 / E-AC-3, Opus, Vorbis) carries an in-bitstream EOS
marker.

`bufferHandle` MUST always reference a valid encoded frame. EOS is carried
on the final real data buffer - there is no EOS-only marker form, no path
to signal EOS without data, and no post-buffer signal method.

If the client has no further data to send, it ends the session via
`stop()` (or `flush(reset=true)` if the decoder is to be reused). If you
haven't got data, don't signal EOS, just shut down the pipeline.

## Output-side contract (tunnelled-mode EOS resolution)

EOS rides on the FINAL `onFrameOutput()` callback of the decode session by `metadata.endOfStream = true`. There is no separate EOS-only marker callback after the last frame.

When `metadata.endOfStream = true`:

- This is the final `onFrameOutput()` callback of the session — fires exactly once per session.
- In non-tunnelled mode the callback delivers the last decoded audio frame with valid `frameAVBufferHandle` and `FrameMetadata`.
- In tunnelled mode the callback is delivered with `frameAVBufferHandle = -1` as is normal for tunnelled output.
- `metadata` is GUARANTEED non-null, because `endOfStream` transitioning from false to true is itself a metadata change. Clients can rely on `metadata != null && metadata.endOfStream` for unambiguous EOS detection — including in tunnelled mode.
- The other fields of `FrameMetadata` describe the final frame as normal.

This resolves the tunnelled-mode ambiguity raised in [discussion #380](https://github.com/rdkcentral/rdk-halif-aidl/discussions/380). With EOS being just-another-metadata-field on the final `onFrameOutput()` (rather than a separate EOS-only callback with undefined fields), there is no ambiguity about what the other metadata fields mean — they describe the frame being delivered.

After this callback the decoder remains in `State::STARTED` but is drained.
No further `onFrameOutput()` is delivered until `flush()` or `stop()` + `start()`.

## EOS lifecycle

1. Client submits buffers via `decodeBufferWithMetadata()`.
2. Application sets `InputBufferMetadata.endOfStream = true` on the final
   `decodeBufferWithMetadata()` call.
3. HAL decodes the final buffer and drains any held frames. In non-tunnelled
   mode these are delivered via `onFrameOutput()`; in tunnelled mode they
   are consumed internally by the vendor layer.
4. HAL delivers the final `onFrameOutput()` with `FrameMetadata.endOfStream = true`.
5. Decoder remains in `State::STARTED` but is drained.

A decode session is the interval from `start()` to the next `stop()` or
`flush(reset=true)`. A `flush(reset=false)` drops buffered input and any
pending EOS callback but does not end the session.

## Use cases

### UC-1: App-driven EOS

App sets `InputBufferMetadata.endOfStream = true` on the final
`decodeBufferWithMetadata()` call. HAL drains and delivers the final
`onFrameOutput()` with `FrameMetadata.endOfStream = true`.

### UC-2: Client has no more data and wants to end the session

Call `stop()` (or `flush(reset=true)` if the decoder is to be reused).
There is no EOS signalling in this case - the final
`onFrameOutput(..., endOfStream = true)` callback is not produced unless
an EOS-carrying input buffer was decoded. This is the sole shutdown path
when no final data exists.

### UC-3: EOS interrupted by `flush()` or `stop()`

Any pending EOS callback is discarded along with any undelivered frames.
A new EOS callback can be delivered only after a subsequent EOS signal.

### UC-4: Restart without flush after EOS

Calling `decodeBufferWithMetadata()` after the EOS callback has been
delivered returns `EX_ILLEGAL_STATE`. The application must call
`flush(reset=true)` or `stop()` + `start()` first.

### UC-5: Multiple EOS attempts

Setting `endOfStream = true` twice in a session is caught at the state
machine: the second `decodeBufferWithMetadata()` call returns
`EX_ILLEGAL_STATE` because the session has already terminated.

## Codec applicability for in-bitstream EOS

| Codec | In-bitstream EOS |
|---|---|
| MP3 | ❌ |
| AAC (LC, HE, HEv2, xHE-AAC) | ❌ |
| AC-3 / E-AC-3 | ❌ |
| Opus | ❌ |
| Vorbis | ❌ |
| AC-4 | ❌ |
| PCM | ❌ |

None of the audio codecs supported by this HAL carry an in-bitstream EOS
marker at the elementary-stream level. Container/transport-level EOS is
the responsibility of the demultiplexer / media pipeline, not the HAL.
Audio EOS is therefore always driven by
`decodeBufferWithMetadata(..., endOfStream = true)` on the final buffer.
