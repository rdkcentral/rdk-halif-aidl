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
	 * Audio trimming to use on presentation.
	 */
	int trimStartNs;
	int trimEndNs;

	/**
	 * Indicates if the audio should be delivered in low latency mode.
	 */
	boolean lowLatency;

	/**
	 * End-of-stream marker delivered to the client on the FINAL
	 * `IAudioDecoderControllerListener.onFrameOutput()` callback of the
	 * decode session.
	 *
	 * When true, this is the final `onFrameOutput()` callback of the session.
	 * The HAL delivers it exactly once per session. There is no separate
	 * EOS-only marker callback - `endOfStream = true` rides on the metadata
	 * of the last real decoded frame in non-tunnelled mode, or on the final
	 * tunnelled-mode metadata callback in tunnelled mode (where
	 * `frameAVBufferHandle = -1` is the normal case).
	 *
	 * The HAL MUST deliver a non-null `FrameMetadata` on the EOS callback so
	 * clients can reliably detect EOS via `metadata.endOfStream` even in
	 * tunnelled mode. This follows from the existing "metadata is non-null
	 * when it changes" rule - `endOfStream` transitioning from false to true
	 * is a metadata change. The other fields of this parcelable describe
	 * the final frame as normal.
	 *
	 * Audio EOS is always application-driven. No supported audio elementary
	 * stream (MP3, AAC, AC-3/E-AC-3, Opus, Vorbis) carries an in-bitstream
	 * EOS marker, so EOS originates only from the client submitting a final
	 * buffer via `IAudioDecoderController.decodeBufferWithMetadata()` with
	 * `InputBufferMetadata.endOfStream = true`.
	 *
	 * After this callback the decoder remains in `State::STARTED` but is
	 * drained. No further `onFrameOutput()` is delivered until `flush()` or
	 * `stop()` + `start()`.
	 *
	 * @see IAudioDecoderController.decodeBufferWithMetadata()
	 * @see InputBufferMetadata.endOfStream
	 */
	boolean endOfStream;

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
