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
import com.rdk.hal.metrics.MetricsEvent;

/**
 *  @brief     Push of occurrences from a source a consumer registered on.
 *
 *  Registered per source, on IMetricsSource, because an occurrence belongs to
 *  the thing that raised it. One listener may be registered on several sources;
 *  MetricsEvent.sourcePath says which one is calling.
 *
 *  @see IMetricsSource.registerEventListener()
 */
@VintfStability
oneway interface IMetricsSourceEventListener
{
    /**
     *  @brief Called when the source raises an event.
     *
     *  oneway, so a slow listener cannot hold up the source that raised it. The
     *  listener does the least it can here and hands off.
     *
     *  @param[in] event : the occurrence, its instant and its payload.
     */
    void onMetricsEvent(in MetricsEvent event);
}
