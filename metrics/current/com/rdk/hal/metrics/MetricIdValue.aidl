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
 *  @brief     One metric value, keyed by its contract id.
 *
 *  The poll-path counterpart to MetricKVPair. Both carry the same value; they
 *  differ in what identifies it and therefore in what the pair costs and what
 *  it can be trusted to mean on its own.
 *
 *  MetricKVPair is self-describing: its fully-qualified name still means
 *  something in a log line, a merged set or a bug report, long after the call
 *  that produced it. That is worth paying for once, and it is what getAll()
 *  returns.
 *
 *  This pair is not self-describing and does not try to be. It is two int64s,
 *  fixed width, no string to marshal, for the case where the client already
 *  resolved the source's fields and is now reading the same set every 20 ms for
 *  the life of the session. Re-sending "frames_decoded" on each of those polls
 *  transmits a constant.
 *
 *  Nothing is lost by using it, because the id says more than the name does. A
 *  name matches while the meaning underneath it moves - a product declaring
 *  decode_latency_sum_us but populating milliseconds still matches by name. The
 *  id is computed over the unit and kind as well, so the same mismatch is a
 *  different id, and a client comparing against the id it resolved sees a hard
 *  mismatch rather than a figure a thousand times wrong.
 */
@VintfStability
parcelable MetricIdValue
{
    /**
     *  Contract id of the field, as returned in MetricFieldInfo.id by
     *  getFields(). Identifies the field within this source; it is not
     *  qualified by instance, because .0 and .1 are the same field on
     *  different sources.
     */
    long id;

    /** The value. int64 always, exactly as MetricKVPair carries it. */
    long value;
}
