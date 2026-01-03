/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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

package com.rdk.hal.compositeinput;

import com.rdk.hal.compositeinput.Port;
import com.rdk.hal.compositeinput.SignalStatus;
import com.rdk.hal.compositeinput.VideoResolution;

/**
 * @brief Current status of a composite input port.
 * 
 * Describes the runtime state of a composite input port, including
 * connection, signal, and video mode information.
 */
@VintfStability
parcelable PortStatus
{
    /**
     * @brief Detailed signal information.
     */
    @VintfStability
    parcelable SignalInfo
    {
        /** True if horizontal/vertical sync is detected. */
        boolean syncDetected;
        
        /** True if color burst signal is detected. */
        boolean colorBurstDetected;
        
        /** Signal strength in dBm (negative values, higher is better). */
        int signalStrengthDbm;
        
        /** Timestamp of last signal change in milliseconds since epoch. */
        long lastSignalChangeMs;
    }
    
    /** Port ID (0 to maxPorts-1). */
    int portId;
    
    /** True if a physical cable/source is connected to this port. */
    boolean connected;
    
    /** True if this port is currently active for presentation. */
    boolean active;
    
    /** Current signal status. */
    SignalStatus signalStatus;
    
    /** Signal quality percentage (0-100), or -1 if not available. */
    byte signalQuality;
    
    /** Detected video resolution and format, or null if no signal. */
    @nullable VideoResolution detectedResolution;
    
    /** Detailed signal information, or null if not available. */
    @nullable SignalInfo signalInfo;
}
