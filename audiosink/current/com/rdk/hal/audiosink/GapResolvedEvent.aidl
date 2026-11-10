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
 * @brief The audio gap reported by the matching GapStartedEvent has ended:
 * audio is playing again.
 */
@VintfStability
parcelable GapResolvedEvent {
    /**
     * CLOCK_MONOTONIC_RAW time, in nanoseconds, at which the service detected
     * the event.
     */
    long timestampNs;

    /**
     * Presentation time, in nanoseconds, of the frame that ended the episode,
     * or -1 where it is not known.
     */
    long presentationTimeNs;

    /**
     * Length of the episode in nanoseconds, measured on CLOCK_MONOTONIC_RAW
     * from the matching started event to this one.
     */
    long durationNs;

    /**
     * Frame periods of silence in the gap; the amount this gap added to
     * Metric::GAP_FRAMES.
     */
    long frameCount;
}
