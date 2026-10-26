/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.videodecoder;

/**
 *  @brief     Two-dimensional pixel resolution.
 *
 *  Carries a `{width, height}` pair in pixels. Used wherever a structured
 *  resolution is required in place of two loose `int` parameters — for
 *  example, batched stream-configuration parcelables and capability
 *  descriptors.
 *
 *  Both fields are integer pixel counts and MUST be > 0 when the
 *  resolution is used as a hint or target. Container types that allow
 *  "unknown" must document that convention on the carrying field.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable Resolution {

    /**
     * Frame width in pixels. Must be > 0.
     */
    int width;

    /**
     * Frame height in pixels. Must be > 0.
     */
    int height;
}
