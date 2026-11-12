/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.videodecoder;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.videodecoder.CSDVideoFormat;
import com.rdk.hal.videodecoder.Colorimetry;
import com.rdk.hal.videodecoder.ContentLightLevel;
import com.rdk.hal.videodecoder.InputBufferMetadata;
import com.rdk.hal.videodecoder.MasteringDisplayInfo;
import com.rdk.hal.videodecoder.Property;
import com.rdk.hal.videodecoder.VideoDecoderStreamConfig;

/**
 *  @brief     Video Decoder Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */

@VintfStability
interface IVideoDecoderController {
    /**
     * Starts the Video Decoder.
     *
     * The Video Decoder must be in a `READY` state before it can be started.
     * If successful the Video Decoder transitions to a `STARTING` state and then a `STARTED` state.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::READY.
     *
     * @see IVideoDecoder.open(), IVideoDecoder.stop()
     */
    void start();

    /**
     * Stops the Video Decoder.
     *
     * The decoder enters the `STOPPING` state and then any input data buffers that have been passed for decode but have
     * not yet been decoded are automatically freed.  This is effectively the same as a flush.
     * Once buffers are freed and the internal Video Decoder state is reset, the decoder enters the `READY` state.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see start()
     */
    void stop();

    /**
     * Sets a property.
     *
     * @param[in] property              The key of a property from the Property enum.
     * @param[in] propertyValue         Holds the value to set.
     *
     * @returns boolean
     * @retval true     The property was successfully set.
     * @retval false    Invalid property key or value.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     *
     * @see getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
     * Pass an encoded buffer of video elementary stream data to the Video Decoder
     * with per-buffer metadata.
     *
     * The Video Decoder must be in a `STARTED` state.
     * Buffers can be either non-secure or secure to support SVP (Secure Video Path).
     * Each call shall reference a single video frame with a presentation timestamp
     * carried in `metadata.nsPresentationTime`. Exception: for H.264/H.265 input
     * configured with `Alignment.NAL` (`VideoDecoderStreamConfig.bitstreamFormat`,
     * since 0.3.1.0), each call references one complete NAL unit, and every NAL unit
     * of an access unit carries that access unit's presentation timestamp.
     *
     * Buffer Ownership: Ownership of the buffer transfers to the Video Decoder HAL
     * only when this call accepts the buffer (returns true). Once accepted, the HAL
     * is responsible for freeing the buffer after processing. The caller must not
     * modify or access the buffer after a successful call. If the call returns false
     * or throws an exception, ownership remains with the caller.
     *
     * `bufferHandle` MUST reference a valid encoded frame (with `Alignment.NAL`, a
     * valid NAL unit, which may be a non-picture NAL unit). This method only
     * submits data - it carries no end-of-stream signal. A client that has
     * submitted its final buffer ends the decode session out-of-band via
     * `signalEndOfStream()`, which drains the decoder.
     *
     * Throws `binder::Status::Exception::EX_ILLEGAL_STATE` if called after
     * `signalEndOfStream()` has been invoked on this session. This applies in
     * both tunnel and non-tunnel modes - the decoder input path is not
     * tunnelled.
     *
     * `metadata.nsPresentationTime` describes this call only; the HAL MUST NOT
     * carry it across calls. The override fields and `codecSpecificData` apply
     * from this buffer onward and persist as defined in `InputBufferMetadata`.
     *
     * A PTS discontinuity is signalled by calling `signalDiscontinuity()`
     * before the first buffer that follows the discontinuity.
     *
     * @param[in] bufferHandle  A handle to the AV buffer containing the encoded
     *                          video frame. MUST be a valid handle.
     * @param[in] metadata      Per-buffer metadata. See `InputBufferMetadata`.
     *
     * @returns boolean
     * @retval true   Buffer successfully queued for decoding. Buffer ownership transfers to HAL.
     * @retval false  Internal decode buffer queue is full. Buffer ownership remains with caller.
     *                The client SHOULD wait for `IVideoDecoderControllerListener.onDecodeBufferAvailable()`
     *                before retrying, to avoid wasted binder transactions. Continuing to call this
     *                method while the queue is full is permitted but will return `false` repeatedly
     *                until space is available.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if `bufferHandle` is
     *            invalid.
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see InputBufferMetadata
     * @see signalDiscontinuity()
     * @see IVideoDecoderControllerListener.onFrameOutput()
     */
    boolean decodeBufferWithMetadata(in long bufferHandle, in InputBufferMetadata metadata);

    /**
     * Starts a flush operation on the decoder.
     *
     * The Video Decoder must be in a `STARTED` state.
     * Any input data buffers that have been passed for decode but have
     * not yet been decoded are automatically freed.
     *
     * Any pending decoded video frames due for callback are returned to the video frame buffer pool.
     * The internal Video Decoder state is optionally reset.
     *
     * On completion the decoder transitions from `FLUSHING` to `STARTED` when
     * reset=false, and accepts input straight away. When reset=true it
     * transitions to `READY`, and `start()` is required before further input.
     *
     * <b>Flush during a pending end-of-stream:</b> if `flush()` is called after
     * `signalEndOfStream()` has been invoked but before
     * `IVideoDecoderControllerListener.onEndOfStream()` has fired, the flush
     * proceeds normally - input buffers not yet decoded are freed and the held
     * reorder/DPB tail is discarded rather than drained, so none of those
     * frames are emitted via `onFrameOutput()`. The requested end-of-stream is
     * still honoured: the HAL fires `onEndOfStream()` exactly once after the
     * flush completes, whichever state the flush ends in.
     * The flush completes first: the decoder has entered `STARTED` or `READY`
     * and sent the `onStateChanged()` that ends `FLUSHING` before it sends
     * `onEndOfStream()`. The two callbacks are on separate listeners, so a
     * client must not rely on receiving them in that order; the state is
     * settled by the time the EOS is sent.
     *
     * @param[in] reset - When true, the internal Video Decoder state is fully reset and the decoder
     *                    ends in `State::READY`. When false, it ends in `State::STARTED`.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see signalEndOfStream(), IVideoDecoderControllerListener.onEndOfStream()
     */
    void flush(in boolean reset);

    /**
     * Signals a discontinuity in the video stream.
     *
     * This is the sole PTS discontinuity signal on the input side. The client
     * calls it between the last buffer before the discontinuity and the first
     * buffer after it: buffers passed to `decodeBufferWithMetadata()` after
     * this call returns are PTS discontinuous with every buffer passed before
     * it and with every frame already held in the Video Decoder.
     *
     * The decoder MUST reset its PTS tracking and interpolation state before
     * decoding the first buffer passed after this call, and MUST NOT
     * interpolate timestamps across the discontinuity. Buffers passed before
     * this call, and frames already held in the Video Decoder, are decoded
     * and output as normal.
     *
     * The first frame output from buffers passed after this call carries
     * `FrameMetadata.discontinuity = true`.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see FrameMetadata.discontinuity
     */
    void signalDiscontinuity();

    /**
     * Signals client-driven end-of-stream and drains the decoder.
     *
     * This is the discrete, authoritative "I will submit no further buffers"
     * signal. It is the only end-of-stream path on the input side - there is
     * no per-buffer EOS flag. It serves the after-the-fact case where the
     * client discovers end-of-stream only after its final buffer was already
     * submitted (async demux, network EOF, pipelined I/O).
     *
     * On this call the HAL MUST decode and emit every held frame in
     * presentation order via `IVideoDecoderControllerListener.onFrameOutput()`
     * (each with its `FrameMetadata`, plus `onUserDataOutput()` for captions),
     * and then fire `IVideoDecoderControllerListener.onEndOfStream()` exactly
     * once after the final frame. No held frame may be dropped on EOS.
     *
     * This is distinct from `stop()` and `flush()`, which abruptly discard the
     * decoder's reorder/DPB tail rather than draining it.
     *
     * A second call is a no-op. After this call any `decodeBufferWithMetadata()`
     * throws `EX_ILLEGAL_STATE`. The decoder remains in `STARTED` (drained)
     * until `flush(false)`, or `flush(true)` or `stop()` followed by `start()`. If `flush()` arrives after this
     * call but before `onEndOfStream()` has fired, the held frames are
     * discarded rather than drained, but the requested end-of-stream is still
     * honoured - `onEndOfStream()` fires once after the flush completes; see
     * `flush()`.
     *
     * Behaviour is identical in tunnel and non-tunnel modes - the MW calls this
     * method the same way. In tunnel mode the decoder->sink data flow is
     * vendor-internal; the vendor must implement the EOS signal propagation
     * from decoder to sink so the sink can fire
     * `onEndOfStream(nsPresentationTime)` with the correct presentation
     * timing. The MW observes the same sequencing in both modes:
     * `decoder.onEndOfStream()` (decode complete) followed by
     * `sink.onEndOfStream(nsPresentationTime)` (presentation complete).
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the resource
     *            is not in State::STARTED, or if no buffers have ever been
     *            submitted on this session (no stream has started).
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see IVideoDecoderControllerListener.onEndOfStream()
     */
    void signalEndOfStream();

    /**
     * Sends codec specific data to initialise the Video Decoder.
     *
     * This function sends codec-specific data to the Video Decoder for initialisation.
     * The Video Decoder must be in the `STARTED` state before calling this function.
     *
     * Some video media requires out-of-band codec-specific data to describe the video stream.
     * This data is pre-filtered from the container or provided by the application. When
     * required, this function must be called before video frame buffers are passed to
     * `decodeBufferWithMetadata()`.
     *
     * Since 0.3.1.0, the new codec-specific data applies from the next buffer
     * submitted to `decodeBufferWithMetadata()` after this call returns; on an older
     * server, a call made after buffers are queued takes effect at a vendor-specific
     * point. To bind a record to a
     * specific buffer instead, a client talking to a 0.3.1.0 or later server attaches
     * it to that buffer's `InputBufferMetadata.codecSpecificData`.
     *
     * The record supplies parameter sets and, for length-prefixed input, the NAL
     * length size. It does not select the input layout; that is
     * `VideoDecoderStreamConfig.bitstreamFormat`.
     *
     * The format of the `codecData` parameter depends on the `csdVideoFormat`:
     *
     * For `AVC_DECODER_CONFIGURATION_RECORD` (H.264/AVC), this is the
     * `AVCDecoderConfigurationRecord`, starting with the configuration version byte.
     * See ISO/IEC 14496-15:2022, 5.3.3.1.2 and
     * https://www.iso.org/standard/83336.html for more details.
     *
     * For `HEVC_DECODER_CONFIGURATION_RECORD` (H.265/HEVC), this is the
     * `HEVCDecoderConfigurationRecord`, starting with the configuration version byte.
     * See ISO/IEC 23008-2 and https://www.iso.org/standard/85457.html for
     * further information.
     *
     * For `AV1_DECODER_CONFIGURATION_RECORD` (AV1 video), this is the
     * `AV1CodecConfigurationRecord`, starting with the first configuration version byte.
     * See https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-section
     * for more details.
     *
     * @param[in] csdVideoFormat The codec specific data format. This must match the codec specified in the `open()`
     * call.
     * @param[in] codecData      The byte array of codec data. This must not be empty.
     *
     * @returns boolean
     * @retval true  The codec data was successfully set.
     * @retval false Invalid parameter or empty codec data array.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the resource is not in the `STARTED` state.
     *
     *
     * @pre The resource must be in the `STARTED` state.
     */
    boolean parseCodecSpecificData(in CSDVideoFormat csdVideoFormat, in byte[] codecData);

    /**
     * Atomically applies a batch of container/manifest-derived
     * stream-configuration hints in a single binder transaction. This is
     * the canonical surface for setting all `VideoDecoderStreamConfig`
     * fields — there are no individual typed setters; every field is
     * configured through this call.
     *
     * <h4>Atomicity</h4>
     * Either every non-null field is applied or none are. If any field fails
     * validation, the call returns `EX_ILLEGAL_ARGUMENT` and the decoder
     * state is unchanged from before the call.
     *
     * <h4>Hint precedence and persistence</h4>
     * Bitstream-derived metadata wins over the hint when present; the hint
     * is the fallback used only when the bitstream is silent. The values the
     * decoder actually used are reported via `FrameMetadata`. Hints persist
     * across `flush()` and are cleared on `close()`.
     *
     * <h4>Per-field application</h4>
     * Each non-null field is applied to the decoder's stream-config state:
     * - `resolution`           — pre-allocation seed for frame buffers
     * - `frameRate`            — pipeline timing seed
     * - `pixelAspectRatio`     — PAR fallback when bitstream VUI omits it
     * - `colorimetry`          — colour primaries / matrix fallback
     * - `masteringDisplayInfo` — SMPTE ST 2086 fallback (HEVC SEI type 137)
     * - `contentLightLevel`    — CTA-861.3 MaxCLL/MaxFALL fallback (SEI 144)
     * - `dolbyVisionLayerFlags`— BL/EL presence; only meaningful for DOLBY_VISION
     * - `bitstreamFormat`      — H.264/H.265 input layout; binding configuration,
     *                            not a hint (since 0.3.1.0)
     *
     * @param[in] config  Stream-configuration batch. Fields set to `null`
     *                    are ignored (no change). Fields with values are
     *                    applied as hints; see `VideoDecoderStreamConfig`
     *                    for per-field validation rules.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the resource is not in the READY state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if any field fails validation
     *            (e.g. `resolution.width <= 0`, `frameRate.denominator == 0`
     *            while `numerator != 0`, exactly one of `pixelAspectRatio.numerator` /
     *            `denominator` is 0, or `bitstreamFormat` not listed in
     *            `CodecCapabilities.supportedBitstreamFormats` for the open codec).
     *
     * @pre The resource must be in State::READY.
     *
     * @see VideoDecoderStreamConfig, FrameMetadata
     */
    void setStreamConfig(in VideoDecoderStreamConfig config);
}
