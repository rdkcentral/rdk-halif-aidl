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
import com.rdk.hal.broadcast.frontend.Bandwidth;
import com.rdk.hal.broadcast.frontend.CodingRate;
import com.rdk.hal.broadcast.frontend.DvbTStandard;
import com.rdk.hal.broadcast.frontend.Modulation;
import com.rdk.hal.broadcast.frontend.GuardInterval;
import com.rdk.hal.broadcast.frontend.TransmissionMode;

/**
 *  @brief     DVB-T specific capabilities.
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/**
 * The AUTO member of all the enums will only be returned if the frontend supports a real auto
 * selection of the respective parameter. Just choosing the first applicable value and bailing out
 * on error doesn't count as AUTO mode.
 */
@VintfStability
parcelable DvbTCapabilities {
    /** Supported bandwidths */
    Bandwidth[] bandwidths;
    /** Supported code rates */
    CodingRate[] codingRates;
    /** Supported standards */
    DvbTStandard[] dvbTStandards;
    /** Supported modulations */
    Modulation[] subCarrierModulations;
    /** Supported guard intervals */
    GuardInterval[] guardIntervals;
    /** Supported transmission mode */
    TransmissionMode[] transmissionModes;
    /** Reserverd for future use */
    ParcelableHolder extension;
}
