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
package com.rdk.hal.hdmiinput;
import com.rdk.hal.hdmiinput.IHDMIInput;
import com.rdk.hal.hdmiinput.PlatformCapabilities;

/** 
 *  @brief     HDMI Input Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Amit Patel
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IHDMIInputManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "HDMIInputManager";

    /**
     * Gets the platform capabilities for HDMI inputs.
     *
     * This function can be called at any time.
     * The returned value is not allowed to change between calls.
     *
     * @returns PlatformCapabilities parcelable.
     */
    PlatformCapabilities getCapabilities();

    /**
	 * Gets the platform list of HDMI input IDs.
     * 
     * @returns IHDMIInput.Id[]
     */
	IHDMIInput.Id[] getHDMIInputIds();
 
    /**
	 * Gets a HDMI input interface.
     *
     * @param[in] hdmiInputId  The HDMI input port ID, must be one of the values returned by getHDMIInputIds().
     *
     * @returns IHDMIInput or null if the ID is invalid.
     */
    @nullable IHDMIInput getHDMIInput(in IHDMIInput.Id hdmiInputId);

}
