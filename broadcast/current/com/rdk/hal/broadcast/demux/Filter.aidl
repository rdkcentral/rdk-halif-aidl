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

import com.rdk.hal.broadcast.demux.IMpeg2TsAudioFilter;
import com.rdk.hal.broadcast.demux.IMpeg2TsClockFilter;
import com.rdk.hal.broadcast.demux.IMpeg2TsDataFilter;
import com.rdk.hal.broadcast.demux.IMpeg2TsSupplementaryAudioFilter;
import com.rdk.hal.broadcast.demux.IMpeg2TsVideoFilter;

/**
 * A typed demux filter instance.
 *
 * Exactly one member is active and represents the concrete filter instance that was opened.
 *
 * This union is semantically coupled to FilterType: every concrete filter kind defined in FilterType must have a
 * corresponding union member here.
 *
 * Note: FilterType values are not used as this union's discriminator tag. AIDL generates the union tag separately.
 *
 * @see FilterType
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
union Filter {
    /** A MPEG-2 TS data filter instance. */
    IMpeg2TsDataFilter mpeg2TsData;

    /** A MPEG-2 TS clock filter instance. */
    IMpeg2TsClockFilter mpeg2TsClock;

    /** A MPEG-2 TS video filter instance. */
    IMpeg2TsVideoFilter mpeg2TsVideo;

    /** A MPEG-2 TS audio filter instance. */
    IMpeg2TsAudioFilter mpeg2TsAudio;

    /** A MPEG-2 TS supplementary audio filter instance. */
    IMpeg2TsSupplementaryAudioFilter mpeg2TsSupplementaryAudio;
}
