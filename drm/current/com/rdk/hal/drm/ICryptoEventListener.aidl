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

/** 
 *  @brief     Events callbacks listener interface from Crypto.
 *  @author    TBD
 */

@VintfStability
oneway interface ICryptoEventListener {

    /**
     * @brief Callback when the Crypto resource has raised an error.
     *
     * @param[in] errorCode 		    An error code value.
     * @param[in] vendorErrorCode  	    A vendor specific error code.
     */
    void onError(in int errorCode, in int vendorErrorCode);
 
    /**
     * @brief Callback when the Crypto resource has transitioned to a new state.
     *
     * @param[in] oldState	            The state that the resource has transitioned from.
     * @param[in] newState              The new state that the resource has transitioned to.
     */
    void onStateChanged(in int oldState, in int newState);
}
