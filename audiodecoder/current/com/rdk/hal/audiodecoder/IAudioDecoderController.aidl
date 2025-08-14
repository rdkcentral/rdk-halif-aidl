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
import com.rdk.hal.audiodecoder.CSDAudioFormat;
import com.rdk.hal.audiodecoder.Property;

import com.rdk.hal.PropertyValue;

/** 
 *  @brief     Audio Decoder Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IAudioDecoderController {

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
     * @see getProperty()
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property and propertyValue.
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);


    /**
	 * Starts the audio decoder.
     * 
     * The audio decoder must be in a ready state before it can be started.
     * If successful the audio decoder transitions to a `STARTING` state and then a `STARTED` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::READY.
     * 
     * @see open(), stop()
     */
    void start();
 
    /**
	 * Stops the audio decoder.
     * 
     * The decoder enters the `STOPPING` state and then any input data buffers that have been passed for decode but have
     * not yet been decoded are freed automatically.  This is effectively the same as a flush.
     * Once buffers are freed and the internal audio decoder state is reset, the decoder enters the `READY` state.
     *
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     * 
     * @see start()
     */
    void stop();
 
    /**
	 * Pass an encoded buffer of audio elementary stream data to the audio decoder.
     * 
     * The audio decoder must be in a `STARTED` state.
     * Buffers can be either non-secure or secure to support SAP.
     * Each call shall reference a single audio frame with a presentation timestamp.
     * 
     * @param[in] nsPresentationTime	The presentation time of the audio frame in nanoseconds.
     * @param[in] bufferHandle			A handle to the AV buffer containing the encoded audio frame.
     * @param[in] trimStartNs			The time to trim from the start of the decoded audio in nanoseconds.
     * @param[in] trimEndNs  			The time to trim from the end of the decoded audio in nanoseconds.
     *
     * @returns true on success or false if the decode buffer is full.
     * 
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE 
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT
     * 
     * @pre The resource must be in State::STARTED.
     */
    boolean decodeBuffer(in long nsPresentationTime, in long bufferHandle, in int trimStartNs, in int trimEndNs);

    /**
	 * Starts a flush operation on the decoder.
     * 
     * The audio decoder must be in a state of `STARTED`.
     * Any input data buffers that have been passed for decode but have
     * not yet been decoded are automatically freed.
     * The internal audio decoder state is optionally reset.
     *
     * @param[in] reset     When true, the internal audio decoder state is fully reset back to its opened READY state.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     */
	void flush(in boolean reset);

    /**
	 * Signals a discontinuity in the audio stream.
     * 
     * The audio decoder must be in a state of `STARTED`.
     * Buffers that follow this call passed in `decodeBuffer()` shall be regarded
     * as PTS discontinuous to any audio frames previously passed.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     */
    void signalDiscontinuity();

    /**
	 * Signals an end of stream condition in the audio stream after the last audio buffer has been delivered.
     * 
     * The audio decoder must be in a state of `STARTED`.
     * Any frames held by the decoder should continue to be decoded and output.
     * No more audio buffers are expected to be delivered to the audio decoder after
	 * `signalEOS()` has been called unless the decoder is first flushed or stopped and started again.
     * 
	 * An `IAudioDecoderControllerListener.onFrameOutput()` callback with `FrameMetadata.endOfStream` 
     * must be set to true after all audio frames have been output.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     */
	void signalEOS();

    /**
     * Sends codec-specific data to initialise the audio decoder.
     *
     * Some audio formats require out-of-band codec-specific data describing the audio stream,
     * which has been filtered from the container or provided by the application.
     * This must be invoked before any audio frame buffers are passed to `decodeBuffer()`.
     *
     * For example, MPEG-4 Audio requires the AudioSpecificConfig, beginning with the audio object type.
     * 
     * The accepted `CSDAudioFormat` values align with DVB, ISDB, HLS, and DASH broadcast/streaming standards.
     *
     * @see ISO/IEC 14496-3:2019
     * @see https://www.iso.org/standard/76383.html
     *
     * @param[in] csdAudioFormat   Codec-specific data format enum.
     * @param[in] codecData        Byte array containing the codec-specific data.
     *
     * @returns boolean
     * @retval true     The codec data was successfully set.
     * @retval false    Invalid parameter or empty codec data array.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *           Thrown if the resource is not in State::STARTED.
     *
     * @pre The decoder resource must be in State::STARTED.
     */
    boolean parseCodecSpecificData(in CSDAudioFormat csdAudioFormat, in byte[] codecData);
}