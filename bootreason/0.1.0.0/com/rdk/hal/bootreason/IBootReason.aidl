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
package com.rdk.hal.bootreason;
import com.rdk.hal.bootreason.Capabilities;
import com.rdk.hal.bootreason.ResetType;
import com.rdk.hal.bootreason.BootCause;
import com.rdk.hal.bootreason.PowerSource;

/** 
 *  @brief     Boot Reason HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IBootReason
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "BootReason";

    /**
     * Gets the capabilities of the boot service.
     *
     * @returns Capabilities parcelable.
     *
     */
    Capabilities getCapabilities();

    /**
     * Gets the reason the device was booted.
     * 
     * @returns BootCause
     *
     */
    BootCause getBootCause();

    /**
     * Sets the reboot reason that will be associated with the next reboot.
     * This function is used for validation testing the retrieval method of various boot
     * scenarios.
     *
     * @param[in] cause           BootCause value.
     * @param[in] causeString     Free-form reboot reason string (64 bytes)
     */
    void setBootCause(in BootCause cause, in String reasonString);

    /**
     * Performs a shutdown and warm reboot of the device.
     * 
     * A number of reset types can be applied as part of the reboot process.
     * On success this function does not return.
     * 
     * @param[in] resetType     ResetType value
     * @param[in] causeString  Free-form reset reason string (64 bytes)
     */
    void reboot(in ResetType resetType, in String reasonString);

    /**
     * Gets the device power source.
     *
     * @return PowerSource
     */
    PowerSource getPowerSource();
}
