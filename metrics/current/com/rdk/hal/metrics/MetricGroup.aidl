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

import com.rdk.hal.metrics.MetricValue;

/**
 * @brief     What one element instance measured.
 * @author    Gerald Weatherup
 */

/**
 * @brief The figures one element instance reports.
 *
 * The envelope is fixed so that the contents can be free. A consumer knows
 * every group is an identifier, an instance and an array, and can walk one
 * without code written for that particular element. A new figure is a new
 * member of the component's `Metric` enum rather than a new parcelable member.
 */
@VintfStability
parcelable MetricGroup {

    /**
     * Identifier of the element this group reports.
     *
     * The value of a member of the serving component's `MetricElement` enum.
     */
    long id;

    /**
     * Which instance of the element this group reports, from 0.
     *
     * A separate field because how many decoders are live is a property of the
     * moment: a second decoder exists only while a second session does.
     */
    int instance;

    /**
     * What this element measured.
     *
     * Every value here was latched at the one instant its enclosing
     * `MetricSnapshot` records.
     */
    MetricValue[] values;
}
