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
import com.rdk.hal.hdmiinput.HDCPStatus;
import com.rdk.hal.hdmiinput.HDCPProtocolVersion;

/** 
 *  @brief     Controller callbacks listener interface from HDMI input.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
oneway interface IHDMIInputControllerListener
{
    /**
     * Device connection state event notification.
     * 
     * Debouncing is peformed by the HAL and must be in a stable state before firing the event.
     * Always fires to reflect the current state during the `OPENING` state transition.
     *
     * @param[in] state     Reflects the device connection state.
     */
    void onConnectionStateChanged(in boolean state);

    /** 
     * Always fires to reflect the current signal state during the `STARTING` state transition.
     * 
     * @param[in] signalState   The signal state.
     */
    void onSignalStateChanged(in SignalState signalState);

    /**
     * Video format change notification.
     * 
     * Fires to reflect a change in the video format from the HDMI source device.
     *
     * @param[in] vic       The VIC code.
     */
    void onVideoFormatChanged(in VIC vic);

    /**
     * Variable refresh rate change notification.
     *
     * Fires to reflect a change in the VRR/FVA signalling from the source device
     * decoded from the received Video Timing Extended Metadata (VTEM).
     * 
     * When the VTEM is no longer received (EM timeout condition) then this
     * callback fires with vrrActive=false, M_CONST=false, fastVActive=false, frameRate=0.0.
     * 
     * The `frameRate` could vary on a frame by frame basis, but this callback shall not
     * fire at more than 2Hz.
     *
     * @param[in] vrrActive     When true, VRR is active.
     * @param[in] M_CONST       When true, M_CONST VRR is active.
     * @param[in] fastVActive   When true, FVA is active.
     * @param[in] frameRate     The latest frame rate calculated while VRR is active.
     */
    void onVRRChanged(in boolean vrrActive, boolean M_CONST, in boolean fastVActive, double frameRate);

    /**
     * Auxilliary Video Information (AVI) InfoFrame event.
     * 
     * The event fires on first received InfoFrame after the HDMI input port is in
     * in a STARTED state, after a device connection or if the InfoFrame changes.
     *
     * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
     */
    void onAVIInfoFrame(in byte[] data);

    /**
     * Audio InfoFrame event.
     *
     * The event fires on first received InfoFrame after the HDMI input port is in
     * in a STARTED state, after a device connection or if the InfoFrame changes.
     *
     * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
     */
    void onAudioInfoFrame(in byte[] data);

    /**
     * Source Product Description (SPD) InfoFrame event.
     *
     * The event fires on first received InfoFrame after the HDMI input port is in
     * in a STARTED state, after a device connection or if the InfoFrame changes.
     *
     * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
     */
    void onSPDInfoFrame(in byte[] data);

    /**
     * MPEG Source (MS) InfoFrame event.
     *
     * The event fires on first received InfoFrame after the HDMI input port is in
     * in a STARTED state, after a device connection or if the InfoFrame changes.
     *
     * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
     */
    //void onMPEGSourceInfoFrame(in byte[] data); - TOO FAST as it can update on every frame.  Also not recommended.

    /**
     * NTSC VBI Source InfoFrame event.
     *
     * The event fires on first received InfoFrame after the HDMI input port is in
     * in a STARTED state, after a device connection or if the InfoFrame changes.
     *
     * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
     */
    // void onNTSCVBIInfoFrame(in byte[] data); -TOO FAST as it can update on every frame

    /**
     * DRMIF - Dynamic Range and Mastering InfoFrame
     * Contains SDR/HDR EOTF and static metadata.
     * Only fires on first received, on change to previous info frame or after a start().
     */
    
    /**
     * Dynamic Range and Mastering (DRM) InfoFrame event.
     *
     * The event fires on first received InfoFrame after the HDMI input port is in
     * in a STARTED state, after a device connection or if the InfoFrame changes.
     *
     * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
     */
    void onDRMInfoFrame(in byte[] data);
    
    // void onHDRDynamicMetadataExtendedInfoFrame(in SPDInfoFrame spdInfoFrame); - TOO FAST as it can update on every frame.
    // NOT NEEDED - void onGraphicsOverlayFlagExtendedInfoFrame(in SPDInfoFrame spdInfoFrame);

    /**
     * Vendor Specific InfoFrame (VSIF) event.
     *
     * The event fires on first received InfoFrame after the HDMI input port is in
     * in a STARTED state, after a device connection or if the InfoFrame changes.
     * 
     * VSIF are unique only when the OUI is included in the data matching.
     * e.g. Dolby VSIF and HF-VSIF are delivered as separate InfoFrames.
     *
     * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
     */
    void onVendorSpecificInfoFrame(in byte[] data);

    /**
     * Will be `HDCPProtocolVersion.UNDEFINED` protocol version until first authentication.
     */
    void onHDCPStatusChanged(in HDCPStatus hdcpStatus, in HDCPProtocolVersion hdcpProtocolVersion);
}
