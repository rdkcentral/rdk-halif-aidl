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

/**
 *  @brief     One element of a domain, and everything it serves.
 *
 *  An element is declared once, as a type — instances are not enumerated here.
 *  How many the hardware supports is 'instances'; which of them are live comes
 *  from IMetricsManager.getSourcePaths(), because the live set is dynamic (a
 *  picture-in-picture decoder exists only while the second session does).
 */
@VintfStability
parcelable MetricElementInfo
{
    /** e.g. "video_decoder", "video_sink", "clock". */
    String element;

    MetricFieldInfo[] fields;

    /**
     *  How many of this element the hardware SUPPORTS — the ceiling, not the
     *  live count. Declaring it lets capability be checked before the product
     *  boots, and lets a test assert that no source index >= instances ever
     *  appears. It must agree with the owning HAL's own feature profile.
     */
    int instances;

    /**
     *  The cadence this element is polled at. May be tighter than the 50 ms
     *  platform floor; never looser — freshness is a partner-facing promise.
     */
    int pollCadenceMs;
}
