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
 * - "BOOT": Initial bootloader-defined state
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
 * On system boot, the implementation shall set the indicator to the first state
 * defined in the platform's HFP file until changed by the set() function.
 *
 * Vendors may define additional custom states as needed.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
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
     * @returns Capabilities The capabilities parcelable of the indicator service.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IIndicator}} for exception handling behavior).
     */
    Capabilities getCapabilities();

    /**
     * Sets a new indicator state.
     *
     * @param[in] state An indicator state to be set.
     * @returns boolean Returns `true` if the state was set successfully, `false` otherwise.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IIndicator}} for exception handling behavior).
     */
    boolean set(in String state);

    /**
     * Gets the current indicator state.
     *
     * @returns State The current indicator state.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IIndicator}} for exception handling behavior).
     */
    String get();
}
