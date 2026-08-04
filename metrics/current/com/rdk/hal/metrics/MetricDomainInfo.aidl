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
import com.rdk.hal.metrics.MetricElementInfo;

/**
 *  @brief     One domain and its elements.
 *
 *  A domain is the subject area and the unit of extension: adding "cpu" or
 *  "memory" alongside "av" touches nothing that already exists, and requires no
 *  interface change.
 */
@VintfStability
parcelable MetricDomainInfo
{
    /** e.g. "av", "cpu", "memory". */
    String domain;

    /**
     *  Which revision of THIS domain's field dictionary the declaration was
     *  written against. Per domain, because an A/V dictionary cannot define
     *  cpu.core.utilisation_pct.
     */
    String dictionaryVersion;

    /**
     *  True when this domain's fields are computed as a stated function of measured
     *  fields, false when they are read from an instrument.
     *
     *  A vendor never declares a derived domain and a SoC never serves one, but
     *  getCapabilities() returns the union of every profile live on the device, and the
     *  layers above the HAL are exactly the ones that declare them. Without this flag a
     *  computed figure arrives indistinguishable from a measured one, and a consumer
     *  differencing it produces a number nothing ever measured.
     */
    boolean derived;

    MetricElementInfo[] elements;
}
