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
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.OutputPortProperty;
import com.rdk.hal.PropertyValue;

/**
 * @brief     Listener interface for audio output port events.
 * @details   Provides callbacks for changes in port connection state, supported formats,
 *            output format changes, state transitions, and feature support (e.g., Dolby Atmos).
 *            Registered by clients interested in monitoring real-time output port events.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
oneway interface IAudioOutputPortListener {

    /**
     * @brief     Called when a dynamic property value changes.
     * @details   Fires for any property whose value changes after the listener
     *            was registered. Common change sources:
     *            <ul>
     *              <li><b>CONNECTION_STATE</b> — physical hot-plug / hot-unplug
     *                  events (HDMI cable insert/remove, ARC/eARC negotiation,
     *                  Bluetooth A2DP connect/disconnect). The HAL fires this
     *                  callback whenever the underlying connection transitions
     *                  between any two ConnectionState values
     *                  (UNKNOWN / DISCONNECTED / CONNECTED / PENDING / FAULT).
     *                  Clients should not poll CONNECTION_STATE — register a
     *                  listener instead.</li>
     *              <li><b>OUTPUT_FORMAT</b> — when the active format changes
     *                  (e.g. AUTO mode resolves to a different codec after
     *                  EDID/CEC re-negotiation).</li>
     *              <li><b>VOLUME / MUTE</b> — when changed by another component
     *                  (e.g. system audio service adjusting per-port master).</li>
     *              <li><b>SUPPORTED_AUDIO_FORMATS / DOLBY_ATMOS_SUPPORT</b> —
     *                  when the connected sink's capability set changes
     *                  (e.g. different AVR plugged in, eARC handshake completes).</li>
     *            </ul>
     *
     *            On disconnect (CONNECTION_STATE → DISCONNECTED) any in-flight
     *            audio routed to this port is silently dropped. The port
     *            remains open from the controller's perspective; the HAL does
     *            not implicitly close it. Middleware should decide whether to
     *            re-route to another port, pause playback, or wait for re-plug.
     *
     * @param[in] property   The OutputPortProperty that changed.
     * @param[in] newValue   The new PropertyValue.
     */
    void onPropertyChanged(in OutputPortProperty property, in PropertyValue newValue);
}
