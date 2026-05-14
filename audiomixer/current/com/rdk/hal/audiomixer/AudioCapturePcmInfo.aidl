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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.Channel;

/**
 * @brief PCM sample format descriptor for captured audio.
 * 
 * Describes the binary encoding of PCM samples within an AudioCaptureData frame.
 * Only populated when AudioCaptureData.format is PCM_STEREO or PCM_MULTICHANNEL.
 */
@VintfStability
parcelable AudioCapturePcmInfo {
    /**
     * Number of significant bits per PCM sample (e.g., 16, 24, 32).
     */
    int bitsPerSample;

    /**
     * Container word size in bits that each sample is packed into (e.g., 32).
     * When equal to bitsPerSample, samples are tightly packed with no padding.
     * When greater (e.g., bitsPerSample=24, containerBitsPerSample=32), each sample
     * occupies a larger container word with the unused bits padded to zero.
     */
    int containerBitsPerSample;

    /**
     * True if samples are signed integers; false if unsigned.
     * Signed is typical for 16-bit and 32-bit PCM. 8-bit PCM is commonly unsigned.
     */
    boolean isSigned;

    /**
     * True if sample bytes are in little-endian order; false for big-endian.
     * Little-endian is standard on x86/ARM platforms.
     */
    boolean isLittleEndian;

    /**
     * @brief Channel position map for multi-channel PCM audio.
     *
     * Describes the order and position of audio channels within the captured PCM frame.
     * The array index represents the channel number (0-based), and the Channel enum value
     * at that index indicates the physical or logical placement of that channel.
     *
     * Populated when AudioCaptureData.format is PCM_MULTICHANNEL and PCM_STEREO
     * For PCM_STEREO, this array will contain two entries: [CH_FL, CH_FR].
     *
     * @returns Array of Channel positions in frame order. Empty array if channel mapping is not provided.
     *
     * Example for 5.1 surround (Left, Right, Centre, LFE, Rear Left, Rear Right):
     * [CH_FL, CH_FR, CH_FC, CH_LFE, CH_RL, CH_RR]
     */
    Channel[] channelMap;
}
