/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast.frontend;

import com.rdk.hal.broadcast.frontend.LnbTone;
import com.rdk.hal.broadcast.frontend.LnbVoltage;

/**
 * LNB controller interface.
 *
 * Handles control operations for a Low-Noise Block downconverter (LNB), including voltage control, tone control, and
 * DiSEqC signalling. Obtained via IFrontend.openLnb().
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
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
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the voltage value is not supported.
     *
     * @param[in] voltage The voltage to set.
     */
    void setVoltage(in LnbVoltage voltage);

    /**
     * Set the LNB tone.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the tone value is not supported.
     *
     * @param[in] tone The tone mode to set.
     */
    void setTone(in LnbTone tone);

    /**
     * Get the overload state of the LNB controller.
     *
     * @returns True if the LNB power line is overloaded (e.g. possible short circuit on the LNB voltage line), false
     *          otherwise.
     */
    boolean isOverloaded();

    /**
     * Send a DiSEqC (Digital Satellite Equipment Control) command.
     *
     * Sends a DiSEqC command to the connected LNB equipment as specified by the EUTELSAT Bus Functional Specification
     * Version 4.2. Blocks until the entire command has been transmitted.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the command is empty or malformed.
     *
     * @param[in] command The DiSEqC command bytes to transmit.
     */
    void sendDiseqc(in byte[] command);
}
