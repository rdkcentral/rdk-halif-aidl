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
package com.rdk.hal.audiosink;

/**
 * @brief     What describes an occurrence audiosink raised.
 * @author    Gerald Weatherup
 */

/**
 * @brief What describes an occurrence audiosink raised.
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
     * Unit: ms. Kind: current. Length of the episode this closes, from start
     * to resume. Not cumulative — UNDERFLOW_DURATION_MS carries the running
     * total.
     */
    UNDERFLOW_END_DURATION_MS = 1,

    /**
     * Unit: ms. Kind: current. Silence already elapsed at the crossing, which
     * is SILENCE_THRESHOLD_MS within one detection interval. Present so a
     * consumer need not assume the threshold it was configured with is the one
     * in force.
     */
    SILENCE_ELAPSED_MS = 2,

    /**
     * Unit: ms. Kind: current. Length of the whole period this closes, from
     * the onset of silence rather than from the crossing. Not cumulative —
     * SILENCE_DURATION_MS carries the running total.
     */
    SILENCE_END_DURATION_MS = 3,
}
