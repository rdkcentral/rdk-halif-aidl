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
import com.rdk.hal.broadcast.frontend.Modulation;
import com.rdk.hal.broadcast.frontend.GuardInterval;
import com.rdk.hal.broadcast.frontend.TransmissionMode;
import com.rdk.hal.broadcast.frontend.Bandwidth;
import com.rdk.hal.broadcast.frontend.DvbTStandard;
import com.rdk.hal.broadcast.frontend.DvbSStandard;

/**
 *  @brief     SignalInfo values
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/**
 * These are the values that can be returned on status requests. It will always be in sync with
 * @ref SignalInfoProperty.
 */
@VintfStability
union SignalInfoValue {
    /** Demod Lock status */    
    boolean isDemodLocked;

    /** RF Lock status */
    boolean isRfLocked;

    /** RF signal level in dbm */
    int rfLevel;

    /** Carrier to noise ratio in dB (float) */
    float cnr;

    /** Bit error rate - The number of error bit per 1 billion bits */
    int ber;
    
    /** Pre Viterbi BER - The number of error bit per 1 billion bits before correction */
    int preBer;

    /** Uncorrected Error count */
    int uncorrectedErrors;

    /** Signal Strength Indicator as defined in NorDig (int, range 0-100) */
    int ssi;

    /** Signal Quality Indicator as defined in NorDig (int, range 0-100) */
    int sqi;

    /** The actual frequency that the tuner is locked on (long, in Hertz) */
    long actualFrequencyHz;

    /** Physical Layer Pipe ID (int, range 0-255) */
    int plpId;

    /** Physical Layer Pipe IDs (array of int, range 0-255) */
    int[] plpIds;

    /** DVB-T2 System Id @See SignalInfoProperty::T2_SYSTEM_ID*/
    int t2SystemId;

    /** The used modulation / sub-modulation. */
    Modulation modulation;
    
    /** The used guard interval. (enum value) */
    GuardInterval guardInterval;

    /** The used transmission mode. */
    TransmissionMode transmissionMode;

    /** Bandwidth */
    Bandwidth bandwidth;
     
    /** Symbols per second */
    int symbolRate;

    /** DVB-T Standard */
    DvbTStandard dvbTStandard;

    /** DVB-S Standard */
    DvbSStandard dvbSStandard;
}
