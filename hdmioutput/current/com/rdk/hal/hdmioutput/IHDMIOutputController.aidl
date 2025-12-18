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
import com.rdk.hal.hdmioutput.Property;
import com.rdk.hal.hdmioutput.PropertyKVPair;
import com.rdk.hal.hdmioutput.SPDInfoFrame;
import com.rdk.hal.hdmioutput.HDCPStatus;
import com.rdk.hal.hdmioutput.HDCPProtocolVersion;
import com.rdk.hal.PropertyValue;

/** 
 *  @brief     HDMI Output Controller HAL interface.
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
interface IHDMIOutputController
{
    /** 
     * 
     * Host Information extracted by RDK MW
     *   - get entire EDID from HAL and parse in RDK MW
     *   - includes getting host display video aspect ration/dimensions
     *   - read HDR support
     *   - read pixel formats, YUV/RGB/422/420/444 etc.
     *   - HDMI/E-EDID version
     * 
     * TODO: 1. Read HDCP spec to look for states listed.
     *       2. Create state diagram.
     *		 3. How recover from auth failure?   Customer can go in-out of standby.  RDK could close+reopen HDMI output.
     * 
     * TODO: Document in CEC how it uses the new HDMIOutput event onEDID() event.
     * What about HDCP events??? https://www.eetimes.com/the-nuts-and-bolts-of-hdcp/
     * What happens if no HDMI sink device is attached - what are the refresh rates for graphics and video output sync?
     * Needs diagram to show compositor -> HDMI output and how aspect ratio and scaling occurs.
     * Diagram to show hot plug scenario - what events occurs and what action by RDK MW.  Clear and DRM content scenarios.
     */

    /**
     * Requirements
     * HAL.HDMIOUTPUT.1. No re-auth expected on a VIC or color mode switch.
     * HAL.HDMIOUTPUT.2. AVMUTE shall be asserted by HAL implementation, according the HDMI and HDCP specs.
     * HAL.HDMIOUTPUT.3. When output to a 4:3 aspect ratio sink display (using a VIC code of 4:3 aspect ratio), 
     *                   the 16:9 composited graphics and video shall be letterboxed inside the 4:3 output frame.  
     *                   AFD code XXX shall be set to indicate 16:9 in 4:3 frame.
     * HAL.HDMIOUTPUT.4. AUTO HDCP - immediately on device connection after open()
     *                   Define number of retries if negotiation protocol failures.
     *                   Define 2.x and 1.x negotation.
     *                   Always negotiate highest supported version.
     * HAL.HDMIOUTPUT.5. Playback/decryption.
     * HAL.HDMIOUTPUT.6. Key Revocation List for HDCP - vendor layer responsibility, updated only by firmware update. 
     *                   Handling SRMs delivered with content?
     */

    /**
	 * Starts the HDMI output.
     * 
     * The HDMI output must be in a `READY` state before it can be started.
     * If successful the HDMI output transitions to a `STARTING` state and then a `STARTED` state.
     * 
     * In a `STARTED` state the HDMI output port is enabled to drive an output signal capable of carrying audio, video and data frames.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::READY.
     * 
     * @see stop(), IHDMIOutput.open()
     */
    void start();
 
    /**
	 * Stops the HDMI output.
     * 
     * The HDMI output enters the `STOPPING` state where the output signal is disabled.
     * Once the HDMI output signal is disabled, the HDMI output enters the `READY` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     * 
     * @see start(), IHDMIOutput.close()
     */
    void stop();

    /**
     * Gets the current HPD line state.
     *
     * The current HDMI output hot plug detect state detects the presence of a HDMI sink
     * device.
     *
     * @return boolean
     * @retval true         The HPD line is asserted.
     * @retval boolean      The HPD line is deasserted.
     * 
     * @see start()
     */
    boolean getHotPlugDetectState();

    /**
     * Sets a property.
     * 
     * Properties may be set in the `READY` state to take effect once started or in the `STARTED` state
     * where they are dynamically applied to the current HDMI output signal.
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
     * where they are dynamically applied to the current HDMI output signal.
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
     * Gets the current authenticated HDCP version which was negotiated with the HDMI sink device (HDCP receiver).
     *
     * If HDCP has not yet been authenticated then `HDCPProtocolVersion.UNDEFINED` is returned.
     *
     * @returns HDCPProtocolVersion
     *
     * @see getHDCPStatus(), getSinkHDCPVersion()
     */
    HDCPProtocolVersion getHDCPCurrentVersion();

    /**
     * Gets the HDCP version reported by the HDMI sink device (HDCP receiver).
     *
     * If the HDCP receiver version is not yet known then `HDCPProtocolVersion.UNDEFINED` is returned.
     *
     * @returns HDCPProtocolVersion
     *
     * @see getHDCPStatus(), getHDCPCurrentVersion()
     */
    HDCPProtocolVersion getHDCPReceiverVersion();

    /**
     * Gets the HDCP status.
     *
     * If HDCP is unable to be used, due to a disconnected or unpowered device then `HDCPStatus.UNKNOWN` is returned.
     *
     * @returns HDCPStatus
     *
     * @see getHDCPCurrentVersion(), getHDCPReceiverVersion()
     */
    HDCPStatus getHDCPStatus();
    
    /**
     * Sets the source product description (SPD) InfoFrame data.
     *
     * If set to null, then no SPD InfoFrame is transmitted.
     * The default is no SPD InfoFrame is defined or transmitted.
     *
     * @param[in] spdInfoFrame  SPD InfoFrame description.
     *
     * @pre The HDMI output must be in a `READY` or `STARTED` state.
     * 
     * @see getSPDInfoFrame()
     */
    void setSPDInfoFrame(in @nullable SPDInfoFrame spdInfoFrame);

    /**
     * Gets the source product description (SPD) InfoFrame data.
     *
     * If null is returned, then no SPD InfoFrame is defined.
     *
     * @return SPDInfoFrame
     *
     * @pre The HDMI output must be in a `READY` or `STARTED` state.
     *
     * @see setSPDInfoFrame()
     */
    @nullable SPDInfoFrame getSPDInfoFrame();
}
