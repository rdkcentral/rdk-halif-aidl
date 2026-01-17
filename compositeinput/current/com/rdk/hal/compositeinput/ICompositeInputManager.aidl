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
 */
@VintfStability
interface ICompositeInputManager
{
    /** The service name to publish. */
    const @utf8InCpp String serviceName = "composite_input";

    /**
     * Gets the platform capabilities for composite input.
     *
     * This function can be called at any time and returns platform-wide information
     * about supported features and properties. The returned value is constant and
     * must not change between calls.
     *
     * @returns PlatformCapabilities parcelable containing platform-wide capabilities.
     *
     * @see PlatformCapabilities
     */
    PlatformCapabilities getPlatformCapabilities();

    /**
     * Gets the list of available composite input port IDs.
     *
     * Returns an array of valid port identifiers that can be used with getPort().
     * The array size matches PlatformCapabilities.maxPorts and is constant.
     *
     * @returns Array of port IDs available on this platform (typically 0 to maxPorts-1).
     *
     * @see getPort()
     */
    int[] getPortIds();

    /**
     * Gets the interface for a specific composite input port.
     *
     * Returns a port-specific interface for controlling and querying an individual
     * composite input port. Each port can be independently controlled.
     *
     * @param[in] portId     The port ID to access. Must be one of the IDs returned by getPortIds().
     * @returns ICompositeInputPort interface for the requested port, or null if port not found.
     *
     * @retval ICompositeInputPort   Valid port interface for the specified portId.
     * @retval null                  Port ID not found or invalid.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if portId is out of range.
     * @pre portId must be valid (from getPortIds()).
     *
     * @see ICompositeInputPort, getPortIds()
     */
    @nullable ICompositeInputPort getPort(in int portId);
}
