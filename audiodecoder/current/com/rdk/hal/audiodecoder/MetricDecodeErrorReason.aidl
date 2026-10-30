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
package com.rdk.hal.audiodecoder;

/**
 * @brief     Why a decode fault happened.
 * @author    Gerald Weatherup
 */

/**
 * @brief Why a decode fault happened.
 *
 * Carried as a `MetricValue.value`, not as an identifier.
 */

@VintfStability
@Backing(type="long")
enum MetricDecodeErrorReason
{

    /**
     * No decode error has been recorded.
     */
    NONE = 0,

    /**
     * The coded bitstream was malformed or failed to parse.
     */
    BITSTREAM_ERROR = 1,

    /**
     * The stream is well formed but uses a tool, profile or level this decoder
     * does not implement.
     */
    UNSUPPORTED_FORMAT = 2,

    /**
     * The decoder failed internally on a stream it should have been able to
     * decode.
     */
    DECODER_FAULT = 3,

    /**
     * A resource the decode depended on was withdrawn, such as a secure buffer
     * or a hardware context reclaimed under pressure.
     */
    RESOURCE_LOST = 4,

    /**
     * The decode hardware reported a fault.
     */
    HARDWARE_FAULT = 5,
}
