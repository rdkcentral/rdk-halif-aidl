/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast.frontend;

/**
 * Available frontend signal info property types.
 *
 * Note that this enum is shared across all frontend types and thus includes values that are only usable on some of
 * them. You should always request and consult the list of supported status properties from the frontend before using
 * any of them.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum SignalInfoProperty {
    /** Clean value when default initialized. */
    UNDEFINED = 0,
    /**
     * The type of the frontend associated with this signal info (e.g., DVB-T, DVB-S, DVB-C).
     * If no tune has been performed, this value is UNDEFINED.
     */
    FRONTEND_TYPE,
    /** The actual frequency that the tuner is locked on (in Hertz). */
    ACTUAL_FREQUENCY,
    /** Demod Lock status. */
    DEMOD_LOCK,
    /** RF Lock status. */
    RF_LOCK,
    /** RF signal level in dbm. */
    RF_LEVEL,
    /** Carrier to noise ratio in dB. */
    CNR,
    /** Bit error rate - The number of error bit per 1 billion bits. */
    BER,
    /** Pre Viterbi BER - The number of error bit per 1 billion bits before correction. */
    PRE_BER,
    /** Uncorrected error count. */
    UNCORRECTED_ERRORS,
    /** Signal Strength Indicator as defined in NorDig (range 0-100). */
    SSI,
    /** Signal Quality Indicator as defined in NorDig (range 0-100). */
    SQI,
    /** Physical Layer Pipe ID (range 0-255). */
    PLP_ID,
    /** Physical Layer Pipe IDs (range 0-255). */
    PLP_IDS,
    /** DVB-T2 System Id. */
    T2_SYSTEM_ID,
    /** The used modulation / sub-modulation. */
    MODULATION,
    /** The used guard interval. */
    GUARD_INTERVAL,
    /** The used transmission mode. */
    TRANSMISSION_MODE,
    /** Bandwidth. */
    BANDWIDTH,
    /** Symbol Rate. */
    SYMBOL_RATE,
    /** DVB-T Standard. */
    DVB_T_STANDARD,
    /** DVB-S Standard. */
    DVB_S_STANDARD,
    /** Code rate. */
    CODE_RATE,
    /** DVB-C Annex. */
    DVB_C_ANNEX,
    /** Spectral inversion mode. */
    SPECTRAL_INVERSION,
    /** roll-off factor. */
    ROLL_OFF,
    /** DVB-T hierarchical transmission mode. */
    DVB_T_HIERARCHY,
    /** DVB-T MISO mode. */
    DVB_T_MISO,
    /** DVB-S/S2/S2X inner FEC. */
    DVB_S_INNER_FEC,
    /** DVB-S2/S2X pilot mode. */
    DVB_S_PILOT,
    /** DVB-S2/S2X physical-layer scrambling mode. */
    DVB_S_PLS_MODE,
    /** DVB-S2/S2X physical-layer scrambling code. */
    DVB_S_PLS_CODE,
    /** DVB-S2/S2X input stream identifier. */
    DVB_S_INPUT_STREAM_ID,
}
