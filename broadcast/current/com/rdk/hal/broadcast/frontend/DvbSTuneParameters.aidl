/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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

import com.rdk.hal.broadcast.frontend.CodingRate;
import com.rdk.hal.broadcast.frontend.DvbSStandard;
import com.rdk.hal.broadcast.frontend.Modulation;
import com.rdk.hal.broadcast.frontend.RollOff;

/**
 *  @brief     DVB-S/S2/S2X-specific tuning parameters.
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler
 */
@VintfStability
parcelable DvbSTuneParameters {
    /** The frequency to tune to in Hertz */
    long frequencyHz;
    /**
     * The symbol rate in symbols per second.
     *
     * Use 0 for auto symbol rate detection (if supported, see DvbSCapabilities).
     */
    int symbolRate;
    /** Which DVB-S standard to use */
    DvbSStandard dvbSStandard;
    /** The modulation to use */
    Modulation modulation;
    /** Inner FEC coding rate */
    CodingRate innerFec;
    /** Roll-off factor */
    RollOff rollOff;
    /** Reserved for future use */
    ParcelableHolder extension;
}
