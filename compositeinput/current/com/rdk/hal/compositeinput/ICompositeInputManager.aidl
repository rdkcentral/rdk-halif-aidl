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

import com.rdk.hal.compositeinput.PlatformCapabilities;
import com.rdk.hal.compositeinput.Port;
import com.rdk.hal.compositeinput.ICompositeInputPort;

/**
 * @brief Composite Input Manager interface.
 * 
 * Provides platform-independent access to composite video input functionality.
 * This manager interface allows discovery and access to individual composite input ports.
 * 
 * @author Gerald Weatherup
 */
@VintfStability
interface ICompositeInputManager
{
    /** The service name to publish. */
    const @utf8InCpp String serviceName = "composite_input_manager";
    
    /**
     * @brief Gets the platform capabilities for composite input.
     * 
     * Returns information about supported features, video standards,
     * and available ports on this platform.
     * 
     * @returns PlatformCapabilities parcelable containing platform-wide capabilities.
     */
    PlatformCapabilities getPlatformCapabilities();
    
    /**
     * @brief Gets the list of available composite input port IDs.
     * 
     * @returns Array of port IDs available on this platform (0 to maxPorts-1).
     */
    int[] getPortIds();
    
    /**
     * @brief Gets the interface for a specific composite input port.
     * 
     * Returns a port-specific interface for controlling and querying
     * an individual composite input port.
     * 
     * @param[in] portId The port ID (0 to maxPorts-1).
     * @returns ICompositeInputPort interface for the requested port, or null if port not found.
     * @exception EX_ILLEGAL_ARGUMENT if portId is out of range.
     */
    @nullable ICompositeInputPort getPort(in int portId);
}
