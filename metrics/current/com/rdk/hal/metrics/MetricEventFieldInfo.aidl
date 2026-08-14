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
 *  @brief     One value an event kind declares it may carry.
 *
 *  Only a unit is declared. The counter/current/high_water/config
 *  classification says how a figure behaves over time, which is meaningless for
 *  the payload of a single occurrence - there is no series to difference.
 *
 *  Declaring the payload per kind is what makes a new kind cheap: a SoC that can
 *  distinguish a failure mode its peers cannot declares the kind and its values,
 *  consumers that do not know it ignore it, and no parcelable is widened to hold
 *  a value only one kind uses.
 */
@VintfStability
parcelable MetricEventFieldInfo
{
    /** Bare payload name, e.g. "duration_ms". */
    String name;

    /** The unit its value carries, e.g. "ms". */
    String unit;
}
