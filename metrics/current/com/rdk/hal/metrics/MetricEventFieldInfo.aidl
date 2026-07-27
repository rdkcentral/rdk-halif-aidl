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
 *  @brief     One value carried by an event kind.
 *
 *  The name is bare — "duration_ms", "pts_ms" — because the source says which
 *  element raised the event and the kind says what happened. Prefixing it
 *  would say the same thing twice.
 *
 *  Only a unit is declared. The counter/current/high_water/config
 *  classification describes how a figure behaves over time, which is
 *  meaningless for the payload of a single occurrence.
 */
@VintfStability
parcelable MetricEventFieldInfo
{
    String name;
    String unit;
}
