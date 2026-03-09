/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.drm;
import com.rdk.hal.drm.Capabilities;
import com.rdk.hal.drm.IDrmController;
import com.rdk.hal.drm.IDrmControllerListener;
import com.rdk.hal.drm.IDrmEventListener;
import com.rdk.hal.PropertyValue;

/** 
 *  @brief     DRM resource interface.
 *  @author    TBD
 */

@VintfStability
interface IDrm
{
    /** DRM resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */    
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /**
     * @brief Gets the capabilities of the DRM service.
     * 
     * The returned value is not allowed to change between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();
    /**
     * @brief Gets a property.
     *
     * @param[in] property              The key of a property.
     *
     * @returns PropertyValue or null if the property key is unknown.
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property value.
     */
    @nullable PropertyValue getProperty(in int property);

    /**
     * @brief Gets the DRM controller interface.
     *
     * @param[in] listener              The controller listener callback interface.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IDrmController interface.
     */
    IDrmController getController(in IDrmControllerListener listener);

    /**
     * @brief Registers an event listener to receive DRM events.
     *
     * @param[in] listener              The event listener callback interface.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    void registerEventListener(in IDrmEventListener listener);
    
}
