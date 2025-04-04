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
     * 
     * TODO: Create state diagrams for IHDMIInput and the HDCPStatus state machines.
     * TODO: Document in CEC how it uses the HDMIInput ports.
     * Diagram to show hot plug scenario - what events occurs and what action by RDK MW.
     * 
     * Diagram on RDK MW init
     *   1. Get all IHDMIInput interfaces.
     *   2. For each port, get the default EDID, modify and setEDID().
     *   3. For each port, open(...) to get controller interface.
     *   4. When it needs to be viewed
     *      4.1 Attach HDMI input as video source to video plane.
     *      4.2 Call IHDMIInputController.start() for AV to flow.
     *   5. When it needs to be stopped viewed
     *      5.1 Call IHDMIInputController.stop() for AV to flow.
     *      5.1 Deattach HDMI input as video source from video plane.
     *   6. Switching HDMI version.
     *   7. Add/remove ALLM support.
     *   7. Add/remove VRR support.
     */

    /**
     * Requirements
     * HAL.HDMIINPUT.1. No re-auth expected on a VIC or color mode switch.
     * HAL.HDMIINPUT.2. AVMUTE shall be adhered to by blanking the AV when asserted.
     * HAL.HDMIINPUT.3. SVP when HDCP is engaged.
     * HAL.HDMIINPUT.4. Starts in CLOSED state which is powered down, but CEC remains active.
     * HAL.HDMIINPUT.5. Until an EDID is set, HPD is unasserted, port is unpowered and CEC is disabled.
     */

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
     * When started, video from the HDMI input port can be mapped to a video plane and audio is mixed.
     * 
     * The HDMI input must be in a `READY` state before it can be started.
     * If successful the HDMI output transitions to a `STARTING` state and then a `STARTED` state.
     * 
     * The `IHDMIInputControllerListener.onSignalStateChanged()` callback is always fired during
     * the `STARTING` state to indicate the current signal state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     * 
     * @pre The resource must be in State::READY.
     * 
     * @see stop(), IHDMIInput.open()
     */
    void start();
 
    /**
    * Stops the HDMI input.
    *
    * @exception binder::Status EX_ILLEGAL_STATE If the resource is not in the `STARTED` state.
    *
    * @pre The resource must be in the `STARTED` state.
    *
    * @see start(), IHDMIInput.close()
    */
    void stop();

    /**
     * Sets a property.
     * 
     * Properties may be set in the `READY` state to take effect once started or in the `STARTED` state
     * where they are dynamically applied to the HDMI input port.
     *
     * @param[in] property              The key of a property from the Property enum.
     * @param[in] propertyValue         Holds the value to set.
     *
     * @returns boolean
     * @retval true     The property was successfully set.
     * @retval false    Invalid property key or value.
     *
     * @see setPropertyMulti(), getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
     * Sets multiple properties.
     * 
     * Properties may be set in the `READY` state to take effect once started or in the `STARTED` state
     * where they are dynamically applied to the HDMI input port.
     *
     * @param[in] propertyKVList        Array of key value pairs of properties.
     *
     * @returns boolean
     * @retval true     The property was successfully set.
     * @retval false    Invalid property key or value.
     *
     * @see setProperty(), getProperty()
     */
    boolean setPropertyMulti(in PropertyKVPair[] propertyKVList);

    /**
     * Gets the current authenticated HDCP version which was negotiated with the HDMI source device (HDCP transmitter).
     *
     * If HDCP has not yet been authenticated then `HDCPProtocolVersion.UNDEFINED` is returned.
     *
     * @returns HDCPProtocolVersion
     *
     * @see getHDCPStatus(), IHDMIInputControllerListener.onHDCPStatusChanged()
     */
    HDCPProtocolVersion getHDCPCurrentVersion();

    /**
     * Gets the HDCP status.
     *
     * If HDCP is not in use, then `HDCPStatus.UNKNOWN` is returned.
     *
     * @returns HDCPStatus
     *
     * @see getHDCPCurrentVersion(), IHDMIInputControllerListener.onHDCPStatusChanged()
     */
    HDCPStatus getHDCPStatus();
    
    /**
     * Gets the last received source product description (SPD) InfoFrame.
     *
     * @returns InfoFrame data byte array or empty array if no InfoFrame has been received since the last device was connected or started.
     *
     * @see IHDMIInputControllerListener.onSPDInfoFrame()
     */
    byte[] getSPDInfoFrame();

}
