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
import com.rdk.hal.videosink.MetricValue;

/**
 * @brief Metric values latched at one instant.
 *
 * The service latches timestampNs and every value together before it copies any
 * of them out, so figures in one snapshot are consistent with each other and a
 * rate is the difference of two snapshots divided by the difference of their
 * timestamps.
 */
@VintfStability
parcelable MetricSnapshot {
    /**
     * CLOCK_MONOTONIC_RAW time of the latch, in nanoseconds. Taken at the
     * start of the read, at the same instant as the values.
     */
    long timestampNs;

    /**
     * One entry per metric that was requested, is supported and has a value.
     * A metric the product does not support, or that has no value at this
     * instant, has no entry. The order is not specified.
     */
    MetricValue[] values;
}
