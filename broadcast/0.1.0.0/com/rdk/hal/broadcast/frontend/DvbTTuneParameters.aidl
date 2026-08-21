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
import com.rdk.hal.broadcast.frontend.DvbTCodingRate;
import com.rdk.hal.broadcast.frontend.DvbTStandard;
import com.rdk.hal.broadcast.frontend.GuardInterval;
import com.rdk.hal.broadcast.frontend.Modulation;
import com.rdk.hal.broadcast.frontend.SignalDetectMode;
import com.rdk.hal.broadcast.frontend.TransmissionMode;

/**
 * DVB-T-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable DvbTTuneParameters {
    /** The frequency to tune to in Hertz. */
    long frequency;

    /** Signal detect mode to use when tuning. */
    SignalDetectMode signalDetectMode;

    /** The bandwidth to use. */
    Bandwidth bandwidth;

    /** Which DVB-T Standard to use. */
    DvbTStandard dvbTStandard;

    /** The modulation to use. */
    Modulation subCarrierModulation;

    /** LP and HP coding rates for DVB-T/T2. */
    DvbTCodingRate codingRate;

    /** The guard interval to use. */
    GuardInterval guardInterval;

    /** The transmission mode to use. */
    TransmissionMode transmissionMode;

    /**
     * The plp id for DVB-T2.
     *
     * Use -1 for auto. Range 0-255.
     */
    int plpId;

    /** Reserved for future use. */
    ParcelableHolder extension;
}
