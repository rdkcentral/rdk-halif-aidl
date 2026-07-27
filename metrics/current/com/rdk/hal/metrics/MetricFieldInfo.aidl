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
 *  @brief     What one declared field is — enough to interpret the number
 *             without consulting anything else at runtime.
 */
@VintfStability
parcelable MetricFieldInfo
{
    /** Field name within its element, e.g. "frames_decoded". */
    String name;

    /** "frames" | "ms" | "us" | "ns" | "bytes" | "events" | "percent" | "hz" | "none" */
    String unit;

    /**
     *  How the value behaves over time — this governs the arithmetic a
     *  consumer may do, and is what keeps deltas and samples from being mixed:
     *
     *    "counter"     cumulative since source creation; may be differenced
     *    "current"     a live sample; absolute, NEVER sum it
     *    "high_water"  monotone max since source creation; absolute
     *    "config"      a tunable's present value; absolute
     */
    String kind;

    /** True when setField() is accepted on this field. */
    boolean writable;
}
