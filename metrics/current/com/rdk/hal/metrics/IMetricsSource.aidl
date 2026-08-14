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
import com.rdk.hal.metrics.MetricIdValue;
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
     *  This is the normal read for a capture loop.
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
     *  @brief Single-field read. Diagnostics and one-off reads, not the capture
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
     *         population, test injection, and zeroing a high-water mark.
     *
     *  A writable high_water field accepts 0 and nothing else. Counters are made
     *  window-relative by differencing, but a maximum over a window is not the
     *  difference of two maxima, so the reader zeros the mark where its own
     *  reporting window begins. There is one reader, so the zero point is not
     *  contended.
     *
     *  @param[in] name  : bare field name, e.g. "sync_threshold_ms".
     *  @param[in] value : the value to set.
     *  @returns boolean : true on success.
     *
     *  @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION on a
     *             read-only field.
     *  @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT on an
     *             undeclared name, or a non-zero write to a high_water field.
     */
    boolean setField(in String name, in long value);

    /**
     *  @brief Subset read by contract id — the capture path, same single-snapshot
     *         guarantee as getAll() and getFieldsByName().
     *
     *  Identical in meaning to getFieldsByName(); only the key differs. A capture
     *  loop reads the same field set every cadence for the life of a source, and
     *  the names of that set never change, so the string form re-marshals a
     *  constant on every read - in the request, and again in every pair returned.
     *  This form carries two int64s per value and no string at all.
     *
     *  Ids come from getFields(), which a client already calls once to resolve
     *  the source. Passing an id this source does not serve omits it from the
     *  result rather than raising an error, exactly as an unknown name is
     *  omitted, so a newer consumer degrades cleanly on an older product.
     *
     *  Prefer getAll() where the values outlive the call - a diagnostic dump, a
     *  bug report, anything merged across sources - because MetricKVPair carries
     *  the fully-qualified name and this does not.
     *
     *  @param[in]  ids    : contract ids to read, from MetricFieldInfo.id.
     *  @param[out] values : those this source serves, id and value.
     *  @returns boolean : true on success.
     */
    boolean getFieldsById(in long[] ids, out MetricIdValue[] values);

    /**
     *  @brief Write by contract id. Same meaning as setField(); only the key
     *         differs.
     *
     *  The id form matters more here than on the read path, and not for the same
     *  reason. A read keyed by id saves marshalling a constant string; a WRITE
     *  keyed by id is a correctness check. A name goes on matching while the
     *  meaning under it moves - a product declaring `sync_threshold_ms` but
     *  populating microseconds still matches by name - and a write that lands on
     *  a field whose unit or kind is not what the caller believed sets the wrong
     *  value rather than merely reporting one. Because the id hashes the path,
     *  unit and kind, that mismatch fails the write instead.
     *
     *  It also lets a client that resolved ids once hold nothing else. Without
     *  this, a caller keeps its name map alive purely to write.
     *
     *  @param[in] id    : contract id, from MetricFieldInfo.id.
     *  @param[in] value : the value to set.
     *  @returns boolean : true on success.
     *
     *  @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION on a
     *             read-only field.
     *  @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT on an id this
     *             source does not serve, or a non-zero write to a high_water
     *             field.
     */
    boolean setFieldById(in long id, in long value);
}
