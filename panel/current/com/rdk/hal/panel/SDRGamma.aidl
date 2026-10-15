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
 * @brief SDR gamma options.
 */
@VintfStability
@Backing(type = "int")
enum SDRGamma {
    SDR_GAMMA_INVALID = -1, //!< SDR gamma is invalid.
    SDR_GAMMA_1_8 = 0, //!< SDR gamma is 1.8.
    SDR_GAMMA_1_9 = 1, //!< SDR gamma is 1.9.
    SDR_GAMMA_2_0 = 2, //!< SDR gamma is 2.0.
    SDR_GAMMA_2_1 = 3, //!< SDR gamma is 2.1.
    SDR_GAMMA_2_2 = 4, //!< SDR gamma is 2.2.
    SDR_GAMMA_2_3 = 5, //!< SDR gamma is 2.3.
    SDR_GAMMA_2_4 = 6, //!< SDR gamma is 2.4.
    SDR_GAMMA_BT_1886 = 7, //!< SDR gamma is ITU-R BT.1886.
    SDR_GAMMA_MAX = 8, //!< End of enum.
}