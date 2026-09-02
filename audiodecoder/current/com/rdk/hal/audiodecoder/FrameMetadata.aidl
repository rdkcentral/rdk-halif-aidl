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
package com.rdk.hal.audiodecoder;
import com.rdk.hal.audiodecoder.PCMMetadata;
import com.rdk.hal.audiodecoder.Codec;
import com.rdk.hal.AVSource;
import com.rdk.hal.audiodecoder.FrameType;

/**
 *  @brief     Audio frame metadata.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable FrameMetadata {

	/**
	 * The type of audio data output by the decoder
	 */
	FrameType type;

	/**
	 * The original source codec of the audio frame.
	 */
	Codec sourceCodec;

	/**
	 * The buffer contains Dolby Atmos audio and metadata.
	 */
	boolean isDolbyAtmos;
	
	/**
	 * Audio trim durations to apply when presenting this decoded frame.
	 *
	 * `trimStartNs` is the duration to discard from the start of the decoded
	 * audio frame; `trimEndNs` from the end. Both are durations in nanoseconds,
	 * relative to the frame's own boundaries (not absolute timestamps).
	 *
	 * Per-frame — applies only to this decoded frame, not to the stream as a
	 * whole. Set to 0 (the common case) for no trim.
	 *
	 * The AudioSink applies these durations before presenting the PCM to the
	 * mixer. Where the decoder has already trimmed the frame itself, it sets
	 * both to 0, so the samples are discarded exactly once.
	 *
	 * Used for codec priming / encoder delay (AAC LC/HE, Opus pre-skip), AAC
	 * SBR padding, and gapless playback across track boundaries.
	 *
	 * Type rationale: `int` (not `long`) — at nanosecond precision, max value
	 * is ~2.1 seconds, sufficient for any per-frame priming/padding trim.
	 *
	 * @see IAudioDecoderController.decodeBufferWithMetadata()
	 * @see InputBufferMetadata.trimStartNs
	 * @see InputBufferMetadata.trimEndNs
	 */
	int trimStartNs;
	int trimEndNs;

	/**
	 * Indicates if the audio should be delivered in low latency mode.
	 */
	boolean lowLatency;

	/**
	 * In-bitstream end-of-stream marker.
	 *
	 * Set true by the HAL on an output frame when it parses a codec-level
	 * end-of-stream marker from the audio elementary stream itself - for
	 * example, Dolby TrueHD substream termination, or any analogous
	 * end-of-sequence indicator defined by the source codec.
	 *
	 * Many common audio formats (raw PCM, MP3, AAC LC, AC-3) carry no
	 * in-stream EOS marker; for those, this flag is always false.
	 *
	 * Advisory and informational only:
	 * - It does NOT end the decode session and never triggers teardown.
	 * - It may appear more than once in a session - at a splice or
	 *   concatenation point an end-of-sequence is a sequence boundary, not
	 *   necessarily end-of-presentation.
	 * - No callback fires for it; it is surfaced purely as this flag for any
	 *   consumer that cares (e.g. splice-aware middleware).
	 *
	 * Client-signalled EOS is NOT carried here. The discrete EOS signal flows
	 * via `IAudioDecoderController.signalEndOfStream()`: the HAL drains every
	 * held frame, and then fires
	 * `IAudioDecoderControllerListener.onEndOfStream()` exactly once after the
	 * final `onFrameOutput()`.
	 *
	 * @see IAudioDecoderController.signalEndOfStream()
	 * @see IAudioDecoderControllerListener.onEndOfStream()
	 */
	boolean bitstreamEOS;

	/**
	 * Discontinuity indicator where the PTS for this frame is likely to be discontinuous to the previous.
	 */
	boolean discontinuity;

	/**
	 * The source of the audio frame.
	 * When the frame is presented the source may be used to configure the audio settings.
	 */
	AVSource source;

	/**
	 * If the frame is PCM audio data this parcelable contains the PCM metadata.
	 * Else metadata is null.
	 */
	@nullable PCMMetadata metadata;

	/**
	 * Proprietary metadata passed from Decoder HAL to Sink HAL.
	 * When the frame type is SOC_PROPRIETARY, SoCPrivate MAY contain opaque HAL metadata (indicated by non-zero length) that is used by the Audio Sink and MUST be passed to the Audio Sink.
	 */
	byte[] SoCPrivate;

	/**
	 * Private extension for future use.
	 */
	ParcelableHolder extension;
}
