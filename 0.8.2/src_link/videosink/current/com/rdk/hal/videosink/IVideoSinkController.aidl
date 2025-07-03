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
package com.rdk.hal.videosink;
import com.rdk.hal.videodecoder.IVideoDecoder;
import com.rdk.hal.videodecoder.FrameMetadata;
import com.rdk.hal.videosink.Property;
import com.rdk.hal.PropertyValue;

/** 
 *  @brief     Video Sink Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
interface IVideoSinkController
{
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
     * Sets the Video Decoder ID linked to this Video Sink.
     *
     * When the Video Sink is opened, the default is set to `IVideoDecoder.Id.UNDEFINED`.
     * When set to `IVideoDecoder.Id.UNDEFINED` then no Video Decoder source is set.
     *
     * @param[in] videoDecoderId		The ID of the Video Decoder source.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     *
     * @returns boolean
     * @retval true     The Video Decoder ID was set successfully.
     * @retval false    Invalid Video Decoder ID.
     *
     * @pre The resource must be in State::READY.
     *
     * @see getVideoDecoder(), IVideoDecoderManager.getVideoDecoderIds()
     */
    boolean setVideoDecoder(in IVideoDecoder.Id videoDecoderId);

    /**
     * Gets the Video Decoder ID linked to this Video Sink.
     *
     * @returns IVideoDecoder.Id which can be IVideoDecoder.Id.UNDEFINED.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::READY or State::STARTED.
     *
     * @see setVideoDecoder()
     */
    IVideoDecoder.Id getVideoDecoder();

    /**
	 * Starts the Video Sink.
     * 
     * The Video Sink must be in a READY state before it can be started.
     * If successful the Video Sink transitions to a `STARTING` state and then a `STARTED` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::READY.
     * 
     * @see stop(), IVideoSink.open()
     */
    void start();

    /**
	 * Stops the Video Sink.
     * 
     * The sink enters the `STOPPING` state and then the sink enters the `READY` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     * 
     * @see start(), IVideoSink.close()
     */
    void stop();

    /**
     * Queues a video frame for display.
     * 
     * When the presentation time occurs for the video frame the current mapped video plane is used
     * to render the video frame.
     * 
     * The presentation time of the video frame is controlled by the AV Clock
     * and will be lip synced with an Audio Sink delivered stream if linked.
     * 
     * If the call is successful the `frameBufferHandle` is owned by the vendor layer and 
     * freed after use or when flushed.
     *
     * @param[in] nsPresentationTime    The presentation time of the video frame in nanoseconds.
     * @param[in] frameBufferHandle     A handle to the video frame buffer.
     * @param[in] metadata              A FrameMetadata object with metadata relating to the video frame.
     * 
     * @returns boolean
     * @retval true     The video frame buffer was queued successfully.
     * @retval false    The video sink queue is full.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT
     * 
     * @pre The resource must be in State::STARTED.
     */
    boolean queueVideoFrame(in long nsPresentationTime, in long frameBufferHandle, in FrameMetadata metadata);
   
    /**
     * Flushes the internal queue of video frames.
     * 
     * Once the flush operation has completed the `onFlushComplete()` callback is made to the client.
     * 
     * When `holdLastFrame` is set true, the current displayed video frame is held on the display
     * until either a new video frame is presented, a new `flush()` call with `holdLastFrame` set to false is made
     * or the video sink is closed.
     *
     * @param[in] holdLastFrame         If true then the current displayed video frame is held.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     * 
     * @see discardFramesUntil(), IVideoSinkControllerListener.onFlushComplete()
     */
    void flush(in boolean holdLastFrame);

    /**
     * Sets the earliest presentation time stamp for the Video Sink to display its next frame.
     * 
     * The next video frame to display shall be >= `nsPresentationTime` after this call.
     * Any frames in tunnelled or non-tunnelled operational mode which are before this time
     * shall be freed and not displayed.
     * 
     * If there is a frame already displayed then it remains displayed until a new frame arrives.
     * The `discardFramesUntil()` function is often used to perform accurate seek operations to a specific presentation
     * time inside a video stream and called after `flush()` with `holdLastFrame` set to true.
     *
     * @param[in] nsPresentationTime    The earliest presentation time of a video frame to display.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     * 
     * @see flush()
     */
    void discardFramesUntil(in long nsPresentationTime);
}
