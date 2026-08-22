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
 * @brief     Whether a metric value is present, and if not, why not.
 * @author    Gerald Weatherup
 */

/**
 * @brief Presence of a metric value.
 *
 * A figure that is absent and a figure that measured zero are different facts,
 * and this enum is what keeps them apart. A metric value is never served as a
 * sentinel: `0` means it measured zero, and no served value ever means
 * "unimplemented".
 */
@VintfStability
@Backing(type="int")
enum MetricStatus {

    /**
     * The value is served and `MetricValue.value` is meaningful.
     */
    SUPPORTED = 0,

    /**
     * This product cannot measure this figure at all.
     *
     * A fixed property of the implementation rather than of the moment: a
     * consumer that sees this once will see it for the lifetime of the
     * resource, and may stop asking. `MetricValue.value` is undefined.
     */
    NOT_SUPPORTED = 1,

    /**
     * The figure is one this product measures, but no value can be derived at
     * this instant.
     *
     * A property of the moment rather than of the implementation — a stream PTS
     * before the first frame carries one, for example. A consumer must keep
     * asking, because a later read may succeed. `MetricValue.value` is
     * undefined.
     */
    NOT_AVAILABLE = 2,
}
