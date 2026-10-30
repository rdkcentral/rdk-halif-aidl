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
package com.rdk.hal.avclock;

/**
 * @brief     The figures avclock measures.
 * @author    Gerald Weatherup
 */

/**
 * @brief The figures avclock measures.
 *
 * Each member states its unit and kind. `MetricValue.id` carries the member's
 * value, which is scoped to this component. Values are append-only.
 */

@VintfStability
@Backing(type="long")
enum Metric
{

    /**
     * Unit: ms. Kind: current. The driver's predicted current
     * audio-versus-video presentation offset. Positive when audio leads,
     * negative when video leads. A live sample rather than a cumulative
     * figure.
     */
    SYNC_OFFSET_MS = 0,

    /**
     * Unit: ms. Kind: high_water. Largest absolute SYNC_OFFSET_MS observed. A
     * monotone non-decreasing high-water mark over the life of the resource,
     * and read-only: a maximum cannot be recovered by differencing two maxima,
     * so a consumer wanting the worst excursion within its own reporting
     * window tracks that itself from SYNC_OFFSET_MS rather than resetting a
     * figure other readers share.
     */
    SYNC_MAX_ABS_OFFSET_MS = 1,

    /**
     * Unit: ms. Kind: counter. Cumulative time the absolute SYNC_OFFSET_MS
     * exceeded SYNC_THRESHOLD_MS — the time integral of out-of-sync operation.
     */
    SYNC_TIME_OVER_THRESHOLD_MS = 2,

    /**
     * Unit: ms. Kind: config. The offset magnitude beyond which playback
     * counts as out of sync. This is the threshold SYNC_TIME_OVER_THRESHOLD_MS
     * integrates against and SYNC_MAX_ABS_OFFSET_MS is judged by, so declaring
     * either of those without this leaves both uninterpretable — reading it is
     * what the key is for. The value is set by product configuration rather
     * than over this interface, so a consumer never has to assume the
     * threshold it was built against is the one in force.
     */
    SYNC_THRESHOLD_MS = 3,

    /**
     * Unit: events. Kind: counter. Count of A/V-sync corrections the clock
     * applied, one per discrete realignment of audio and video.
     */
    RESYNC_COUNT = 4,

    /**
     * Unit: ms. Kind: counter. Sum of the absolute magnitude of each resync
     * correction. Clock-internal, and paired with RESYNC_COUNT so the mean
     * correction size is this divided by that.
     */
    RESYNC_MAGNITUDE_SUM_MS = 5,
}
