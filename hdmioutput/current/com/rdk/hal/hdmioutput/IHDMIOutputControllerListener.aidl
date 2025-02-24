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
     * Device hotplug state changed event.
     * 
     * Always fires to reflect the state during `OPENING` state transition.
     * Fires on any HPD state change while `STARTED`.
     * Debouncing is peformed by HAL - must be in a stable state. 
     */
    void onHotPlugDetectStateChanged(in boolean state);

    /**
     * Frame rate changed event.
     * 
     * The callback fires after the frame rate has been changed on the HDMI output port.
     * Also used to propogate an event back to Netflix for native frame rate support.
     * Must be fired after the AVMUTE has been cleared after a frame rate change.
     * @see videoOutputStatusChanged and Native Frame Rate in Netflix docs. 
     */
    void onFrameRateChanged();

    /**
     * HDCP status change event with protocol version information.
     *
     * @param[in] hdcpStatus            The HDCP status.
     * @param[in] hdcpProtocolVersion   The HDCP protocol version.
     */
    void onHDCPStatusChanged(in HDCPStatus hdcpStatus, in HDCPProtocolVersion hdcpProtocolVersion);

    /**
     * Event callback for the E-EDID of the connected HDMI sink device after it has been read.
     *
     * The HDMI output must be in a `READY` or `STARTED` state with a sink device connected.
     * An E-EDID is expected to be read and provided in this callback after
     * `onHotPlugDetectStateChanged(true)` has been reported.
     *
     * @param[in] edid          Array of bytes representing the full set of E-EDID data blocks.
     *
     * @pre Resource is in State::READY or State::STARTED state.
     *
     * @see IHDMIOutput.open()
     * @see CTA-861
     */
    void onEDID(in byte[] edid);

}
