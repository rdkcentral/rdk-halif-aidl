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
 * @brief An audio gap has started: the sink is outputting silence because the
 * audio due was missing or late. Adds one to Metric::GAP_EPISODES.
 */
@VintfStability
parcelable GapStartedEvent {
    /**
     * CLOCK_MONOTONIC_RAW time, in nanoseconds, at which the service detected
     * the event.
     */
    long timestampNs;

    /**
     * Presentation time, in nanoseconds, of the first frame that was due and
     * missing, or -1 where it is not known.
     */
    long presentationTimeNs;
}
