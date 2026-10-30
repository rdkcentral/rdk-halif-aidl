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
 * @brief     What caused a starvation episode.
 * @author    Gerald Weatherup
 */

/**
 * @brief What caused a starvation episode.
 *
 * Carried as a `MetricValue.value`, not as an identifier.
 */

@VintfStability
@Backing(type="long")
enum MetricUnderflowTrigger
{

    /**
     * No underflow episode has been recorded.
     */
    NONE = 0,

    /**
     * The pipeline had not yet filled at the start of presentation. Expected.
     */
    STARTUP_PREFILL = 1,

    /**
     * Starvation during steady-state playback, with no seek, trickplay or
     * content boundary to explain it. This is the one that indicates a defect.
     */
    MID_STREAM = 2,

    /**
     * The pipeline was refilling after a seek. Expected.
     */
    SEEK_RECOVERY = 3,

    /**
     * The pipeline was refilling after a trickplay rate change. Expected.
     */
    TRICKPLAY_RECOVERY = 4,

    /**
     * The stream crossed a discontinuity such as a period or advert boundary.
     * Expected.
     */
    CONTENT_BOUNDARY = 5,
}
