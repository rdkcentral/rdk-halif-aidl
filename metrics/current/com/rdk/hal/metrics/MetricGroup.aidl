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
 *  @brief     The metric groups this interface can serve.
 *
 *  GENERATED from docs/av_field_dictionary.md by scripts/dictionary-ids.py.
 *  Do not hand-edit - add the element to the dictionary and re-run --emit-aidl.
 *
 *  A group is one <domain>.<element>. Extending the interface with a new group
 *  is an enum value appended here, which is a source-compatible change: a
 *  consumer that does not know a value skips it.
 *
 *  Each group owns a 1000-block of MetricId values, so a metric's group is
 *  `metricId / 1000` and two groups can never collide on an ordinal.
 */
@VintfStability
@Backing(type="int")
enum MetricGroup {

    /** `av.video_decoder` - MetricId values 0..999. */
    AV_VIDEO_DECODER = 0,

    /** `av.video_sink` - MetricId values 1000..1999. */
    AV_VIDEO_SINK = 1,

    /** `av.audio_decoder` - MetricId values 2000..2999. */
    AV_AUDIO_DECODER = 2,

    /** `av.audio_sink` - MetricId values 3000..3999. */
    AV_AUDIO_SINK = 3,

    /** `av.clock` - MetricId values 4000..4999. */
    AV_CLOCK = 4,

    /** `av.session` - MetricId values 5000..5999. */
    AV_SESSION = 5,

    /** `av.admission` - MetricId values 6000..6999. */
    AV_ADMISSION = 6,

    /** `health.poll` - MetricId values 7000..7999. */
    HEALTH_POLL = 7,
}