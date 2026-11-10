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
package com.rdk.hal.audiodecoder.metrics;

import com.rdk.hal.audiodecoder.metrics.Episode;
import com.rdk.hal.audiodecoder.metrics.MetricSnapshot;

/**
 * @brief The episode reported by the matching EpisodeStarted has ended.
 * Carried by onEpisodeResolved().
 */
@VintfStability
parcelable EpisodeResolved {
    /**
     * Which episode this is.
     */
    Episode id;

    /**
     * CLOCK_MONOTONIC_RAW time, in nanoseconds, at which the service detected
     * the end of the episode.
     */
    long timestampNs;

    /**
     * Presentation time, in nanoseconds, of the frame concerned, as defined on
     * the Episode member, or -1 where the frame carried none.
     */
    long presentationTimeNs;

    /**
     * Length of the episode in nanoseconds, measured on CLOCK_MONOTONIC_RAW as
     * defined on the Episode member.
     */
    long durationNs;

    /**
     * Occurrences in the episode, as defined on the Episode member.
     */
    long count;

    /**
     * Every metric the product supports, latched at timestampNs: the values
     * getMetrics() with an empty array would have returned at that instant, so
     * the event needs no second read.
     */
    MetricSnapshot metrics;
}
