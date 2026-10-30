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
 * @brief     The occurrences videosink raises.
 * @author    Gerald Weatherup
 */

/**
 * @brief The occurrences videosink raises.
 *
 * `MetricEvent.eventId` carries one of these, scoped to this component. An occurrence is pushed because
 * a read cannot carry it: a condition that began and ended between two reads
 * is invisible to a reader however fast it polls.
 */

@VintfStability
@Backing(type="long")
enum MetricEventKind
{

    /**
     * Raised at the START of a starvation episode, the instant there is
     * nothing to present at render time. Exactly one UNDERFLOW_END closes it.
     */
    UNDERFLOW = 0,

    /**
     * Raised when presentation resumes, closing the episode the preceding
     * underflow opened.
     */
    UNDERFLOW_END = 1,

    /**
     * Raised when the first frame reaches presentation, once at session start
     * and again after each seek or flush.
     */
    FIRST_FRAME_PRESENTED = 2,

    /**
     * Raised when a quality counter crosses its declared threshold. Only the
     * sink knows whether it shed a frame or repeated one, so which counter
     * moved is carried rather than inferred.
     */
    QUALITY_THRESHOLD_CROSSED = 3,
}
