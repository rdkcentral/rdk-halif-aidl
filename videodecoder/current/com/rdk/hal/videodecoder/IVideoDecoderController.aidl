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
import com.rdk.hal.videodecoder.Property;
import com.rdk.hal.videodecoder.CSDVideoFormat;
import com.rdk.hal.PropertyValue;

/** 
 *  @brief     Video Decoder Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IVideoDecoderController
{
    /**
	 * Starts the Video Decoder.
     * 
     * The Video Decoder must be in a `READY` state before it can be started.
     * If successful the Video Decoder transitions to a `STARTING` state and then a `STARTED` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::READY state.
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
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::STARTED state.
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
     * @see getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
	 * Pass an encoded buffer of video elementary stream data to the Video Decoder.
     * 
     * The Video Decoder must be in a `STARTED` state.
     * Buffers can be either non-secure or secure to support SVP.
     * Each call shall reference a single video frame with a presentation timestamp.
     * 
     * When the decoder has finished with the buffer it is automatically freed by the decoder and returned
     * to the AV Buffer Manager.
     * 
     * @param[in] nsPresentationTime	The presentation time of the video frame in nanoseconds.
     * @param[in] bufferHandle			A handle to the AV buffer containing the encoded video frame.
     * 
     * @returns true on success or false if the decode buffer is full.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE
     * @exception binder::Status EX_ILLEGAL_ARGUMENT
     * 
     * @pre Resource is in State::STARTED state.
     */
    boolean decodeBuffer(in long nsPresentationTime, in long bufferHandle);

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
     * @param[in] reset     When true, the internal Video Decoder state is fully reset back to its opened `READY` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::STARTED state.
     */
    void flush(in boolean reset);

    /**
	 * Signals a discontinuity in the video stream.
     * 
     * The Video Decoder must be in a state of `STARTED`.
     * Buffers that follow this call passed in `decodeBuffer()` shall be regarded
     * as PTS discontinuous to any video frames past or already held in the Video Decoder.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::STARTED state.
     */
	void signalDiscontinuity();

    /**
	 * Signals an end of stream condition after the last AV buffer has been passed for decode.
     * 
     * The Video Decoder must be in a state of `STARTED`.
     * Any frames held by the decoder should continue to be decoded and output.
     * 
     * No more AV buffers are expected to be delivered to the Video Decoder after
	 * `signalEOS()` has been called unless the decoder is first flushed or stopped and started again.
     * 
     * An `IVideoDecoderControllerListener.onFrameOutput()` callback with `FrameMetadata.endOfStream`
     * must be set to true after all video frames have been output.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::STARTED state.
     */
	void signalEOS();
	
    /**
     * Sends codec specific data to initialise the Video Decoder.
     * 
     * The Video Decoder must be in a state of `STARTED`.
     * 
     * Some video media requires out-of-band codec specific data to describe the video stream which
     * has been pre-filtered from the container or provided by the application.
     * When required this function must be called before video frame buffers are passed to `decodeBuffer()`.
     *
	 * For H.264/AVC this is the AVCDecoderConfigurationRecord, starting with the configuration version byte.
	 * @see ISO/IEC 14496-15:2022, 5.3.3.1.2
	 * @see https://www.iso.org/standard/83336.html
	 * 
	 * For H.265/HEVC video, this is the HEVCDecoderConfigurationRecord, starting with the configuration version byte.
     * @see ISO/IEC 23008-2
	 * @see https://www.iso.org/standard/85457.html
	 * 
     * For AV1 video, this is the AV1CodecConfigurationRecord, starting with the first configuration version byte.
     * @see https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-section
     * 
     * @param[in] csdVideoFormat        Codec specific data format enum. Must match codec specified in `open()` call.
     * @param[in] codecData             Byte array of codec data.  Must not be empty.
     * 
     * @returns boolean
     * @retval true     The codec data was successfully set.
     * @retval false    Invalid parameter or empty codec data array.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::STARTED state.
	 */
	boolean parseCodecSpecificData(in CSDVideoFormat csdVideoFormat, in byte[] codecData);
}
