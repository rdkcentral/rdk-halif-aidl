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

import com.rdk.hal.hdmioutput.HDCPStatus;
import com.rdk.hal.hdmioutput.HDCPProtocolVersion;

/**
 *  @brief     Controller callbacks listener interface from HDMI output.
 *
 *  Receives controller-side notifications from the HDMI output subsystem regarding
 *  hotplug events, EDID acquisition, HDCP authentication, and frame rate transitions.
 *
 *  These events are generated from the HDMI controller and are always delivered
 *  on a one-way, async interface. The receiving client must respond in a non-blocking way.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
@VintfStability
oneway interface IHDMIOutputControllerListener
{
    /**
     * Device hotplug state changed event.
     *
     * This event reflects a change in the HDMI Hot Plug Detect (HPD) line state.
     *
     * - **ALWAYS** fired during the `OPENING` transition (CLOSED → READY), even if the
     *   HPD state has not changed, to communicate the initial sink connection state.
     * - **Only on actual HPD changes** during `STARTING`, `STARTED`, and `STOPPING` states
     *   (i.e., when cable is physically connected/disconnected).
     * - Debouncing is handled internally by the HAL; the state reported here is stable.
     *
     * @param[in] state  True if the HPD line is asserted (sink connected), false otherwise.
     *
     * @see IHDMIOutput.open()
     */
    void onHotPlugDetectStateChanged(in boolean state);

    /**
     * Frame rate changed event.
     *
     * Triggered after a new frame rate has been applied to the HDMI output.
     * This indicates that video mode configuration has completed and that
     * any display timing changes are now live.
     *
     * Must be fired only after AVMUTE is cleared — i.e., when content can be visible.
     * This is especially important for native frame rate matching with OTT apps like Netflix.
     *
     * This callback is paired with client-facing logic such as `videoOutputStatusChanged`.
     *
     * @see Native Frame Rate handling in app middleware (e.g., Netflix).
     */
    void onFrameRateChanged();

    /**
     * HDCP status change event.
     *
     * Notifies clients about changes to the HDCP authentication state or negotiated version.
     * May be triggered due to cable changes, EDID updates, power cycling, or key revocation.
     *
     * This callback is expected to cover all transitions: from unauthenticated to authenticated,
     * failure cases, or changes in protocol version (e.g., 1.x vs 2.x).
     *
     * @param[in] hdcpStatus           Current HDCP status of the output link.
     * @param[in] hdcpProtocolVersion  Protocol version negotiated with the sink.
     *
     * @see getHDCPStatus()
     * @see getHDCPCurrentVersion()
     */
    void onHDCPStatusChanged(in HDCPStatus hdcpStatus, in HDCPProtocolVersion hdcpProtocolVersion);

    /**
     * E-EDID read event.
     *
     * Fired when the full Extended EDID (E-EDID) block has been successfully retrieved
     * from the connected HDMI sink.
     *
     * - This event is guaranteed to fire after `onHotPlugDetectStateChanged(true)`
     *   if a valid and powered sink is detected.
     * - This provides full EDID blocks, not just the base 128-byte block.
     * - EDID may be used to extract sink capabilities, such as supported video formats,
     *   audio formats, HDR support, and vendor-specific extensions.
     *
     * @param[in] edid  Byte array representing the full E-EDID data as read from the sink.
     *
     * @pre HDMI output must be in `READY` or `STARTED` state.
     *
     * @see IHDMIOutput.open()
     * @see CTA-861 specification
     */
    void onEDID(in byte[] edid);
}
