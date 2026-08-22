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
 * @brief     What one element measured, and what dimensions it.
 * @author    Gerald Weatherup
 */

/**
 * @brief The figures one element reports, with the attributes that locate them.
 *
 * The envelope is fixed so that the contents can be free. A consumer knows
 * every group is an identifier plus two arrays and can walk one without code
 * written for that particular element — which is what lets a new figure be a
 * declaration change rather than a new parcelable member, and a new parcelable
 * member would be an interface change.
 */
@VintfStability
parcelable MetricGroup {

    /**
     * Identifier of the element this group reports.
     *
     * SHA-256 over "<domain>.<element>", truncated as `MetricValue.id` is. The
     * instance is not part of it — see `attributes`.
     */
    long id;

    /**
     * What dimensions this group.
     *
     * An attribute says which thing was measured rather than what was measured
     * of it, so it carries no aggregation semantics and its identifier composes
     * without a kind term.
     *
     * `instance` is the attribute every group carries, and the only one today.
     * It is an attribute rather than a segment of the element's name because
     * how many decoders are live is a property of the moment rather than of the
     * contract — a second decoder exists only while a second session does, and
     * an identifier that moved with it would not be stable.
     */
    MetricValue[] attributes;

    /**
     * What this element measured.
     *
     * A value carries aggregation semantics — counter, current, high_water or
     * config — and its identifier composes with that kind, so a consumer that
     * would read a gauge on a counter's cadence can be caught rather than
     * quietly producing plausible wrong numbers.
     *
     * Every value here was latched at the one instant its enclosing
     * `MetricSnapshot` records.
     */
    MetricValue[] values;
}
