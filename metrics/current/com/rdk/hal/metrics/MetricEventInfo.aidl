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
 *  @brief     An event kind this element raises, and the payload it carries.
 *
 *  Kinds are scoped by the source that raises them, so they carry no media
 *  prefix: "underflow" from av.video_sink is a video starvation, and the same
 *  kind from av.audio_sink is an audio one.
 *
 *  A consumer reads this before it registers. An element that declares no kinds
 *  raises none, which is the difference between "this element has nothing to
 *  push" and "this product cannot push".
 */
@VintfStability
parcelable MetricEventInfo
{
    /** e.g. "underflow", "decode_error". */
    String kind;

    MetricEventFieldInfo[] fields;
}
