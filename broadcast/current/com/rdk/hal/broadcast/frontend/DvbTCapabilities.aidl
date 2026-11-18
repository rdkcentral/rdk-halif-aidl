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

import com.rdk.hal.broadcast.frontend.DvbTBandwidth;
import com.rdk.hal.broadcast.frontend.DvbTCodeRates;
import com.rdk.hal.broadcast.frontend.DvbTConstellation;
import com.rdk.hal.broadcast.frontend.DvbTGuardInterval;
import com.rdk.hal.broadcast.frontend.DvbTHierarchy;
import com.rdk.hal.broadcast.frontend.DvbTMiso;
import com.rdk.hal.broadcast.frontend.DvbTStandard;
import com.rdk.hal.broadcast.frontend.DvbTTransmissionMode;
import com.rdk.hal.broadcast.frontend.SpectralInversion;

/**
 * @brief DVB-T specific capabilities.
 *
 * The AUTO member of all the enums will only be returned if the frontend supports a real auto selection of the
 * respective parameter. Just choosing the first applicable value and bailing out on error doesn't count as AUTO mode.
 *
 * There is deliberately no capability flag for PLP selection. PLP selection is a mandatory requirement for a DVB-T2
 * frontend, so a frontend that reports DvbTStandard.T2 in dvbTStandards shall support DvbTTuneParameters.plpId,
 * including DvbTPlpId.AUTO.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable DvbTCapabilities {
    /** Supported bandwidths. */
    DvbTBandwidth[] bandwidths;

    /** Supported standards. */
    DvbTStandard[] dvbTStandards;

    /** Supported constellations (AUTO only where the frontend auto-detects, HAL.BROADCAST.21). */
    DvbTConstellation[] constellations;

    /** Supported code rates (AUTO only where the frontend auto-detects, HAL.BROADCAST.21). */
    DvbTCodeRates.Value[] codeRates;

    /** Supported guard intervals (AUTO only where the frontend auto-detects, HAL.BROADCAST.21). */
    DvbTGuardInterval[] guardIntervals;

    /** Supported transmission mode (AUTO only where the frontend auto-detects, HAL.BROADCAST.21). */
    DvbTTransmissionMode[] transmissionModes;

    /** Supported spectral inversion modes (AUTO only where the frontend auto-detects, HAL.BROADCAST.21). */
    SpectralInversion[] inversions;

    /** Supported hierarchical transmission modes (AUTO only where the frontend auto-detects, HAL.BROADCAST.21). */
    DvbTHierarchy[] hierarchies;

    /** Supported MISO modes (AUTO only where the frontend auto-detects, HAL.BROADCAST.21). */
    DvbTMiso[] misoModes;

    /** Reserved for future use. */
    ParcelableHolder extension;
}
