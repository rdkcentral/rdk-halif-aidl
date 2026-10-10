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
package com.rdk.hal.panel;

/**
 *  @brief     SDR gamma curves selectable through `PQParameter.SDR_GAMMA`.
 *
 *  The value of a `PQParameterConfiguration` for `PQParameter.SDR_GAMMA` is one of
 *  these ordinals. A platform supporting a subset lists the supported ordinals in
 *  `PQParameterCapabilities.values`.
 *
 *  Ordinals match the Device Settings `tvSdrGamma_t` enumeration.
 */
@VintfStability
@Backing(type="int")
enum SDRGamma
{
    /** Power-law gamma 1.8. */
    GAMMA_1_8 = 0,
    /** Power-law gamma 1.9. */
    GAMMA_1_9 = 1,
    /** Power-law gamma 2.0. */
    GAMMA_2_0 = 2,
    /** Power-law gamma 2.1. */
    GAMMA_2_1 = 3,
    /** Power-law gamma 2.2. */
    GAMMA_2_2 = 4,
    /** Power-law gamma 2.3. */
    GAMMA_2_3 = 5,
    /** Power-law gamma 2.4. */
    GAMMA_2_4 = 6,
    /** ITU-R BT.1886 reference EOTF. */
    BT_1886 = 7,
}
