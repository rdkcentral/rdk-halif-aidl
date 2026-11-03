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

import com.rdk.hal.metrics.MetricStatus;

/**
 * @brief     One identified metric value.
 * @author    Gerald Weatherup
 */

/**
 * @brief A single identified value, as carried by a read or by an event.
 *
 * The same type serves both, so a consumer extracts a field from a
 * `MetricEvent` exactly as it extracts one from a `MetricSnapshot`.
 */
@VintfStability
parcelable MetricValue {

    /**
     * Identifier of the field this value carries, scoped by its element.
     *
     * The `id` the producing component's Key Value Contract declares for the
     * field: a member of its generated `Metric` enum for a value, or of its
     * `MetricEventAttribute` enum for an event field or attribute. It is unique
     * only within the element that `MetricGroup.id` or `MetricEvent.groupId`
     * names, so a consumer that flattens values out of their group carries the
     * pair.
     *
     * A field's name, unit and kind are its identity. Once frozen, an id never
     * changes any of them: a field served in a new unit takes a new id, so a
     * consumer built against the old one is answered `NOT_SUPPORTED` rather
     * than handed a figure a thousand times wrong.
     *
     * In `attributes`, id `MetricGroup.ATTRIBUTE_INSTANCE` is the instance.
     */
    int id;

    /**
     * The value, signed 64-bit.
     *
     * Meaningful only when `status` is `MetricStatus::SUPPORTED`; undefined
     * otherwise, and in particular never a sentinel standing in for absence.
     *
     * Counters use the positive range. A field is signed because some figures
     * genuinely are: `av.clock.sync_offset_ms` is positive when audio leads and
     * negative when video leads, and a type that cannot go negative cannot
     * express one of those directions.
     */
    long value;

    /**
     * Whether `value` is meaningful, and if not, why not.
     */
    MetricStatus status;
}
