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
package com.rdk.hal.broadcast.frontend;
import com.rdk.hal.broadcast.frontend.LnbTone;
import com.rdk.hal.broadcast.frontend.LnbVoltage;

/**
 * @brief LNB Controller interface.
 *
 * Handles control operations for a Low-Noise Block downconverter (LNB), including
 * voltage control, tone control, and DiSEqC signalling. Obtained via IFrontend.openLnb().
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 *
 * @see IFrontend.openLnb()
 */

@VintfStability
interface ILnbController {
    /**
     * Set the LNB voltage.
     *
     * Use LnbVoltage.NONE to turn off the LNB power.
     *
     * @param[in] voltage The voltage to set.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if the voltage value is not supported.
     */
    void setVoltage(in LnbVoltage voltage);

    /**
     * Set the LNB tone.
     *
     * @param[in] tone The tone mode to set.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if the tone value is not supported.
     */
    void setTone(in LnbTone tone);

    /**
     * Close the LNB controller.
     *
     * Cleans up all attached (hardware) resources and brings the LNB controller back into a
     * state where it can be opened again via IFrontend.openLnb().
     *
     * @exception binder::Status EX_ILLEGAL_STATE if the controller is already closed.
     *
     * @pre The resource must be in an open state.
     *
     * @see IFrontend.openLnb()
     */
    void close();
}
