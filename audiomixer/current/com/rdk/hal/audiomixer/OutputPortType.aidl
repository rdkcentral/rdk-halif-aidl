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
 * @brief    Physical / logical type of an audio output port.
 * @details  Provides a programmatic identification of an output port,
 *           independent of the human-readable `OutputPortCapabilities.portName`.
 *           Declared per output port in the HFP YAML and surfaced via
 *           `OutputPortCapabilities.portType`.
 *
 *           Middleware should branch on `portType` (not `portName`) when
 *           applying type-specific policy — e.g. transcode-to-AC3 only on
 *           SPDIF, hot-unplug handling only on HDMI/ARC/EARC, pairing flow
 *           only on BLUETOOTH.
 *
 * @author    Gerald Weatherup
 * @copyright Copyright 2026 RDK Management
 */
@VintfStability
@Backing(type="int")
enum OutputPortType {
    /** Type cannot be determined or is platform-specific. */
    UNKNOWN = 0,

    /** HDMI output (supports PCM, AC3, EAC3, MAT, TrueHD passthrough). */
    HDMI = 1,

    /** S/PDIF coaxial digital output (supports PCM, AC3, DTS passthrough). */
    SPDIF = 2,

    /** TOSLINK / optical digital output (electrically distinct from SPDIF coax, same protocol). */
    OPTICAL = 3,

    /** Analogue line-out / internal speakers / amplifier (PCM only). */
    SPEAKERS = 4,

    /**
     * Bluetooth audio output (A2DP sink — TV streams to BT speaker / headphones).
     * Connection lifecycle is platform-specific; pairing is typically handled outside
     * the audiomixer HAL. CONNECTION_STATE reflects the active A2DP link.
     */
    BLUETOOTH = 5,

    /**
     * HDMI Audio Return Channel — TV sends audio back to AVR/soundbar.
     * Logically an output even though the cable is the HDMI input. Format negotiation
     * uses CEC; capability subset of HDMI direct (typically PCM + AC3).
     */
    ARC = 6,

    /**
     * HDMI Enhanced Audio Return Channel (eARC) — higher bandwidth than ARC.
     * Supports the full HDMI audio format set (MAT, TrueHD, Atmos object audio)
     * via the dedicated Audio Return Data Channel on TMDS.
     */
    EARC = 7,

    /** Composite analogue audio output bundled with composite video. */
    COMPOSITE = 8,

    /**
     * Vendor-specific / platform-internal port not covered by the standard types.
     * Use `portName` for differentiation.
     */
    INTERNAL = 1000
}
