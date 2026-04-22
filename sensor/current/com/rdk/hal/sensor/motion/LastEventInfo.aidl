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

/**
 * @file LastEventInfo.aidl
 * @brief Diagnostic snapshot of the most recent motion sensor event.
 *
 * Returned by {@link IMotionSensorController#getLastEventInfo()}.
 * Allows debug tools to determine what happened last and when, without
 * replaying the event stream.
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.OperationalMode;

@VintfStability
parcelable LastEventInfo {
    /**
     * @brief The event type (MOTION or NO_MOTION).
     */
    OperationalMode mode;

    /**
     * @brief Wall-clock timestamp in nanoseconds when the event occurred.
     *
     * Elapsed time since the event is computed as (System.nanoTime() - timestampNs).
     */
    long timestampNs;
}
