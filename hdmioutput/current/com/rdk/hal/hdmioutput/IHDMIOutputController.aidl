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
     * Starts the HDMI output signal.
     *
     * This operation initiates signal transmission to the connected HDMI sink.
     * The output transitions from `READY` → `STARTING` → `STARTED`. In this state,
     * the port actively drives the HDMI signal, including video, audio, and InfoFrames.
     *
     * The `onHotPlugDetectStateChanged()` callback fires during this transition only
     * if the HPD line state changes (e.g., cable disconnect/reconnect during start).
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
     * Properties can be set in `READY` state (applied when `start()` is called) or
     * dynamically in `STARTED` state (applied immediately to the active signal).
     *
     * When applied in `STARTED` state, most properties update InfoFrames without disruption.
     * Properties requiring video mode changes (e.g., VIC) will assert/deassert AVMUTE
     * per HDMI specification, causing a brief display interruption.
     *
     * @param[in] property        Property key (@see Property).
     * @param[in] propertyValue   New value to apply.
     *
     * @returns boolean
     * @retval true     Property accepted and applied or queued.
     * @retval false    Invalid property key or value.
     *
     * @pre Output must be in State::READY or State::STARTED.
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
     * This returns the actively negotiated and running HDCP version on the HDMI link.
     * This may differ from the sink's advertised capabilities (from EDID) due to:
     * - HDCP repeaters in the signal chain forcing version downgrade
     * - Authentication failures requiring fallback to lower version
     * - Content that does not require HDCP protection
     *
     * @returns HDCPProtocolVersion enum value.
     * @retval HDCPProtocolVersion.UNDEFINED  No active HDCP session (unprotected content or authentication inactive).
     *
     * @see getHDCPStatus(), getHDCPReceiverVersion(), onEDID()
     */
    HDCPProtocolVersion getHDCPCurrentVersion();

    /**
     * Retrieves the HDCP protocol version reported by the sink.
     *
     * This returns the maximum HDCP version advertised by the connected sink device
     * as read from the sink's EDID or HDCP capability registers. This represents what
     * the sink is capable of, not what is currently active on the link.
     *
     * This may differ from `getHDCPCurrentVersion()` if HDCP repeaters, authentication
     * failures, or content requirements result in a lower version being negotiated.
     *
     * @returns HDCPProtocolVersion enum value.
     * @retval HDCPProtocolVersion.UNDEFINED  Sink capabilities not yet known (HPD deasserted or EDID not read).
     *
     * @see getHDCPStatus(), getHDCPCurrentVersion(), onEDID()
     */
    HDCPProtocolVersion getHDCPReceiverVersion();

    /**
     * Gets the current HDCP status of the HDMI link.
     *
     * Indicates whether HDCP authentication has occurred and whether it succeeded.
     * Use this in combination with `getHDCPCurrentVersion()` to understand the full
     * HDCP authentication state.
     *
     * @returns HDCPStatus enum value indicating authentication state.
     * @retval HDCPStatus.UNKNOWN  No sink present or HDCP state not yet determined.
     *
     * @see getHDCPCurrentVersion(), getHDCPReceiverVersion(), onHDCPStatusChanged()
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
