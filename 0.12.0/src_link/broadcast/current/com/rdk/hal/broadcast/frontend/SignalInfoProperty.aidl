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
package com.rdk.hal.broadcast.frontend;

/**
 *  @brief     Available frontend info types
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/**
 * Note that this enum is shared across all frontend types and thus includes values that are only
 * usable on some of them. You should always request and consult the list of supported status
 * properties from the frontend before using any of them.
 */
@VintfStability
enum SignalInfoProperty {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /** Demod Lock status */    
    DEMOD_LOCK,
    /** RF Lock status */
    RF_LOCK,
    /** RF signal level in dbm */
    RFLEVEL,
    /** Signal to noise ratio in dB (float) */
    CNR,
    /** Bit error rate - The number of error bit per 1 billion bits */
    BER,
    /** Pre Viterbi BER - The number of error bit per 1 billion bits before correction */
    PRE_BER,
    /** Uncorrected Error count */
    UNC,
    /** Signal Strength Indicator as defined in NorDig (int, range 0-100) */
    SSI,
    /** Signal Quality Indicator as defined in NorDig (int, range 0-100) */
    SQI,
    /** The actual frequency that the tuner is locked on (long, in Hertz) */
    ACTUAL_FREQUENCY,
    /** Physical Layer Pipe ID (int, range 0-255) */
    PLP_ID,
    /** Physical Layer Pipe IDs (array of int, range 0-255) */
    PLP_IDS,
    /** DVB-T2 System Id */
    T2_SYSTEM_ID,
    /** The used modulation / submodulation. @ref Modulation */
    MODULATION,
    /** The used guard interval. @ref GuardInterval */
    GUARD_INTERVAL,
    /** The used tranmission mode. @ref TransmissionMode */
    TRANSMISSION_MODE,
    /** Bandwidth */
    BANDWIDTH,
    /** Symbol Rate */
    SYMBOL_RATE,
}
