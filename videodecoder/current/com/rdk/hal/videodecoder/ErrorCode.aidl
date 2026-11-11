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

/**
 *  @brief     Video decoder error code definitions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type = "int")
enum ErrorCode {
    /**
     * No error. Never raised; it is the value an unset ErrorCode holds.
     */
    NONE = 0,

    /**
     * Placeholder, never raised.
     *
     * @deprecated Deprecated since 2026-11-11. Use the codes below.
     * Reason: it carried no meaning; the defined codes replace it.
     */
    xxxx = 1,

    /**
     * The stream's codec is not one the decoder supports.
     *
     * Support: mandatory.
     */
    CODEC_UNSUPPORTED = 2,

    /**
     * The stream is in a supported codec but beyond the capabilities
     * the product declares: profile, level, frame size, frame rate, bit
     * depth, or an output pixel format the decoder cannot produce.
     *
     * Support: mandatory.
     */
    CODEC_EXCEEDS_CAPABILITIES = 3,

    /**
     * Corruption was detected in the bitstream and concealed; the frame
     * was output and decoding carries on.
     *
     * Support: optional.
     */
    BITSTREAM_RECOVERED = 4,

    /**
     * Corruption was detected in the bitstream and the frames it
     * affects were dropped; decoding carries on from the next decodable
     * frame.
     *
     * Support: optional.
     */
    BITSTREAM_FRAMEDROP = 5,

    /**
     * The decoder stopped making progress: input is queued but no
     * output or error has followed within the decoder's own time limit.
     *
     * Support: optional.
     */
    DECODER_LOCK = 6,

    /**
     * The decoder failed for a reason no other code describes.
     *
     * Support: mandatory.
     */
    INTERNAL_ERROR = 7,
}
