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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiomixer;

/**
 * @brief    Immersive (object-based) audio carried on an output port.
 * @details  Reported in ActiveOutputFormat.immersive. Combined with
 *           ActiveOutputFormat.format it tells middleware how the immersive
 *           content leaves the port:
 *           - a bitstream format (EAC3, MAT, TRUEHD, DTS_HD) — the objects
 *             are delivered to an external decoder (AVR, soundbar);
 *           - PCM_STEREO or PCM_MULTICHANNEL — the HAL renders the objects
 *             itself to the port's channel layout.
 *
 * @author    Gerald Weatherup
 * @copyright Copyright 2026 RDK Management
 */
@VintfStability
@Backing(type="int")
enum ImmersiveFormat {
    /** No immersive content; channel-based audio only. */
    NONE = 0,
    /** Dolby Atmos. */
    DOLBY_ATMOS = 1,
    /** DTS:X. */
    DTS_X = 2,
}
