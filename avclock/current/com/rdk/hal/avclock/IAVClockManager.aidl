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
package com.rdk.hal.avclock;
import com.rdk.hal.avclock.IAVClock;

/** 
 *  @brief     AV Clock Manager HAL interface.
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
interface IAVClockManager 
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "AVClockManager";

    /**
	 * Gets the list of platform AV Clock IDs.
     * 
     * @returns IAVClock.Id[]       Array of IDs.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IAVClockManager}} for exception handling behavior).
     *
     */
	IAVClock.Id[] getAVClockIds();   

    /**
     * Gets the AV Clock interface for a given ID.
     *
     * @param[in] avClockId	        The ID of the AV clock.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IAVClock or null if the `avClockId` is invalid.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IAVClockManager}} for exception handling behavior).
     */
    @nullable IAVClock getAVClock(in IAVClock.Id avClockId);
}
