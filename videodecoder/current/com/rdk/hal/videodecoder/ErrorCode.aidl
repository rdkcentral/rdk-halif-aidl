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
     * Placeholder, never raised.
     *
     * @deprecated Deprecated since 2026-11-11. Use the codes below.
     * Reason: it carried no meaning; the defined codes replace it.
     */
    xxxx = 1,

    /**
     * The input bitstream could not be parsed or decoded: a syntax
     * error or corrupt data.
     */
    MALFORMED_STREAM = 2,

    /**
     * The stream uses a profile, level, frame size, bit depth or
     * feature beyond the capabilities the product declares.
     */
    UNSUPPORTED_STREAM = 3,

    /**
     * The decoded frames cannot be output in a supported pixel format.
     */
    UNSUPPORTED_OUTPUT_FORMAT = 4,

    /**
     * Memory or decoder hardware needed to continue is not available,
     * for example after a resolution increase.
     */
    INSUFFICIENT_RESOURCE = 5,

    /**
     * Encrypted input could not be decrypted: the key is not loaded,
     * or the output protection required is not met.
     */
    DECRYPT_FAILED = 6,

    /**
     * The decoder hardware failed and needs a reset.
     */
    HARDWARE_FAILURE = 7,
}
