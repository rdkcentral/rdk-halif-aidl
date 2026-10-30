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
package com.rdk.hal.videosink;

/**
 * @brief     What describes an occurrence videosink raised.
 * @author    Gerald Weatherup
 */

/**
 * @brief What describes an occurrence videosink raised.
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
     * Unit: none. What caused this episode, which is what distinguishes an
     * expected starvation from a defect.
     *
     * The value is a `MetricUnderflowTrigger`.
     */
    UNDERFLOW_TRIGGER = 0,

    /**
     * Unit: ms. PTS of the frame that reached presentation. Absent where the
     * SoC cannot derive a PTS.
     */
    FIRST_FRAME_PRESENTED_PTS_MS = 1,

    /**
     * Unit: none. Which counter crossed its threshold.
     *
     * The value is a `MetricQualityFigure`.
     */
    QUALITY_THRESHOLD_CROSSED_METRIC = 2,

    /**
     * Unit: ms. Stream PTS at the crossing. Absent where no PTS is derivable.
     */
    QUALITY_THRESHOLD_CROSSED_PTS_MS = 3,

    /**
     * Unit: ms. Kind: current. Length of the episode this closes, from start
     * to resume. Not cumulative — UNDERFLOW_DURATION_MS carries the running
     * total.
     */
    UNDERFLOW_END_DURATION_MS = 4,

    /**
     * Unit: frames. Kind: current. How many frames the crossing covered.
     */
    QUALITY_THRESHOLD_CROSSED_COUNT = 5,
}
