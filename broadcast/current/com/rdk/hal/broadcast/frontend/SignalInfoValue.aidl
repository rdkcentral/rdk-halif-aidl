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

import com.rdk.hal.broadcast.frontend.Bandwidth;
import com.rdk.hal.broadcast.frontend.CodingRate;
import com.rdk.hal.broadcast.frontend.DemodLockState;
import com.rdk.hal.broadcast.frontend.DvbSStandard;
import com.rdk.hal.broadcast.frontend.DvbTCodingRate;
import com.rdk.hal.broadcast.frontend.DvbTStandard;
import com.rdk.hal.broadcast.frontend.GuardInterval;
import com.rdk.hal.broadcast.frontend.Modulation;
import com.rdk.hal.broadcast.frontend.RfLockState;
import com.rdk.hal.broadcast.frontend.TransmissionMode;

/**
 * SignalInfo values.
 *
 * These are the values that can be returned on status requests. It will always be in sync with @ref SignalInfoProperty.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
union SignalInfoValue {
    /** Demodulator lock state. */
    DemodLockState demodLockState;
    /** RF lock state. */
    RfLockState rfLockState;
    /** RF signal level in dbm. */
    float rfLevel;
    /** Carrier to noise ratio in dB. */
    float cnr;
    /** Bit error rate - The number of error bits per 1 billion bits (range 0-1,000,000,000). */
    int ber;
    /** Pre Viterbi BER - The number of error bits per 1 billion bits before correction (range 0-1,000,000,000). */
    int preBer;
    /** Uncorrected Error count. */
    long uncorrectedErrors;
    /** Signal Strength Indicator as defined in NorDig (range 0-100). */
    int ssi;
    /** Signal Quality Indicator as defined in NorDig (range 0-100). */
    int sqi;
    /** The actual frequency that the tuner is locked on (in Hertz). */
    long actualFrequency;
    /** Physical Layer Pipe ID (range 0-255). */
    int plpId;
    /** Physical Layer Pipe IDs (range 0-255). */
    int[] plpIds;
    /** DVB-T2 System ID. */
    int t2SystemId;
    /** The used modulation/sub-modulation. */
    Modulation modulation;
    /** The used guard interval. */
    GuardInterval guardInterval;
    /** The used transmission mode. */
    TransmissionMode transmissionMode;
    /** Bandwidth. */
    Bandwidth bandwidth;
    /** Symbols per second. */
    long symbolRate;
    /** DVB-T Standard. */
    DvbTStandard dvbTStandard;
    /** DVB-S Standard. */
    DvbSStandard dvbSStandard;
    /** Coding rate. */
    CodingRate codingRate;
    /** DVB-T LP and HP coding rates. */
    DvbTCodingRate dvbTCodingRate;
}
