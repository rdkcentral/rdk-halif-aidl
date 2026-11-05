/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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

import com.rdk.hal.videodecoder.CSDVideoFormat;

/**
 *  @brief     Codec-specific data (a decoder configuration record) bound to
 *             one input buffer.
 *
 *  Carried in `InputBufferMetadata.codecSpecificData`. The record takes
 *  effect from the buffer it is attached to, so a parameter-set change (for
 *  example an ABR resolution switch on length-prefixed input) applies at
 *  exactly the right access unit.
 *
 *  The record layout per format is the one defined for
 *  `IVideoDecoderController.parseCodecSpecificData()`.
 *
 *  @see InputBufferMetadata.codecSpecificData
 *  @see IVideoDecoderController.parseCodecSpecificData()
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable CodecSpecificData {
    /** Record format. MUST match the codec the decoder was opened with. */
    CSDVideoFormat format = CSDVideoFormat.AVC_DECODER_CONFIGURATION_RECORD;

    /** The record, starting with its configuration version byte. MUST NOT be empty. */
    byte[] data;
}
