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
package com.rdk.hal.broadcast.ca;

import com.rdk.hal.broadcast.ca.CaCapabilities;

/**
 *  @brief     CA Slot HAL interface.
 *
 *  Represents a single Conditional Access (CA) slot on the platform.
 *  Obtain instances via IBroadcastManager.getCaSlot().
 *
 *  ### Exception Handling
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - **Success**: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - **Failure (Exception)**: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */
@VintfStability
interface ICaSlot {

    /** CA slot resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const long UNDEFINED = -1;

        /** The actual resource ID */
        long value;
    }

    /**
     * Get the ID of this CA slot.
     *
     * @returns Id the unique identifier for this CA slot.
     */
    Id getId();

    /**
     * Get the supported capabilities of this CA slot.
     *
     * @returns CaCapabilities the capabilities of this CA slot.
     */
    CaCapabilities getCapabilities();

    /**
     * Enable or disable power to the CA slot.
     *
     * @param[in] enabled   true to enable power, false to disable.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     */
    void setPower(in boolean enabled);
}
