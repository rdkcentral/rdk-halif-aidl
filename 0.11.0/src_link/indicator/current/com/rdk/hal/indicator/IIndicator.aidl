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
package com.rdk.hal.indicator;
import com.rdk.hal.indicator.State;
import com.rdk.hal.indicator.Capabilities;

/**
 * /**
 * * @brief Indicator HAL interface.
 * *
 * * Defines the Hardware Abstraction Layer (HAL) interface for indicator services.
 * * @author Luc Kennedy-Lamb
 * * @author Peter Stieglitz
 * * @author Douglas Adler
 * * @author Gerald Weatherup
 * */

@VintfStability
interface IIndicator
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "Indicator";

    /**
     * Gets the capabilities of the indicator service.
     *
     * @returns Capabilities The capabilities parcelable of the indicator service.
     */
    Capabilities getCapabilities();

    /**
     * Sets a new indicator state.
     *
     * @param[in] state An indicator state to be set.
     * @returns boolean Returns `true` if the state was set successfully, `false` otherwise.
     */
    boolean set(in State state);

    /**
     * Gets the current indicator state.
     *
     * @returns State The current indicator state.
     */
    State get();
}