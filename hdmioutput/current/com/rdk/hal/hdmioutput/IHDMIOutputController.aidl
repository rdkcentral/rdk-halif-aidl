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
 *     http://www.apache.org/licenses/LICENSE-2.0
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
 *
 *  Provides lifecycle management and low-level control of HDMI signal generation.
 *  This interface is used after a successful `open()` to configure output parameters,
 *  initiate/stop signalling, and query HDCP state and InfoFrames.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
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
     * Starts the HDMI output signal.
     *
     * This operation initiates signal transmission to the connected HDMI sink.
     * The output transitions from `READY` → `STARTING` → `STARTED`. In this state,
     * the port actively drives the HDMI signal, including video, audio, and InfoFrames.
     *
     * Callbacks such as `onHotPlugDetectStateChanged()` may fire during transition
     * to reflect sink connection status.
     *
     * If `start()` is called when not in `READY`, an `EX_ILLEGAL_STATE` exception is thrown.
     *
     * @exception binder::Status EX_ILLEGAL_STATE  HDMI output is not in READY state.
     *
     * @pre Must be in State::READY
     *
     * @see stop(), IHDMIOutput.open()
     */
    void start();

    /**
     * Stops the HDMI output signal.
     *
     * The output transitions from `STARTED` → `STOPPING` → `READY`. Video/audio output
     * is disabled, and downstream sinks receive an inactive signal. This allows the client
     * to reconfigure properties before restarting output.
     *
     * If `stop()` is called outside of the `STARTED` state, an `EX_ILLEGAL_STATE` is raised.
     *
     * @exception binder::Status EX_ILLEGAL_STATE  HDMI output is not in STARTED state.
     *
     * @pre Must be in State::STARTED
     *
     * @see start(), IHDMIOutput.close()
     */
    void stop();

    /**
     * Queries the current Hot Plug Detect (HPD) line state.
     *
     * This reflects whether a valid sink device is physically connected to the HDMI output.
     * HPD deassertion typically indicates cable disconnect or sink power loss.
     *
     * @returns boolean
     * @retval true     HPD is asserted — sink is connected and powered.
     * @retval false    HPD is deasserted — no active sink detected.
     *
     * @see IHDMIOutputControllerListener.onHotPlugDetectStateChanged()
     */
    boolean getHotPlugDetectState();

    /**
     * Sets a property on the HDMI output.
     *
     * Properties can be applied while in `READY` (queued for next `start()`) or
     * dynamically in `STARTED` (applied live, depending on implementation).
     *
     * Setting a property outside of valid states may result in undefined behavior.
     *
     * @param[in] property        Property key (@see Property).
     * @param[in] propertyValue   New value to apply.
     *
     * @returns boolean
     * @retval true     Property accepted and applied or queued.
     * @retval false    Invalid property key or value.
     *
     * @see setPropertyMulti(), getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
     * Sets multiple properties on the HDMI output.
     *
     * Same semantics as `setProperty()`, but applies a batch of key-value pairs.
     * Invalid keys or values result in the full operation failing (fail-fast).
     *
     * @param[in] propertyKVList  Array of property key-value pairs.
     *
     * @returns boolean
     * @retval true     All properties were valid and applied.
     * @retval false    At least one invalid property in the array.
     *
     * @see setProperty(), getProperty()
     */
    boolean setPropertyMulti(in PropertyKVPair[] propertyKVList);

    /**
     * Retrieves the currently authenticated HDCP protocol version.
     *
     * This represents the negotiated HDCP version after successful authentication.
     * If HDCP is not active, `HDCPProtocolVersion.UNDEFINED` is returned.
     *
     * @returns HDCPProtocolVersion
     *
     * @see getHDCPStatus(), getHDCPReceiverVersion()
     */
    HDCPProtocolVersion getHDCPCurrentVersion();

    /**
     * Retrieves the HDCP protocol version reported by the sink.
     *
     * This may differ from the currently authenticated version. If the sink’s
     * capabilities are not yet known, `HDCPProtocolVersion.UNDEFINED` is returned.
     *
     * @returns HDCPProtocolVersion
     *
     * @see getHDCPStatus(), getHDCPCurrentVersion()
     */
    HDCPProtocolVersion getHDCPReceiverVersion();

    /**
     * Gets the current HDCP status of the HDMI link.
     *
     * Indicates whether authentication has occurred and whether it succeeded.
     * If no sink is present or powered, the status will be `HDCPStatus.UNKNOWN`.
     *
     * @returns HDCPStatus
     *
     * @see getHDCPCurrentVersion(), getHDCPReceiverVersion()
     */
    HDCPStatus getHDCPStatus();

    /**
     * Sets the Source Product Description (SPD) InfoFrame payload.
     *
     * The InfoFrame is inserted into HDMI signalling when the output is active.
     * Passing null disables the SPD InfoFrame.
     *
     * The default behavior is to not transmit SPD unless explicitly configured.
     *
     * @param[in] spdInfoFrame    SPD metadata or null to disable.
     *
     * @pre Output must be in State::READY or State::STARTED.
     *
     * @see getSPDInfoFrame()
     */
    void setSPDInfoFrame(in @nullable SPDInfoFrame spdInfoFrame);

    /**
     * Gets the current Source Product Description (SPD) InfoFrame payload.
     *
     * If SPD has not been set, returns null.
     *
     * @returns SPDInfoFrame
     * @retval null    No SPD InfoFrame is currently configured.
     *
     * @pre Output must be in State::READY or State::STARTED.
     *
     * @see setSPDInfoFrame()
     */
    @nullable SPDInfoFrame getSPDInfoFrame();
}
