/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast.demux;

import com.rdk.hal.broadcast.demux.IAudioFilter;
import com.rdk.hal.broadcast.demux.IClockFilter;
import com.rdk.hal.broadcast.demux.IMpeg2TsDataFilter;
import com.rdk.hal.broadcast.demux.ISupplementaryAudioFilter;
import com.rdk.hal.broadcast.demux.IVideoFilter;

/**
 * A typed demux filter instance.
 *
 * Exactly one member is active and represents the concrete filter instance that was opened.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
union Filter {
    /** A MPEG-2 TS data filter instance. */
    IMpeg2TsDataFilter mpeg2TsData;

    /** A clock filter instance. */
    IClockFilter clock;

    /** A video filter instance. */
    IVideoFilter video;

    /** An audio filter instance. */
    IAudioFilter audio;

    /** A supplementary audio filter instance. */
    ISupplementaryAudioFilter supplementaryAudio;
}
