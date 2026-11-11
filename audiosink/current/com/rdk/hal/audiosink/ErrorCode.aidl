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
package com.rdk.hal.audiosink;

/**
 *  @brief     Audio sink error code definitions.
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
    xxx = 1,

    /**
     * A queued frame could not be played.
     */
    RENDER_FAILED = 2,

    /**
     * The output in use cannot play the frame's format.
     */
    UNSUPPORTED_FORMAT = 3,

    /**
     * The output path the sink renders to has been lost.
     */
    OUTPUT_UNAVAILABLE = 4,

    /**
     * A secure audio buffer could not be processed.
     */
    SECURE_PATH_FAILURE = 5,

    /**
     * The audio output hardware failed and needs a reset.
     */
    HARDWARE_FAILURE = 6,
}
