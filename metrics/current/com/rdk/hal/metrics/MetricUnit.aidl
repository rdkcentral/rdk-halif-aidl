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
package com.rdk.hal.metrics;

/**
 *  @brief     What a metric's number counts.
 *
 *  A closed set, and the same set the declaration schema enumerates. It is closed
 *  because a consumer that does not recognise a unit cannot interpret the value at
 *  all - it can only discard it - so a new unit is an interface change rather than a
 *  declaration change, unlike a new field, element or domain.
 */
@VintfStability
@Backing(type="int")
enum MetricUnit {

    /** Not a measured quantity - a mode, an index, a boolean-shaped 0 or 1. */
    NONE = 0,

    /** Video or audio frames. */
    FRAMES = 1,

    /** Playback episodes, e.g. rebuffering episodes. */
    EPISODES = 2,

    /** Milliseconds. */
    MS = 3,

    /** Microseconds. */
    US = 4,

    /** Nanoseconds. */
    NS = 5,

    /** Bytes. */
    BYTES = 6,

    /** Discrete occurrences. */
    EVENTS = 7,

    /** Percent, 0 to 100. */
    PERCENT = 8,

    /** Hertz. */
    HZ = 9,
}
