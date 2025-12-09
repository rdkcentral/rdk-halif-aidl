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
import com.rdk.hal.hdmiinput.Property;
import com.rdk.hal.hdmiinput.PropertyKVPair;
import com.rdk.hal.hdmiinput.HDCPProtocolVersion;
import com.rdk.hal.hdmiinput.HDCPStatus;
import com.rdk.hal.PropertyValue;

/** 
 *  @brief     HDMI Input Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */


@VintfStability
interface IHDMIInputController
{
    /**
     * Gets the current connection state for a device attached to the HDMI input port.
     *
     * @returns boolean
     * @retval true         A device is connected.
     * @retval false        No device is connected.
     *
     * @see IHDMIInputControllerListener.onConnectionStateChanged()
     */
    boolean getConnectionState();

    /**
     * Starts the HDMI input.
     *
     * When started, video from the HDMI input port can be mapped to a video plane and the
     * associated audio can be mixed into the system audio path.
     *
     * The HDMI input must be in a `READY` state before it can be started.
     * If successful, the HDMI input transitions to a `STARTING` state and then to a `STARTED` state.
     *
     * During the `STARTING` state, the `IHDMIInputControllerListener.onSignalStateChanged()`
     * callback is always fired at least once to indicate the current HDMI signal state
     * (e.g. no signal, unstable, locked).
     *
     * When the HDMI input is in the `STARTED` state and a valid sink configuration is present,
     * the HPD line for the corresponding HDMI input port is asserted towards the source.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     *     Thrown if the resource is not in State::READY.
     *
     * @pre The resource must be in State::READY.
     *
     * @see stop(), IHDMIInput.open()
     */
    void start();
 
    /**
     * Stops the HDMI input.
     *
     * The HDMI input must be in the `STARTED` state before it can be stopped.
     * If successful, the HDMI input transitions to a `STOPPING` state and then to a `READY` state.
     *
     * During the `STOPPING` state, the `IHDMIInputControllerListener.onSignalStateChanged()`
     * callback may be fired to indicate signal changes as the port is being stopped.
     *
     * @exception binder::Status EX_ILLEGAL_STATE If the resource is not in the `STARTED` state.
     *
     * @pre The resource must be in the `STARTED` state.
     *
     * @see start(), IHDMIInput.close()
     */
    void stop();

    /**
     * Gets the current authenticated HDCP version which was negotiated with the HDMI source device (HDCP transmitter).
     *
     * The EDID defined in `edid` is set for the HDMI input port.
     * This function can only be called when the interface is open and in the `READY` state.
     * 
     * The RDK middleware is responsible for providing an EDID that only reflects the
     * known capabilities of this HDMI input port.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     *     Thrown if the resource is not in State::READY
     * 
     * @param[in] edid  EDID data as a byte array. Must be valid and standards-compliant (typically 128 or 256 bytes).
     * 
     * @return boolean
     * @retval true     The EDID was set successfully.
     * @retval false    Indicates an error condition (e.g., resource not available, invalid state, or parameter validation failure).
     *
     * @see getEDID(), getCapabilities()
     */
    boolean setEDID(in byte[] edid);
}
