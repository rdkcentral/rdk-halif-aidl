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
import com.rdk.hal.metrics.MetricFieldInfo;
import com.rdk.hal.metrics.MetricKVPair;

/**
 *  @brief     One metric source — a single <domain>.<element>.<instance>.
 *
 *  The source is the read unit, so no path is passed on reads: one call is one
 *  coherent snapshot. The atomicity boundary is therefore visible in the name.
 *
 *  A name given to this interface is the BARE field name - `frames_decoded` -
 *  because the source already fixes the domain, element and instance. It is the
 *  same name `getFields()` returns, fed straight back without concatenation,
 *  and a caller cannot ask one source for another's field because there is no
 *  way to express it.
 *
 *  A name RETURNED in a value is fully qualified - `av.video_decoder.0.frames_decoded`
 *  - because a value outlives the call that produced it. In a log line, a merged
 *  set or a bug report, `frames_decoded` alone says nothing about which source
 *  produced it.
 *
 *  Every value is int64.
 */
@VintfStability
interface IMetricsSource
{
    /**
     *  @brief Field descriptors for this source.
     *
     *  The presence query. A consumer tests for a field by looking for its name
     *  here, never by assuming — a field this product cannot measure is absent
     *  rather than served as 0.
     *
     *  @returns MetricFieldInfo[] : every field this source serves.
     */
    MetricFieldInfo[] getFields();

    /**
     *  @brief Whole-source read — every declared field under ONE coherent
     *         snapshot, so paired fields (frames decoded vs presented) can
     *         never produce an impossible ratio.
     *
     *  Atomicity is an obligation on the implementation, not a property to be
     *  discovered: a source spanning two hardware blocks latches both.
     *
     *  This is the normal read for a poll loop.
     *
     *  @param[out] values : fully-qualified name/value pairs.
     *  @returns boolean : true on success.
     */
    boolean getAll(out MetricKVPair[] values);

    /**
     *  @brief Subset read — the named fields only, same single-snapshot
     *         guarantee.
     *
     *  Names are the bare field names from `getFields()`. Unknown names are
     *  omitted from the result rather than raising an error, so a newer consumer
     *  degrades cleanly on an older product.
     *
     *  @param[in]  names  : bare field names to read, e.g. "frames_decoded".
     *  @param[out] values : those that exist on this source.
     *  @returns boolean : true on success.
     */
    boolean getFieldsByName(in String[] names, out MetricKVPair[] values);

    /**
     *  @brief Single-field read. Diagnostics and one-off reads, not the poll
     *         path.
     *
     *  @param[in]  name  : bare field name, e.g. "frames_decoded".
     *  @param[out] value : single-element array receiving the value. AIDL
     *                      primitives cannot be out parameters, so a length-1
     *                      long array carries it back alongside the boolean.
     *  @returns boolean : false when the name is not served here.
     */
    boolean getField(in String name, out long[] value);

    /**
     *  @brief Write path — writable fields only: config, tunables, userspace
     *         population, and test injection.
     *
     *  @param[in] name  : bare field name, e.g. "sync_threshold_ms".
     *  @param[in] value : the value to set.
     *  @returns boolean : true on success.
     *
     *  @exception EX_UNSUPPORTED_OPERATION on a read-only field.
     *  @exception EX_ILLEGAL_ARGUMENT on an undeclared name.
     */
    boolean setField(in String name, in long value);
}
