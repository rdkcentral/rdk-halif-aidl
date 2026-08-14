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
import com.rdk.hal.metrics.MetricEventValue;

/**
 *  @brief     One occurrence, pushed at the moment it happened.
 *
 *  Some figures cannot be carried by a read at all. A counter says how many
 *  occurrences there have been and a `last_*` field describes the newest, which
 *  is exact for rates and totals - but several occurrences inside one capture
 *  interval collapse to their newest member, and a consumer that needs each one
 *  cannot recover the others by reading more often. An event carries each
 *  occurrence individually and at the instant it happened.
 *
 *  THERE IS NO BUFFER AND NO CURSOR. This callback is the delivery: no seq, no
 *  retention, no drop-oldest accounting, and nothing per caller for a vendor to
 *  implement. The counters remain the record of how many occurred, so a consumer
 *  that missed a call has still not lost the count - it has lost that
 *  occurrence's detail, which is what the counters could never carry anyway.
 *
 *  A value the source cannot supply is OMITTED from values[], never defaulted.
 */
@VintfStability
parcelable MetricsEvent
{
    /** The source that raised it: "<domain>.<element>.<instance>". */
    String sourcePath;

    /** Declared event kind, from MetricEventInfo.kind. */
    String kind;

    /** Host wall-clock at detection, in milliseconds. */
    long tsUnixMs;

    /** The values this kind declares, by bare name. */
    MetricEventValue[] values;
}
