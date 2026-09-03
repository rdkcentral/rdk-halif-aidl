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

import com.rdk.hal.metrics.MetricGroup;

/**
 * @brief     Every figure a read returned, latched at one instant.
 * @author    Gerald Weatherup
 */

/**
 * @brief The result of one metric read.
 *
 * The read is the snapshot. Everything in it was latched at `timestampNs`, so
 * paired figures — frames decoded against frames presented, underflow episodes
 * against their cumulative duration — can never be read torn. An implementation
 * whose figures span two hardware blocks latches both; this is an obligation on
 * the implementation rather than a property a consumer discovers.
 */
@VintfStability
parcelable MetricSnapshot {

    /**
     * When every value in this snapshot was latched, in nanoseconds.
     *
     * From a monotonic clock that cannot step, so the age of a snapshot is
     * always computable and two snapshots always order. A clock that could be
     * stepped by a time-of-day correction would make a duration derived from
     * two reads occasionally negative.
     *
     * This is the instant of sampling, not of transmission.
     */
    long timestampNs;

    /**
     * What was read, one group per element instance.
     *
     * A group is absent where the resource has nothing to report for that
     * element. A group present with an empty `values` is a different fact: the
     * element exists and served nothing at this instant.
     */
    MetricGroup[] groups;
}
