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
import com.rdk.hal.metrics.IMetricsManagerEventListener;

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
     *  @brief The live source paths, e.g. "av.video_decoder.0".
     *
     *  The LIVE set, which is dynamic. How many of an element can exist is
     *  declared as MetricElementInfo.instances; which exist right now is this.
     *
     *  @returns String[] : live source paths.
     */
    String[] getSourcePaths();

    /**
     *  @brief Access to one source.
     *
     *  @param[in] path : "<domain>.<element>.<instance>", from getSourcePaths().
     *  @returns IMetricsSource : the source, or null if the path is not live.
     */
    @nullable IMetricsSource getSource(in String path);

    /**
     *  @brief Registers for source appear/disappear notification within a scope.
     *
     *  `pathPrefix` selects how much of the device a consumer hears about, named
     *  the same way the sources themselves are:
     *
     *      ""                      every source on the device
     *      "av"                    one domain
     *      "av.video_decoder"      one element, every instance of it
     *      "av.video_decoder.0"    one source
     *
     *  A consumer that reads everything registers on "av". One that only drives
     *  the decode path registers on "av.video_decoder" and is not woken for the
     *  sink or the clock.
     *
     *  MATCHING IS BY WHOLE SEGMENT, not by string prefix: "av.video" selects
     *  nothing, because no element is named "video". A string prefix would
     *  silently capture "av.video_decoder" and "av.video_sink" together, and a
     *  consumer would receive sources it did not ask for.
     *
     *  A listener may register more than once with different prefixes. The
     *  registrations are independent, and a source matching two of them is
     *  reported once per matching registration.
     *
     *  The prefix must name a domain or element the product declares, so a typo
     *  fails here rather than leaving a registration that is silently never
     *  called. It need not have a live source yet - the live set is dynamic, and
     *  registering before one exists is the point.
     *
     *  @param[in] pathPrefix : the scope to listen within; "" for the whole device.
     *  @param[in] listener   : the listener.
     *  @returns boolean : true on success, false if this listener is already
     *                     registered for this prefix.
     *
     *  @exception EX_ILLEGAL_ARGUMENT if `pathPrefix` names no declared domain or
     *             element.
     *  @exception EX_NULL_POINTER if `listener` is null.
     */
    boolean registerEventListener(in String pathPrefix,
                                  in IMetricsManagerEventListener listener);

    /**
     *  @brief Unregisters one previously registered scope.
     *
     *  Removes the registration made with this exact `pathPrefix`, leaving any
     *  other registration the same listener holds in place.
     *
     *  @param[in] pathPrefix : the prefix the listener was registered with.
     *  @param[in] listener   : the listener.
     *  @returns boolean : true on success, false if no such registration exists.
     *
     *  @exception EX_NULL_POINTER if `listener` is null.
     */
    boolean unregisterEventListener(in String pathPrefix,
                                    in IMetricsManagerEventListener listener);
}
