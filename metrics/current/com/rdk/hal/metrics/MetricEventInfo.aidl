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
import com.rdk.hal.metrics.MetricEventFieldInfo;

/**
 *  @brief     An event kind and the values it carries.
 *
 *  Kinds are scoped by the source that raises them, so they carry no media
 *  prefix: "underflow" from av.video_sink is a video starvation, and the same
 *  kind from av.audio_sink is an audio one.
 *
 *  Declaring the values per kind is what makes a new kind free — a SoC that can
 *  distinguish a new failure mode declares the kind and its values, consumers
 *  that do not know it ignore it, and no parcelable is widened to hold a field
 *  only one kind uses.
 */
@VintfStability
parcelable MetricEventInfo
{
    /** e.g. "underflow", "underflow_end", "decode_error". */
    String kind;

    MetricEventFieldInfo[] fields;
}
