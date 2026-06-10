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
import com.rdk.hal.audiomixer.OutputPortType;
import com.rdk.hal.audiomixer.OutputFormat;
import com.rdk.hal.audiomixer.AQProcessor;

/**
 * @brief    Capabilities for an audio output port.
 * Enumerates which properties can be set or queried for a given port,
 *           plus codec/format support and AQ processors.
 * @note     This structure is descriptive only. Property reads use
 *           IAudioOutputPort.getProperty(); property writes use
 *           IAudioOutputPortController.setProperty() (controller acquired via
 *           IAudioOutputPort.open()).
 */
@VintfStability
parcelable OutputPortCapabilities {

    /**
    * @brief Human-readable name or role for this output port (e.g., "HDMI", "SPDIF", "Speakers").
    * @details Required, declared per output port in hfp-audiomixer.yaml under
    *          outputPorts[].portName. Used for debugging, logging, and
    *          user-facing diagnostics. For programmatic type identification
    *          and policy branching, use `portType` instead.
    */
    String portName;

    /**
    * @brief Programmatic type of this output port.
    * @details Declared per output port in hfp-audiomixer.yaml under
    *          outputPorts[].portType. Middleware should branch on this enum
    *          (not on the string `portName`) when applying type-specific
    *          policy — e.g. transcode-to-AC3 only on SPDIF, hot-unplug
    *          handling only on HDMI/ARC/EARC, pairing flow only on BLUETOOTH.
    *
    *          Multiple ports of the same type may exist (e.g. two HDMI
    *          outputs); use `portName` to distinguish them.
    */
    OutputPortType portType;

    /**
     * List of property keys supported by this output port (see OutputPortProperty).
     * E.g., VOLUME, DELAY_MS, OUTPUT_FORMAT, etc.
     */
    OutputPortProperty[] supportedProperties;

    /**
     * List of supported output audio formats.
     */
    OutputFormat[] supportedOutputFormats;

    /**
     * List of AQ processor instances supported (first is default).
     */
    AQProcessor[] supportedAQProcessors;

    /**
     * List Dolby MS12 Audio Profiles (first is default).
     * If there are no defined MS12 Audio Profiles for this audio port then
     * dolbyMs12AudioProfiles is not populated with profile strings.
     */
    @nullable String[] dolbyMs12AudioProfiles;

    /**
     * @brief   True when this port supports audio capture via
     *          IAudioOutputPortController.getAudioCapture().
     *
     * @details If true, clients holding the port controller (acquired
     *          via IAudioOutputPort.open()) may call
     *          IAudioOutputPortController.getAudioCapture(listener) to
     *          obtain an IAudioCapture interface for streaming audio
     *          from this port. If false, calling @c getAudioCapture()
     *          throws binder::Status EX_UNSUPPORTED_OPERATION. Capture
     *          acquisition is gated by holding the port controller —
     *          the read-side IAudioOutputPort handle does not expose
     *          getAudioCapture().
     *
     * @see     IAudioOutputPortController.getAudioCapture()
     */
    boolean supportsAudioCapture;
}
