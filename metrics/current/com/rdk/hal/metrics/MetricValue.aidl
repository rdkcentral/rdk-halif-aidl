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
     * Identifier of the field this value carries.
     *
     * The first 8 bytes of SHA-256 over the field's composed path together with
     * the terms that give it meaning:
     *
     *   value      "<domain>.<element>.<field>|<unit>|<kind>"
     *   attribute  "<domain>.<element>.<field>|<unit>"
     *
     * Nothing allocates an identifier and there is no registry to consult, so a
     * layer computes it rather than being told it. Two consequences follow, and
     * both are the point.
     *
     * The unit is part of the identity, so a product that declares a field in
     * microseconds and populates milliseconds yields a different identifier —
     * its consumer sees a hard mismatch rather than a figure that is quietly a
     * thousand times wrong.
     *
     * The identifier does not depend on which file declares the field, so
     * moving a declaration between modules renames nothing.
     *
     * The width is a requirement rather than a preference: a 32-bit space puts
     * a birthday collision at the tens of thousands of keys, and a collision
     * here is two measurements answering to one identifier.
     */
    long id;

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
