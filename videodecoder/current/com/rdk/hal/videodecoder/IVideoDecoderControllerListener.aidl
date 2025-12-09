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
	 * 
	 * The userData is extracted from SEI (Supplemental Enhancement Information) messages 
	 * in the video bitstream as defined by ITU-T H.264 (AVC) and ITU-T H.265 (HEVC) standards.
	 * 
	 * SEI User Data Structure:
	 * The userData byte array contains the complete SEI user_data_unregistered() payload 
	 * with the following structure:
	 * 
	 * For H.264/AVC (ITU-T H.264 Annex D.1.6):
	 * +-----------------------+------------------+
	 * | uuid_iso_iec_11578    | 16 bytes (UUID)  |
	 * +-----------------------+------------------+
	 * | user_data_payload_byte| variable length  |
	 * +-----------------------+------------------+
	 * 
	 * For H.265/HEVC (ITU-T H.265 Annex D.2.6):
	 * +-----------------------+------------------+
	 * | uuid_iso_iec_11578    | 16 bytes (UUID)  |
	 * +-----------------------+------------------+
	 * | user_data_payload_byte| variable length  |
	 * +-----------------------+------------------+
	 * 
	 * The uuid_iso_iec_11578 is a 16-byte (128-bit) UUID that identifies the 
	 * syntax and semantics of the user_data_payload_byte data. Common UUIDs include
	 * those for closed captions (CEA-608/CEA-708), AFD (Active Format Description),
	 * and bar data.
	 * 
	 * The output video frame can be delivered before or after the onUserDataOutput().
	 * The user data must be delivered in the same frame presentation order as the output frames.
     *
     * @param[in] nsPresentationTime	The presentation time.
     * @param[in] userData				Array of bytes containing the complete SEI user data payload
     *                                  including the 16-byte UUID and user data payload bytes.
     */
    void onUserDataOutput(in long nsPresentationTime, in byte[] userData);
 
}
