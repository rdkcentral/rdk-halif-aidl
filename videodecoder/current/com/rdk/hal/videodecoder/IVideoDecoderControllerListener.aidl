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
import com.rdk.hal.videodecoder.FrameMetadata;

/** 
 *  @brief     Controller callbacks listener interface from video decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
oneway interface IVideoDecoderControllerListener {
 
    /**
	 * Callback when a full video frame has been decoded or the frame metadata needs to be notified.
     * The metadata must be non-null on the first frame after start() or flush() call or
     * when the metadata changes in the stream. 
     * It can only be null if the contents have not changed since the last callback.
     *
     * @param[in] nsPresentationTime	The presentation time or -1 if only metadata is being returned.
     * @param[in] frameBufferHandle		Handle to 2D frame buffer or -1 if no handle is delivered in tunnelled mode.
     * @param[in] metadata				A FrameMetadata parcelable of metadata related to the frame.
     */
    void onFrameOutput(in long nsPresentationTime, in long frameBufferHandle, in @nullable FrameMetadata metadata);

    /**
    * Callback which delivers the picture user data from a frame.
    * The userData byte array starts from (and includes) the user_identifier field (typically 'GA94').
    * The output video frame can be delivered before or after the onUserDataOutput().
    * The user data must be delivered in the same frame presentation order as the output frames.
    *
    * The userData byte array contains SEI NAL data, typically conforming to the "user_data_registered_itu_t_t35" structure, used for captioning:
    * - Begins with the ITU-T T.35 country_code (0xB5 for USA)
    * - Followed by provider_code (0x0031 for ATSC)
    * - Includes a user_identifier string (usually 'GA94')
    * - Contains a user_data_type_code (0x03 for CEA-608/708)
    * - Followed by one or more CC data packets (cc_valid, cc_type, and data bytes)
    *
    * The RDK media pipeline must parse this data to extract embedded CEA-608 or CEA-708 caption packets.
    * Each `onUserDataOutput()` call corresponds to a single decoded video frame and maintains AV sync for captions.
    * This approach standardises the delivery of caption-related data across all platforms supporting embedded SEI in compressed video streams.
    *
    * @param[in] nsPresentationTime  The presentation time.
    * @param[in] userData            Array of bytes containing the SEI user data (e.g., ATSC A/72 caption payload).
    */
    void onUserDataOutput(in long nsPresentationTime, in byte[] userData);
    }
