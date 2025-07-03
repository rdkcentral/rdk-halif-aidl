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
package com.rdk.hal.deviceinfo;
import com.rdk.hal.deviceinfo.Capabilities;
import com.rdk.hal.deviceinfo.HALVersion;
import com.rdk.hal.deviceinfo.SetPropertyResult;
import com.rdk.hal.deviceinfo.Property;

/** 
 *  @brief     Device Information HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Amit Patel
 *  @author    Milorad Neskovic
 *  @author    Tijo Thomas
 *  @author    Gerald Weatherup
 */

@VintfStability
interface IDeviceInfo
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "DeviceInfo";
    
    /**
     * Gets the capabilities of the Device Info service.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();

    /**
     * Gets the HAL version.
     *
     * The HAL version is defined as major.minor.doc and relates to the version of the
     * HAL specification version this vendor layer supports.
     *
     * @returns HALVersion parcelable.
     */
    HALVersion getHALVersion();

    /**
     * Gets a persisted device property.
     * 
     * On success, the returned `String` contains the current property value.
     * 
     * All ASCII hex values are in upper case.
     * All MAC addresses are in "XX:XX:XX:XX:XX:XX" format.
     * 
     * If the property is not supported the function returns null.
     *
     * Property key strings should be one of the define KEY_nnn strings
     * or can be a custom product KEY_OEM_nnn string.
     *
     * @param[in] propertyKey           The key of a property from the Property enum.
     *
     * @returns String value or null if the property key is unsupported.
     * 
     * @see setProperty(), getCapabilities()
     */
    @nullable String getProperty(in String propertyKey);

    /**
     * Sets and persists a device property.
     * 
     * The new value is written and verified before the function returns.
     * 
     * Usually only the factory needs to set these properties.
     * 
     * All ASCII hex values must be in upper case.
     * All MAC addresses must be in "XX:XX:XX:XX:XX:XX" format.
     * 
     * Property key strings should be one of the define KEY_nnn strings
     * or can be a custom product KEY_OEM_nnn string.
     *
     * @param[in] propertyKey           The key string of a property.
     * @param[in] value                 The new value of the property.
     *
     * @returns SetPropertyResult
     * @retval SUCCESS                      Success
     * @retval ERROR_INVALID_PARAM          Parameter passed to this function is invalid
     * @retval ERROR_MEMORY_EXHAUSTED       Memory allocation failure
     * @retval ERROR_FAILED_CRC_CHECK       CRC check failed
     * @retval ERROR_WRITE_FLASH_FAILED     Flash write failed
     * @retval ERROR_FLASH_READ_FAILED      Flash read failed
     * @retval ERROR_FLASH_VERIFY_FAILED    Flash verification failed
     * 
     * @see SetPropertyResult
     */
    SetPropertyResult setProperty(in String propertyKey, in String value);

    /** @} */
}




