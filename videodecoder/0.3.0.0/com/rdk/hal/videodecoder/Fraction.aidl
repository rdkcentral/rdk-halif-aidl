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
 *  @brief     Rational number expressed as numerator / denominator.
 *
 *  Used wherever a structured rational is required in place of two loose
 *  `int` parameters — frame rate (e.g. 30000/1001 for 29.97 fps), pixel
 *  aspect ratio (e.g. 10/11 for NTSC), or any other ratio.
 *
 *  Carrying APIs document their own rules for `0/0` ("unknown") and
 *  zero-denominator handling. As a base contract:
 *  - `denominator` MUST be > 0 unless the carrying API explicitly permits
 *    `0/0` to encode "unknown".
 *  - `numerator` MUST be >= 0.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable Fraction {

    /**
     * Numerator. Must be >= 0.
     */
    int numerator;

    /**
     * Denominator. Must be > 0 unless the carrying API permits 0/0.
     */
    int denominator;
}
