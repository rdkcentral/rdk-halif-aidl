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
    * Gets a persisted device property by key.
    *
    * On success, returns a `Property` parcelable (see Property.aidl).
    * @See `PropertyType.aidl` for supported formats and validation rules.
    *
    * Property key strings must be one of the keys listed in `getCapabilities().supportedProperties[]`.
    *
    * @param[in] propertyKey  The key of a property to retrieve.
    * @returns Property parcelable with metadata, or null if unsupported.
    *
    * @see getCapabilities(), Property.aidl, PropertyType.aidl
    */
    @nullable Property getProperty(in String propertyKey);

    /** @} */
}




