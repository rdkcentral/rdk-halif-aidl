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
 * @brief Audio channel position definitions for PCM audio layouts.
 *
 * Defines the standardised channel positions used in multi-channel audio capture.
 * These enumeration values describe the physical or logical placement of audio
 * channels within the audio frame (e.g., front left, surround right, overhead, etc.).
 *
 * Channel positions are typically arranged as:
 * - **Front**: Left, Right, Centre
 * - **Low-Frequency**: Subwoofer / LFE
 * - **Surround/Rear**: Side Left, Side Right, Rear Left, Rear Right, Rear Centre
 * - **Height/Overhead**: Top Front Left, Top Front Right, Top Front Centre, Top Side Left, Top Side Right, Top Rear Left, Top Rear Right
 * - **Wide**: Wide Left, Wide Right
 */
@VintfStability
@Backing(type="int")
enum Channel {
    // Front channels
    CH_FL,   // Front Left
    CH_FR,   // Front Right
    CH_FC,   // Front Centre

    // Low-frequency channel
    CH_LFE,  // Subwoofer / Low-Frequency Effects

    // Surround / rear channels
    CH_SL,   // Side Left
    CH_SR,   // Side Right
    CH_RL,   // Rear Left
    CH_RR,   // Rear Right
    CH_RC,   // Rear Centre

    // Height / overhead channels
    CH_TFL,  // Top Front Left
    CH_TFR,  // Top Front Right
    CH_TFC,  // Top Front Centre
    CH_TSL,  // Top Side Left
    CH_TSR,  // Top Side Right
    CH_TRL,  // Top Rear Left
    CH_TRR,  // Top Rear Right

    // Wide channels
    CH_WL,   // Wide Left
    CH_WR,   // Wide Right
}
