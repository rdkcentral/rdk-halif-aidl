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
package com.rdk.hal.boot;
import com.rdk.hal.boot.Capabilities;
import com.rdk.hal.boot.ResetType;
import com.rdk.hal.boot.BootReason;
import com.rdk.hal.boot.PowerSource;

/** 
 *  @brief     Boot HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IBoot
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "Boot";

    /**
     * Gets the capabilities of the boot service.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();

    /**
     * Gets the reason the device was booted.
     * 
     * @returns BootReason
     */
    BootReason getBootReason();

    /**
     * Performs a shutdown and warm reboot of the device.
     * 
     * A number of reset types can be applied as part of the reboot process.
     * If no reset types are provided, then a normal reboot is performed.
     * On success this function does not return.
     * 
     * @param[in] resetTypes    Array of `ResetType` values.
     */
    void reboot(in ResetType[] resetTypes);

    /**
     * Performs a shutdown of the device, without reboot.
     * 
     * On success this function does not return.
     */
    void shutdown();

    /**
     * Gets the device power source.
     *
     * @return PowerSource
     */
    PowerSource getPowerSource();
}
