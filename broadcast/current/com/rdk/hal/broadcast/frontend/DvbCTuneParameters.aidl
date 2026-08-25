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

import com.rdk.hal.broadcast.frontend.CodingRate;
import com.rdk.hal.broadcast.frontend.DvbCAnnex;
import com.rdk.hal.broadcast.frontend.DvbCBandwidth;
import com.rdk.hal.broadcast.frontend.DvbCModulation;
import com.rdk.hal.broadcast.frontend.SignalDetectMode;

/**
 * DVB-C-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable DvbCTuneParameters {
    /** The frequency in Hertz. */
    long frequency;

    /** Signal detect mode to use when tuning. */
    SignalDetectMode signalDetectMode;

    /**
     * The symbol rate in symbols per second.
     *
     * Use -1 for auto symbol rate if it is supported.
     */
    int symbolRate;

    /** The bandwidth to use. */
    DvbCBandwidth bandwidth;

    /** Which DVB-C Annex to use. */
    DvbCAnnex dvbCAnnex;

    /** The modulation to use. */
    DvbCModulation modulation;

    /** Coding rate - the inner FEC. */
    CodingRate codingRate;

    /** Reserved for future use. */
    ParcelableHolder extension;
}
