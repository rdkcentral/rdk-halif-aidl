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
 * @brief     What describes an occurrence audiodecoder raised.
 * @author    Gerald Weatherup
 */

/**
 * @brief What describes an occurrence audiodecoder raised.
 *
 * Each member states its unit, and its kind where the occurrence measured it.
 * `MetricValue.id` carries the member's value, which is scoped to this
 * component. Values are append-only.
 */

@VintfStability
@Backing(type="long")
enum MetricEventAttribute
{

    /**
     * Unit: none. Classification of this fault, with the same values as
     * LAST_DECODE_ERROR_REASON. The value a consumer branches on.
     *
     * The value is a `MetricDecodeErrorReason`.
     */
    DECODE_ERROR_REASON = 0,

    /**
     * Unit: none. The SoC's own error code for this fault, carried through
     * uninterpreted. For vendor diagnosis, and never branched on.
     */
    DECODE_ERROR_VENDOR_CODE = 1,

    /**
     * Unit: ms. Stream PTS at detection, within one frame interval. Absent
     * where the SoC cannot derive a PTS at all, and NOT_AVAILABLE where it can
     * but could not at this instant. Never sent as -1.
     */
    DECODE_ERROR_PTS_MS = 2,
}
