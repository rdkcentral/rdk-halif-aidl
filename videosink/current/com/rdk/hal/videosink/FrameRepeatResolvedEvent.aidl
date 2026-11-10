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
 * @brief The freeze reported by the matching FrameRepeatStartedEvent has ended:
 * a new frame has been presented.
 */
@VintfStability
parcelable FrameRepeatResolvedEvent {
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
     * Repeated frames in the episode; the amount this episode added to
     * Metric::FRAMES_REPEATED.
     */
    long frameCount;
}
