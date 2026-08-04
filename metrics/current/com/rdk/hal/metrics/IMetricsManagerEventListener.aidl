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
 *  @brief     Notification that the set of live sources has changed.
 *
 *  Per-session sources come and go with their sessions, so a consumer attaches
 *  at source start rather than polling getSourcePaths().
 *
 *  Only sources inside the scope this listener registered for are reported. A
 *  consumer registered on "av.video_decoder" never hears about a sink source, so it neither
 *  filters what it receives nor wakes for a domain it does not read.
 *
 *  @see IMetricsManager.registerEventListener()
 */
@VintfStability
oneway interface IMetricsManagerEventListener
{
    /**
     *  @brief A source became available.
     *  @param[in] path : e.g. "av.video_decoder.1".
     */
    void onSourceAdded(in String path);

    /**
     *  @brief A source went away. Its final values are no longer readable.
     *  @param[in] path : e.g. "av.video_decoder.1".
     */
    void onSourceRemoved(in String path);
}
