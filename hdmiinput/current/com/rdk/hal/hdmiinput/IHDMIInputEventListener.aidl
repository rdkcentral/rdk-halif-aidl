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
import com.rdk.hal.hdmiinput.State;
import com.rdk.hal.hdmiinput.metrics.EpisodeResolved;
import com.rdk.hal.hdmiinput.metrics.EpisodeStarted;

/**
 *  @brief     Event callbacks listener interface from HDMI input.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IHDMIInputEventListener {
    /**
     Callback when the HDMI input has transitioned to a new state.
     *
     * @param[in] oldState      The state that the port has transitioned from.
     * @param[in] newState      The new state that the port has transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * EDID change notification.
     *
     * Fires when the EDID for the HDMI input port is changed via setEDID().
     *
     * @param[in] edid  The new EDID data as a byte array.
     */
    void onEDIDChange(in byte[] edid);

    /**
     * Raised once when an episode starts. onMetricEpisodeResolved() follows,
     * with the same Episode, when it ends.
     *
     * Episodes are the only metric events: nothing is raised per occurrence,
     * and per-occurrence figures are read with IHDMIInput.getMetrics().
     *
     * @param[in] event    Which episode started, and when.
     *
     * @see Episode, EpisodeStarted
     */
    void onMetricEpisodeStarted(in EpisodeStarted event);

    /**
     * Raised once when the episode reported by onMetricEpisodeStarted() ends.
     *
     * @param[in] event    Which episode ended, when, how long it lasted and
     * what it counted.
     *
     * @see Episode, EpisodeResolved
     */
    void onMetricEpisodeResolved(in EpisodeResolved event);
}
