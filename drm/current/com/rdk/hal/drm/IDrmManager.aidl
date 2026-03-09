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
import com.rdk.hal.drm.IDrm;
import com.rdk.hal.drm.ICrypto;
 
/** 
 *  @brief     DRM Manager HAL interface.
 *  @author    TBD
 */

@VintfStability
interface IDrmManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "drmmanager";

    /**
     * @brief Get all DRM resource IDs.
     * 
     * The list of DRM resources is static in the system and does not change
     * between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IDrm.Id[] Array of DRM resource identifiers.
     */
    IDrm.Id[] getDrmIds();

    /**
     * @brief Gets a DRM resource interface.
     *
     * @param[in] drmResourceId     The ID of the DRM resource.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IDrm interface which can be null if the resource ID is invalid.
     */
    @nullable IDrm getDrm(in IDrm.Id drmResourceId);

    /**
     * @brief Get all Crypto resource IDs.
     * 
     * The list of Crypto resources is static in the system and does not change
     * between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns ICrypto.Id[] Array of Crypto resource identifiers.
     */
    ICrypto.Id[] getCryptoIds();

    /**
     * @brief Gets a Crypto resource interface.
     *
     * @param[in] cryptoResourceId     The ID of the Crypto resource.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns ICrypto interface which can be null if the resource ID is invalid.
     */
    @nullable ICrypto getCrypto(in ICrypto.Id cryptoResourceId);
}
