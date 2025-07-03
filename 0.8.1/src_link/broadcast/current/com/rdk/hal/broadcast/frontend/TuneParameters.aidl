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
import com.rdk.hal.broadcast.frontend.AtscTuneParameters;
import com.rdk.hal.broadcast.frontend.DvbCTuneParameters;
import com.rdk.hal.broadcast.frontend.DvbTTuneParameters;
//import com.rdk.hal.broadcast.frontend.DvbSTuneParameters;
//import com.rdk.hal.broadcast.frontend.Atsc3TuneParameters;
//import com.rdk.hal.broadcast.frontend.IsdbTTuneParameters;

/**
 *  @brief     Tuner-specific tuning parameters
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

@VintfStability
union TuneParameters {
    /** Tune parameters for tuning ATSC tuners */
    AtscTuneParameters atscTuneParameters;
    /** Tune parameters for tuning DVB-T tuners */
    DvbTTuneParameters dvbTTuneParameters;
    /** Tune parameters for tuning DVB-C tuners */
    DvbCTuneParameters dvbCTuneParameters;

    /** TODO */
    /** Tune parameters for tuning ATSC3 tuners */
    //Atsc3TuneParameters atscTuneParameters;
    /** Tune parameters for tuning DVB-S tuners */
    //DvbSTuneParameters dvbSTuneParameters;
    /** Tune parameters for tuning ISDB-T tuners */
    //IsdbTTuneParameters isdbTTuneParameters;

}
