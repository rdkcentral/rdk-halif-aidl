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
import com.rdk.hal.broadcast.frontend.DvbTCapabilities;
import com.rdk.hal.broadcast.frontend.DvbCCapabilities;
import com.rdk.hal.broadcast.frontend.DvbSCapabilities;
import com.rdk.hal.broadcast.frontend.AtscCapabilities;
import com.rdk.hal.broadcast.frontend.SignalInfoProperty;

/**
 *  @brief     Capabilities for the Frontend
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

@VintfStability
parcelable Capabilities {
    /** Supported info types for carrier */
    SignalInfoProperty[] SignalInfoProperties;

    /** Minimum frequency range of the tuner */
    long minFrequencyHz;
    /** Maximum frequency range of the tuner */
    long maxFrequencyHz;
    
    /**
     * Range in Hertz that will result in the Tuner obtaining a lock
     */
    long acquireFrequencyRangeHz;

    /** Minimum symbol rate in Symbols per second */
    int minSymbolRate;
    /** Maximum symbol rate in Symbols per second */
    int maxSymbolRate;

    /** A value of true indicates that the tuner can autodetect the symbol rate */
    boolean hasAutoSymbolRate;

    /** Capabilities specific to a given @FrontendType */
    union SpecificCapabilities {
        DvbTCapabilities dvbTCapabilities;
        DvbCCapabilities dvbCCapabilities;
        AtscCapabilities atscCapabilities;        
        DvbSCapabilities dvbSCapabilities;
    }

    /** Reserved for future use */
    ParcelableHolder extension;
}
