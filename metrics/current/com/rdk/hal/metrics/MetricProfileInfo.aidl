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
import com.rdk.hal.metrics.MetricDomainInfo;

/**
 *  @brief     One layer's declaration, as that layer declared it.
 *
 *  A profile is what a single layer owes. The HAL layer keeps one, and a layer above
 *  the HAL keeps its own in its own repository; getCapabilities() returns them all.
 *  They are returned as separate profiles rather than one flattened domain list
 *  because each carries its own versions, and a consumer that cannot tell which
 *  declaration a domain came from cannot tell which shape it is parsing.
 *
 *  A layer never declares another layer's fields, which is what keeps "who owes this
 *  figure" answerable from the profile it appears in.
 */
@VintfStability
parcelable MetricProfileInfo
{
    /** The metrics HAL interface version this profile was written against. */
    String interfaceVersion;

    /**
     *  Which revision of the declaration schema this profile's shape follows.
     *
     *  Every profile in the union has the same shape, which is what lets them compose
     *  without translation. This states which shape, so a consumer knows what it is
     *  parsing rather than inferring it from what happens to be present.
     */
    String schemaVersion;

    MetricDomainInfo[] domains;
}
