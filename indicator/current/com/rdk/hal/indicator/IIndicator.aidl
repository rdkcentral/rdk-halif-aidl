/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.indicator;
import com.rdk.hal.indicator.Capabilities;

/**
 * @brief Indicator HAL interface.
 *
 * Defines the Hardware Abstraction Layer (HAL) interface for indicator services.
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IIndicator
{
    /** Indicator resource ID type */
    @VintfStability
    parcelable Id {
        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities of this indicator instance.
     *
     * This function can be called at any time and returns the set of states
     * supported by this specific indicator instance. The returned value must
     * not change between calls.
     *
     * @returns Capabilities parcelable containing supported state strings.
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    Capabilities getCapabilities();

    /**
     * Sets a new indicator state.
     *
     * The state string must be one of the states listed in the capabilities
     * returned by getCapabilities(). Setting an unsupported state will fail.
     *
     * @param[in] state An indicator state string to be set.
     * @returns Success flag indicating whether state was set.
     * @retval true State was set successfully.
     * @retval false State is not supported or setting failed.
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid state string.
     */
    boolean set(in String state);

    /**
     * Gets the current indicator state.
     *
     * Returns the currently active state as a string.
     *
     * @returns Current indicator state string.
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    String get();
}
