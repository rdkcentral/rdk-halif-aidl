/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.farfieldvoice;
import com.rdk.hal.farfieldvoice.ListeningMode;

/**
 *  @brief     Far Field Voice service capabilities.
 *
 *  Static, platform-level capabilities advertised by the FFV HAL. Values are
 *  fixed for the lifetime of a given platform image and do not change between
 *  calls to `IFarFieldVoice.getCapabilities()`.
 *
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
parcelable Capabilities
{
    /**
     * Array of channel types supported by this platform (e.g. "KEYWORD" =
     * Keyword Audio channel). Channel-type identifiers are HAL-defined; vendors
     * must use the standard identifiers — vendor-specific channel types are
     * not permitted in the AIDL surface.
     */
    @utf8InCpp String[] channelTypes;

    /**
     * Number of microphone inputs (Microphones Audio channel count).
     */
    int microphoneChannelCount;

    /**
     * Listening modes the platform supports. Subsequent calls to
     * `IFarFieldVoiceController.setListeningMode()` must use one of these.
     * Not every platform supports every mode — a low-power SoC may only
     * support `KEYWORD_ALERT` and `POWERED_OFF`, for example.
     *
     * @see ListeningMode
     */
    ListeningMode[] supportedListeningModes;
}
