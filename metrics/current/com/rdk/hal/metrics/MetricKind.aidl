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
 *  @brief     How a metric's value behaves over time.
 *
 *  This governs the arithmetic a consumer may do, and is what keeps deltas and
 *  samples from being mixed. A closed set, and the same set the declaration schema
 *  enumerates: a consumer that misreads the kind produces a wrong number rather than
 *  no number, so an unrecognised value cannot be tolerated.
 */
@VintfStability
@Backing(type="int")
enum MetricKind {

    /** Cumulative since source creation. May be differenced. */
    COUNTER = 0,

    /** A live sample. Absolute - never sum it. */
    CURRENT = 1,

    /** Monotone maximum since source creation. Absolute. */
    HIGH_WATER = 2,

    /** A tunable's present value. Absolute. */
    CONFIG = 3,
}
