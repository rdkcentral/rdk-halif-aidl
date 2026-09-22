/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.hdmicec;

/**
 * @brief       Device types as defined in the HDMI specification 2-0 section 11.3.2
 */

@VintfStability
@Backing(type="int")
enum DeviceType {
    /**
     * No device type
     */
    NONE = 0,

    /**
     * Render the video from HDMI input on a screen
     */
    TV = 1,

    /**
     * Generic Source with recording functionality
     * that is expressed via CEC Feature "One Touch Record"
     */
    RECORDING_DEVICE = 2,

    /**
     * Generic Source with tuner functionality that is
     * expressed via CEC Feature "Tuner Control"
     */
    TUNER = 3,

    /**
     * Generic Source which is not a recording device or a tuner.
     */
    PLAYBACK_DEVICE = 4,

    /**
     * Render the audio from HDMI input (or alternate audio input);
     * implements System Audio Control Feature
     */
    AUDIO_SYSTEM = 5,

    /**
     * A device according to H14b Section CEC 11.1 which has no other
     * functionality or device type.
     */
    CEC_SWITCH = 6,

    /**
     * A device that performs processing functions:
     * Cannot itself become an Active Source.
     * has an HDMI output and at least one input.
     * passes video from input to output modified or unmodified.
     * has its own physical address.
     * requires direct addressing.
     * has no other device types.
     */
    PROCESSOR = 7
}