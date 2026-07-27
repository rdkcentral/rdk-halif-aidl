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
 *  @brief     Everything this product serves — the runtime truth a consumer
 *             reads once and matches its own names against.
 *
 *  The schema travels with the interface (the ethtool -S string-table
 *  principle): a consumer reads the catalog, keeps the names it understands and
 *  ignores the rest, so a product can add fields, add an element or add a whole
 *  domain with no consumer change.
 *
 *  The metric set is therefore NOT part of the ABI. Adding a metric is a
 *  declaration change — no interface freeze, no version bump, no coordinated
 *  consumer rebuild — which is what lets the metric set track the partner
 *  certification set, which moves every year, without the HAL moving with it.
 */
@VintfStability
parcelable Capabilities
{
    /**
     *  Opaque identity of this product's declared set. Stable while the
     *  declaration is unchanged, different the moment anything in it changes.
     *  A consumer cache-keys its resolved name map on this rather than diffing
     *  field lists, and a bug report needs only this value to pin exactly what
     *  the device was serving.
     */
    String schemaId;

    MetricDomainInfo[] domains;
}
