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
 * @brief     The figures audiodecoder measures.
 * @author    Gerald Weatherup
 */

/**
 * @brief The figures audiodecoder measures.
 *
 * Each member states its unit and kind. `MetricValue.id` carries the member's
 * value, which is scoped to this component. Values are append-only.
 */

@VintfStability
@Backing(type="long")
enum Metric
{

    /**
     * Unit: frames. Kind: counter. Audio access units decoded and emitted at
     * the decoder output, one per emitted access unit. Counted from instance
     * creation and never reset on flush or seek.
     */
    FRAMES_DECODED = 0,

    /**
     * Unit: frames. Kind: counter. Audio frames discarded before output,
     * whether through an xrun or because they were undecodable.
     * Decoder-internal, and excluded from FRAMES_DECODED.
     */
    FRAMES_DROPPED = 1,

    /**
     * Unit: events. Kind: counter. Audio decode-error occurrences. A distinct
     * axis from FRAMES_DROPPED, exactly as on the video decoder: an error need
     * not drop a frame, and a drop need not be an error.
     */
    DECODE_ERRORS = 2,

    /**
     * Unit: us. Kind: counter. Running sum of per-frame audio decode latency,
     * from the access unit being queued at the input to the frame being
     * emitted at the output. Paired with FRAMES_DECODED.
     */
    DECODE_LATENCY_SUM_US = 3,

    /**
     * Unit: ms. Kind: current. Stream PTS at detection of the most recent
     * audio decode error, within one frame interval. Read with DECODE_ERRORS.
     * Left undeclared where no PTS is derivable, and never served as -1.
     */
    LAST_DECODE_ERROR_PTS_MS = 4,

    /**
     * Unit: none. Kind: current. Classification of the most recent audio
     * decode error. This is the value a consumer branches on, and what makes
     * the fault comparable across SoCs.
     *
     * The value is a `MetricDecodeErrorReason`.
     */
    LAST_DECODE_ERROR_REASON = 5,

    /**
     * Unit: none. Kind: current. The SoC's own code for the same fault,
     * carried through uninterpreted. For vendor diagnosis, and never branched
     * on.
     */
    LAST_DECODE_ERROR_VENDOR_CODE = 6,
}
