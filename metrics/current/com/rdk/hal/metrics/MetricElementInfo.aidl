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
 *  An element is declared once, as a type. Its instances are not counted here:
 *  IMetricsManager.getSourcePaths() names every one of them, and a count stated
 *  a second time is a count that can disagree with the list.
 */
@VintfStability
parcelable MetricElementInfo
{
    /** e.g. "video_decoder", "video_sink", "clock". */
    String element;

    MetricFieldInfo[] fields;

    /**
     *  The longest interval, in milliseconds, that this element's values may go
     *  without being refreshed. A MAXIMUM, not a rate to capture at.
     *
     *  It is a freshness guarantee: a read returns values sampled no longer than this
     *  ago. 20 means the values are refreshed at least every 20 ms. The platform
     *  ceiling is 50 ms; an element may guarantee tighter, never looser.
     *
     *  It bounds what is worth reading, not what is allowed. Reads are never
     *  rate-limited and never rejected for arriving too often - a consumer capturing
     *  faster than this simply reads the same values again, because nothing has
     *  refreshed them in between. A consumer differencing counters at a shorter
     *  interval than this is dividing by an interval no measurement covered.
     *
     *  Always populated. A declaration that omits it is declaring the 50 ms ceiling,
     *  and the value carried here is 50 - a consumer reads the guarantee in force
     *  rather than inferring a default that is stated elsewhere.
     */
    int captureCadenceMs;
}
