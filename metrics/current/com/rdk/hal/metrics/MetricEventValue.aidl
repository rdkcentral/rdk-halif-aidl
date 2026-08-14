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
 *  @brief     One value carried by an event.
 *
 *  The name is BARE - "duration_ms", "reason", "vendor_code" - because
 *  MetricsEvent already says which source raised the occurrence and which kind
 *  it was. Prefixing would say the same thing twice, and there is no
 *  four-segment path that would be correct anyway: an event payload is a
 *  property of the occurrence, not a field of the source.
 *
 *  This is why an event does not carry MetricKVPair. That parcelable promises a
 *  fully-qualified name, because a metric value read from a source has one and
 *  needs it once it outlives the call. A payload value has no such name to give,
 *  and a type that promised one would be lying in every event ever sent.
 *
 *  Every value is int64, as everywhere else in this interface. A value the
 *  source cannot supply is OMITTED from the event, never defaulted - a PTS that
 *  cannot be derived is absent, not sent as -1.
 */
@VintfStability
parcelable MetricEventValue
{
    /** Bare payload name, as declared in MetricEventFieldInfo. */
    String name;

    /** The value. int64 always. */
    long value;
}
