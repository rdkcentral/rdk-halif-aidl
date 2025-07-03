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
import com.rdk.hal.broadcast.frontend.DvbCAnnex;
import com.rdk.hal.broadcast.frontend.Modulation;

/**
 *  @brief     DVB-T-specific tuning parameters
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

@VintfStability
parcelable DvbCTuneParameters {
    /** The bandwidth to use */
    Bandwidth bandwidth;
    /** Which DVB-C Annex to use */
    DvbCAnnex dvbCAnnex;
    /** The modulation to use */
    Modulation modulation;
    /** Coding rate - the inner FEC */
    CodingRate codingRate;
    /** The frequency in Hertz */
    long frequencyHz;
    /** The symbolRate in symbols per second. (Use 0 for auto symbolRate if it is supported) */
    int symbolRate;
    /** Reserved for future use. Allows for parsing of custom data during development and testing */   
    ParcelableHolder extension;
}
