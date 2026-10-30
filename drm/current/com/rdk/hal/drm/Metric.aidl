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
package com.rdk.hal.drm;

/**
 * @brief     The figures drm measures.
 * @author    Gerald Weatherup
 */

/**
 * @brief The figures drm measures.
 *
 * Each member states its unit and kind. `MetricValue.id` carries the member's
 * value, which is scoped to this component. Values are append-only.
 */

@VintfStability
@Backing(type="long")
enum Metric
{

    /**
     * Unit: operations. Kind: counter. Decrypt operations completed, summed
     * across the key sessions this media session holds. The denominator for
     * mean decrypt latency.
     */
    DECRYPT_COUNT = 0,

    /**
     * Unit: events. Kind: counter. Decrypt operations that failed on a key
     * already held. Distinct from a licence that was never obtained, which is
     * not vendor-observable and is not counted here.
     */
    DECRYPT_ERRORS = 1,

    /**
     * Unit: us. Kind: counter. Sum of decrypt operation latency. Paired with
     * DECRYPT_COUNT, so the mean decrypt latency is this divided by that.
     */
    DECRYPT_LATENCY_SUM_US = 2,
}
