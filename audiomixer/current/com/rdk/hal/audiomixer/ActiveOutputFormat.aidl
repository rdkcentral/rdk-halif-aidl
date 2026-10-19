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
import com.rdk.hal.audiomixer.ImmersiveFormat;
import com.rdk.hal.audiomixer.OutputFormat;

/**
 * @brief    The audio an output port is emitting now.
 * @details  Read with IAudioOutputPort.getActiveOutputFormat() and delivered
 *           whole by IAudioOutputPortListener.onActiveOutputFormatChanged().
 *           Every field describes the same instant: one negotiated change is
 *           one event, so a client never sees a mix of old and new values.
 *
 *           The configured value stays in OutputPortProperty.OUTPUT_FORMAT
 *           (which may be AUTO or PASSTHROUGH); this parcelable is what that
 *           configuration resolved to against the current source and sink.
 *
 *           Each output port reports independently. At the same moment HDMI
 *           may carry MAT with Dolby Atmos, SPDIF AC3 5.1 and the speakers
 *           PCM rendered from the same Atmos source.
 *
 * @author    Gerald Weatherup
 * @copyright Copyright 2026 RDK Management
 */
@VintfStability
parcelable ActiveOutputFormat {
    /**
     * The format on the wire. Never AUTO or PASSTHROUGH: a passthrough
     * bitstream reports its own format (e.g. EAC3) with isPassthrough true.
     */
    OutputFormat format;

    /**
     * True when the source bitstream is sent unchanged; false when the HAL
     * decoded, mixed, transcoded or encoded it.
     */
    boolean isPassthrough;

    /** Sample rate in Hz (e.g. 48000). */
    int sampleRateHz;

    /**
     * Channel positions in frame order. The array length is the channel
     * count, LFE included. For a bitstream format this is the coded bed
     * (e.g. 7.1 for a MAT Atmos stream), not the immersive objects.
     */
    Channel[] channelMap;

    /**
     * Immersive content carried or rendered on this port.
     * NONE when a port that cannot carry immersive audio receives it: the
     * HAL emits the channel bed or a downmix, and does not report an error.
     */
    ImmersiveFormat immersive;
}
