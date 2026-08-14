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
import com.rdk.hal.metrics.Capabilities;
import com.rdk.hal.metrics.IMetricsSource;

/**
 *  @brief     Service entry point for com.rdk.hal.metrics.
 *
 *  Carries named numeric values from whoever measures them to whoever consumes
 *  them, organised into DOMAINS. This interface serves the "av" domain: the
 *  playback-quality figures a streaming partner certifies against.
 *
 *  A domain is the unit of extension - a later one is added without touching
 *  "av" or this interface - which is why the naming is domain-qualified rather
 *  than assuming its subject.
 *
 *  Naming — every metric name is four segments, fully qualified, no short form:
 *
 *      <domain>.<element>.<instance>.<field>
 *
 *      av.video_decoder.0.frames_decoded
 *      av.video_sink.1.frames_dropped_late
 *      av.clock.0.sync_offset_ms
 *      av.audio_sink.0.underflowed
 *
 *  The first three segments address a source; the fourth selects a field within
 *  it. The path IS the identity — there is no source-id parcelable, because
 *  modelling it a second time only creates a way for the two to disagree.
 *
 *  Names are by subject, not by producer. Which block sources a figure differs
 *  per SoC, and for some fields it is middleware rather than the SoC at all, so
 *  a producer-shaped name would move between products for the same metric.
 *  There is no SoC-private namespace: a figure only one SoC can produce still
 *  gets one dictionary entry, so no consumer ever grows per-SoC code.
 */
@VintfStability
interface IMetricsManager
{
    /** @brief Service name to publish this HAL as. */
    const @utf8InCpp String serviceName = "MetricsManager";

    /**
     *  @brief The catalog — every domain, element and field this product
     *         serves.
     *
     *  Read once. A consumer matches the names it understands, keeps them, and
     *  ignores the rest. The catalog is built from the declaration at startup
     *  and stands for the life of the service, so one read is all it takes.
     *
     *  @returns Capabilities : the runtime truth, built from the declaration.
     */
    Capabilities getCapabilities();

    /**
     *  @brief Every source path this platform serves, e.g. "av.video_decoder.0".
     *
     *  STATIC PER PLATFORM. A source is a hardware resource the vendor always
     *  has - idle is not absent - so the set is fixed for the life of the
     *  service, and a consumer enumerates once and holds the result. This is the
     *  only statement of how many of an element exist; the catalog describes an
     *  element once, as a type.
     *
     *  A source that is idle serves its fields like any other; its counters
     *  simply do not advance.
     *
     *  @returns String[] : every source path this platform serves.
     */
    String[] getSourcePaths();

    /**
     *  @brief Access to one source.
     *
     *  A path this platform serves always resolves, whether or not the resource
     *  is currently in use.
     *
     *  @param[in] path : "<domain>.<element>.<instance>", from getSourcePaths().
     *  @returns IMetricsSource : the source, or null if this platform declares
     *                            no such source.
     *
     *  @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if `path` is
     *             not three segments. A well-formed path that this platform does
     *             not serve returns null; a path that is not a path at all is an
     *             error in the caller.
     */
    @nullable IMetricsSource getSource(in String path);
}
