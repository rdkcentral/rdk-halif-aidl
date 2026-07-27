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
 *  @brief     One metric value, keyed by its fully-qualified name.
 *
 *  The name is the whole four-segment path — "av.video_decoder.0.frames_decoded",
 *  never a bare field name. A bare name is ambiguous the moment it leaves the
 *  call that produced it: frames_decoded from av.video_decoder.0 and from
 *  av.audio_decoder.0 are the same string, so a consumer merging two sources
 *  would collide, and a captured payload in a log would mean nothing.
 *
 *  Every value is int64. A metric is a count, a duration in ms or us, a byte
 *  figure or an offset, and all of those are signed 64-bit. Counters use the
 *  positive range and never the sign; a signed field such as sync_offset_ms
 *  uses it (audio leads -> positive); a boolean-shaped field is 0 or 1.
 */
@VintfStability
parcelable MetricKVPair
{
    /** Fully-qualified metric name: <domain>.<element>.<instance>.<field>. */
    String name;

    /** The value. int64 always. */
    long value;
}
