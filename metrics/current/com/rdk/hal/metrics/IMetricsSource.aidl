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
import com.rdk.hal.metrics.MetricsEvent;
import com.rdk.hal.metrics.IMetricsSourceEventListener;

/**
 *  @brief     One metric source — a single <domain>.<element>.<instance>.
 *
 *  The source is the read unit, so no path is passed on reads: one call is one
 *  coherent snapshot. The atomicity boundary is therefore visible in the name.
 *
 *  Every name returned is fully qualified. Every value is int64.
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
     *  Names are fully qualified, as everywhere else. Unknown names are omitted
     *  from the result rather than raising an error, so a newer consumer
     *  degrades cleanly on an older product.
     *
     *  @param[in]  names  : fully-qualified names to read.
     *  @param[out] values : those that exist on this source.
     *  @returns boolean : true on success.
     */
    boolean getFieldsByName(in String[] names, out MetricKVPair[] values);

    /**
     *  @brief Single-field read. Diagnostics and one-off reads, not the poll
     *         path.
     *
     *  @param[in]  name  : fully-qualified name.
     *  @param[out] value : the value.
     *  @returns boolean : false when the name is not served here.
     */
    boolean getField(in String name, out long value);

    /**
     *  @brief Write path — writable fields only: config, tunables, userspace
     *         population, and test injection.
     *
     *  @param[in] name  : fully-qualified name.
     *  @param[in] value : the value to set.
     *  @returns boolean : true on success.
     *
     *  @exception EX_UNSUPPORTED_OPERATION on a read-only field.
     *  @exception EX_ILLEGAL_ARGUMENT on an undeclared name.
     */
    boolean setField(in String name, in long value);

    /**
     *  @brief Events since the caller's last read.
     *
     *  Middleware is the only reader of this interface, so there is one cursor
     *  and the caller holds it: pass the highest seq you have seen. The HAL
     *  keeps no per-caller cursor state. Multi-consumer fan-out belongs one
     *  layer up, where consumers genuinely read at different cadences.
     *
     *  The buffer exists only to bridge one poll interval. Oldest events drop
     *  at the cap, and the overwrite is counted so a reader can tell it fell
     *  behind rather than silently seeing a gap.
     *
     *  @param[in]  sinceSeq  : return events with seq greater than this.
     *  @param[in]  maxEvents : cap on the number returned.
     *  @param[out] events    : the events, in seq order.
     *  @returns boolean : true on success.
     */
    boolean getRecentEvents(in long sinceSeq, in int maxEvents,
                            out MetricsEvent[] events);

    /**
     *  @brief Optional push, where the implementation can raise events from a
     *         schedulable context.
     *
     *  Where offered it removes poll latency on events. The buffer remains the
     *  delivery of record, because a oneway binder call cannot be made from an
     *  atomic context.
     *
     *  @param[in] listener : the listener.
     *  @returns boolean : true on success.
     */
    boolean registerEventListener(in IMetricsSourceEventListener listener);

    /**
     *  @brief Unregisters a previously registered listener.
     *
     *  @param[in] listener : the listener.
     *  @returns boolean : true on success.
     */
    boolean unregisterEventListener(in IMetricsSourceEventListener listener);
}
