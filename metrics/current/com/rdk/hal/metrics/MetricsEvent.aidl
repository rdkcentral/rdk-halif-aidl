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
import com.rdk.hal.metrics.MetricKVPair;

/**
 *  @brief     One event on a source's event buffer.
 *
 *  When it happened, what kind it was, and its declared values. Nothing else is
 *  fixed, because nothing else is universal: only two kinds carry a duration,
 *  only some carry a PTS, only quality events carry a count. seq and tsUnixMs
 *  are properties of the buffer rather than of any metric, and kind selects
 *  which values the catalog says will be present.
 *
 *  A value the source cannot supply is OMITTED, never defaulted. A PTS that
 *  cannot be derived is absent from values[], not sent as -1 — "no PTS
 *  available for this drop" and "the PTS is minus one" are different facts.
 */
@VintfStability
parcelable MetricsEvent
{
    /** Monotonic per source, from 1. The cursor key. */
    long seq;

    /** Host wall-clock at detection. */
    long tsUnixMs;

    /** Declared event kind, scoped by the source that raised it. */
    String kind;

    /** The values this kind declares. Names are fully qualified. */
    MetricKVPair[] values;
}
