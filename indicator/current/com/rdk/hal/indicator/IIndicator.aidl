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
package com.rdk.hal.indicator;
import com.rdk.hal.indicator.Capabilities;

/**
 * @brief Indicator HAL interface.
 *
 * Defines the Hardware Abstraction Layer (HAL) interface for indicator services.
 * Each indicator instance represents a hardware-controlled visual indicator
 * (e.g., LED, panel display) that can be set to different states.
 *
 * For RDK reference implementations, a single global indicator is typically used
 * to reflect the overall device state. Third-party vendors may implement multiple
 * independent indicator instances if required by their platform architecture.
 *
 * States are represented as strings to provide flexibility and extensibility.
 * Standard state names include:
 * - "BOOT": Initial bootloader-defined state. The interface is expected to set this
 *   state on boot until changed by the set() function. It is up to the implementation
 *   to set the first state. In the case of RDK Comcast method, it's a "BOOT" state.
 * - "ACTIVE": System is fully operational
 * - "STANDBY": Low-power idle state
 * - "OFF": All indicators are off
 * - "DEEP_SLEEP": Deep sleep mode
 * - "WPS_CONNECTING": Wi-Fi Protected Setup is active
 * - "WPS_CONNECTED": WPS connection successful
 * - "WPS_ERROR": WPS session failed
 * - "WPS_SES_OVERLAP": Multiple WPS sessions detected
 * - "WIFI_ERROR": Wi-Fi hardware or configuration fault
 * - "IP_ACQUIRED": IP address successfully assigned
 * - "NO_IP": IP assignment failed
 * - "FULL_SYSTEM_RESET": Factory reset in progress
 * - "USB_UPGRADE": Firmware upgrade via USB
 * - "SOFTWARE_DOWNLOAD_ERROR": Software update failed
 * - "PSU_FAILURE": Power supply fault detected
 *
 * Vendors may define additional custom states as needed.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */

@VintfStability
interface IIndicator
{
    /** Indicator resource ID type */
    @VintfStability
    parcelable Id {
        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities of this indicator instance.
     *
     * This function can be called at any time and returns the set of states
     * supported by this specific indicator instance. The returned value must
     * not change between calls.
     *
     * @returns Capabilities parcelable containing supported state strings.
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    Capabilities getCapabilities();

    /**
     * Sets a new indicator state.
     *
     * The state string must be one of the states listed in the capabilities
     * returned by getCapabilities(). Setting an unsupported state will fail.
     *
     * @param[in] state An indicator state string to be set.
     * @returns Success flag indicating whether state was set.
     * @retval true State was set successfully.
     * @retval false State is not supported or setting failed.
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid state string.
     */
    boolean set(in String state);

    /**
     * Gets the current indicator state.
     *
     * Returns the currently active state as a string.
     *
     * @returns Current indicator state string.
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    String get();
}
