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
 * @brief     One occurrence a HAL reported, with what described it.
 * @author    Gerald Weatherup
 */

/**
 * @brief An occurrence pushed from a HAL to a listener.
 *
 * Some facts cannot be carried by a read. A read says what is true now, so a
 * condition that began and ended between two reads is invisible to it however
 * fast the reader polls. An event is how such an occurrence reaches a consumer.
 *
 * The envelope is the one `MetricGroup` uses, for the same reason: a consumer
 * walks an event kind it has no specific knowledge of, so a new event kind is a
 * declaration change rather than a new callback signature.
 */
@VintfStability
parcelable MetricEvent {

    /**
     * When the occurrence was detected, in nanoseconds.
     *
     * From the same monotonic clock `MetricSnapshot` uses, so an event and a
     * read order against each other. This is the instant of detection, not of
     * delivery: a consumer can therefore tell how long an event waited, and two
     * events keep their true spacing however they were dispatched.
     */
    long timestampNs;

    /**
     * Identifier of the event kind.
     *
     * SHA-256 over "<domain>.<element>.<event_kind>", truncated as
     * `MetricValue.id` is.
     */
    long eventId;

    /**
     * What locates and classifies this occurrence.
     *
     * A closed-vocabulary reason, a vendor code, a stream PTS: these say which
     * occurrence this was and where, rather than measuring anything, so they
     * carry no aggregation semantics.
     *
     * `instance` is carried here, as it is on `MetricGroup`.
     *
     * A field this product never serves is absent from this array. A field the
     * event kind declares that could not be derived at this instant is present
     * with `MetricStatus::NOT_AVAILABLE` — a distinction absence alone cannot
     * make, and the reason an event field is a `MetricValue` rather than a bare
     * pair.
     */
    MetricValue[] attributes;

    /**
     * What this occurrence measured.
     *
     * The length of the episode that just closed, the number of frames a
     * threshold crossing covered. Present where the occurrence measured
     * something; an empty array where it did not, which is normal — an
     * occurrence that is purely a fact about a moment measures nothing.
     */
    MetricValue[] values;
}
