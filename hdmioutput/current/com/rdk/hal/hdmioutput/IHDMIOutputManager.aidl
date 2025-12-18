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
package com.rdk.hal.hdmioutput;
import com.rdk.hal.hdmioutput.PlatformCapabilities;
import com.rdk.hal.hdmioutput.IHDMIOutput;

/** 
 *  @brief     HDMI Output Manager HAL interface.
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
interface IHDMIOutputManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "HDMIOutputManager";

    /**
     * Gets the platform capabilities for HDMI outputs.
     *
     * This function can be called at any time.
     * The returned value is not allowed to change between calls.
     *
     * @returns PlatformCapabilities parcelable.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IHDMIOutputManager}} for exception handling behavior).
     */
    PlatformCapabilities getCapabilities();

    /**
	 * Gets the platform list of HDMI output IDs.
     * 
     * @returns IHDMIOutput.Id[]
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IHDMIOutputManager}} for exception handling behavior).
     */
	IHDMIOutput.Id[] getHDMIOutputIds();
 
    /**
	 * Gets a HDMI output interface.
     *
     * @param[in] hdmiOutputId	The ID of the HDMI output port instance.
     *
     * @returns IHDMIOutput or null if the ID is invalid.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IHDMIOutputManager}} for exception handling behavior).
     */
    @nullable IHDMIOutput getHDMIOutput(in IHDMIOutput.Id hdmiOutputId);

}
