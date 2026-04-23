# Video Decoder HAL

AIDL interface for the RDK video decoder HAL. This document covers the
end-of-stream (EOS) lifecycle. See the `.aidl` files under
[current/com/rdk/hal/videodecoder/](current/com/rdk/hal/videodecoder/) for the full interface.

## EOS model: single metadata-carrying path

EOS rides entirely on the framework metadata parcelables on both sides of
the interface. No separate signal methods, no dedicated listener callbacks.

| Side | Signal |
|---|---|
| **Input** | `InputBufferMetadata.endOfStream = true` on the final call to `IVideoDecoderController.decodeBufferWithMetadata()` |
| **Output** | `FrameMetadata.endOfStream = true` on the final `IVideoDecoderControllerListener.onFrameOutput()` callback |

`bufferHandle` MUST always reference a valid encoded frame. EOS is carried
on the final real data buffer - there is no EOS-only marker form, no path
to signal EOS without data, and no post-buffer signal method.

If the client has no further data to send, it ends the session via
`stop()` (or `flush(reset=true)` if the decoder is to be reused). If you
haven't got data, don't signal EOS, just shut down the pipeline.

## Output-side contract

When `FrameMetadata.endOfStream = true` on an `onFrameOutput()` callback:

- The HAL is signalling EOS on this callback.
- The callback is ordered strictly after any prior decoded-frame callbacks.
- The HAL fires this **exactly once** per decode session.
- **Only** `endOfStream` is authoritative. All other fields of `FrameMetadata`
  (including `codedWidth`, `pixelFormat`, `colorimetry`, etc.) are
  **undefined** on such a callback and MUST be ignored by the client.
- The enclosing `frameAVBufferHandle` is likewise irrelevant for EOS
  detection.

This resolves the #380 vendor divergence at spec level: the EOS callback
is unambiguously identifiable by `endOfStream = true` alone, regardless of
tunnelling mode or the state of other metadata fields.

After this callback the decoder remains in `State::STARTED` but is drained.
No further `onFrameOutput()` is delivered until `flush()` or `stop()` + `start()`.

## EOS lifecycle

1. Client submits buffers via `decodeBufferWithMetadata()`.
2. EOS is signalled via one of:
   - an in-bitstream marker (codec-dependent, see table below); or
   - setting `InputBufferMetadata.endOfStream = true` on the final
     `decodeBufferWithMetadata()` call.
3. HAL decodes the final buffer and drains any held frames, delivering them
   via `onFrameOutput()`.
4. HAL delivers the final `onFrameOutput()` with `FrameMetadata.endOfStream = true`.
5. Decoder remains in `State::STARTED` but is drained.

A decode session is the interval from `start()` to the next `stop()` or
`flush(reset=true)`. A `flush(reset=false)` drops buffered input and any
pending EOS callback but does not end the session.

## Use cases

### UC-1: In-bitstream EOS (MPEG-2 / H.264 / H.265 / MPEG-4 Part 2)

The HAL detects the in-bitstream EOS marker, drains, and delivers the final
`onFrameOutput()` with `FrameMetadata.endOfStream = true`. The app need not
carry `endOfStream = true` on the input - but if it does, the two EOS
sources collapse to a single event.

### UC-2: App-driven EOS (VP9 / AV1 / any)

App sets `InputBufferMetadata.endOfStream = true` on the final
`decodeBufferWithMetadata()` call. HAL drains and delivers the final
`onFrameOutput()` with `FrameMetadata.endOfStream = true`.

### UC-3: Client has no more data and wants to end the session

Call `stop()` (or `flush(reset=true)` if the decoder is to be reused).
There is no EOS signalling in this case - the final
`onFrameOutput(..., endOfStream = true)` callback is not produced unless
an EOS-carrying input buffer was decoded. This is the sole shutdown path
when no final data exists.

### UC-4: EOS interrupted by `flush()` or `stop()`

Any pending EOS callback is discarded along with any undelivered frames.
A new EOS callback can be delivered only after a subsequent EOS signal.

### UC-5: Restart without flush after EOS

Calling `decodeBufferWithMetadata()` after the EOS callback has been
delivered returns `EX_ILLEGAL_STATE`. The application must call
`flush(reset=true)` or `stop()` + `start()` first.

### UC-6: Multiple EOS attempts

Setting `endOfStream = true` twice in a session is caught at the state
machine: the second `decodeBufferWithMetadata()` call returns
`EX_ILLEGAL_STATE` because the session has already terminated.

## Codec applicability for in-bitstream EOS

The HAL is responsible for detecting in-bitstream EOS markers on codecs
that carry them and absorbing them into the signalling lifecycle above.
Container/transport-level EOS is not the HAL's responsibility - that
belongs to the demultiplexer / media pipeline.

| Codec | In-bitstream EOS | Mechanism |
|---|---|---|
| MPEG-1 / MPEG-2 | ✅ | `sequence_end_code` (0x000001B7) |
| MPEG-4 Part 2 | ✅ | `visual_object_sequence_end_code` |
| H.264 / AVC | ✅ | `end_of_stream_rbsp` NAL (type 11), `end_of_sequence_rbsp` NAL (type 10) |
| H.265 / HEVC | ✅ | `end_of_bitstream_rbsp` NAL (type 37), `end_of_seq_rbsp` NAL (type 36) |
| VP9 | ❌ | Container / transport-level only |
| AV1 | ❌ | Container / transport-level only |

For codecs marked ❌, EOS is always application-driven via
`decodeBufferWithMetadata(..., endOfStream = true)` on the final buffer.
