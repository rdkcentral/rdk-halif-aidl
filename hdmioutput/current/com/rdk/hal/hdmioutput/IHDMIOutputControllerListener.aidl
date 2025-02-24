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
import com.rdk.hal.hdmioutput.HDCPStatus;
import com.rdk.hal.hdmioutput.HDCPProtocolVersion;

/** 
 *  @brief     Controller callbacks listener interface from HDMI output.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
oneway interface IHDMIOutputControllerListener 
{
    /** 
     * Always fires to reflect the state during `OPENING` state transition.
     * Fires on any HPD state change while `STARTED`.
     * Debouncing is peformed by HAL - must be in a stable state. 
     */
    void onHotPlugDetectStateChanged(in boolean state);

    /** 
     * Always fires to reflect the state during `OPENING` state transition.
     * Fires on any RX sense state change while `STARTED`.
     * Debouncing is peformed by HAL - must be in a stable state. 
     * For PHY level detection of a connected sink device (can be used if HPD is unreliable)
     * TODO: Consider using this under-the-hood in HAL, and wrap up into HPD state change. - AmitP is checking.
     */
//    void onRxSenseStateChanged(in boolean state);
// Recommend that RxSense can be used to help drive EDID reading and HDCP negotiation.

    /**
     * Fired AFTER the frame rate has been changed by a VIC code assignment.
     * Used to event back to Netflix for FRM - see videoOutputStatusChanged and Native Frame Rate in Netflix docs. 
     * Must be fired after the AVMUTE has been cleared after a VIC change.
     */
    void onFrameRateChanged();

    /**
     * Will be `HDCPProtocolVersion.UNDEFINED` protocol version until first authentication.
     */
    void onHDCPStatusChanged(in HDCPStatus hdcpStatus, in HDCPProtocolVersion hdcpProtocolVersion);

    /**
     * Callback once the E-EDID of the connected HDMI sink device has been fully read.
     *
     * The HDMI output must be in a `READY` or `STARTED` state with a sink device connected.
     * The E-EDID may be dynamically refreshed in response to XXXX while in a connected state.
     *
     * @param[in] edid          Array of bytes representing the full list of E-EDID data blocks.
     *
     * @pre Resource is in State::READY or State::STARTED state.
     *
     * @see IHDMIOutput.open()
     * @see CTA-861-I
     */

    /**
     * Can be called at any time after `onHotPlugDetectStateChanged(true)`.
     */
    void onEDID(in byte[] edid);

}
