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

import com.rdk.hal.broadcast.demux.Mpeg2TsDataFilterParameters;
import com.rdk.hal.broadcast.demux.Mpeg2TsTunnelFilterParameters;

/**
 * Tuner-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
union FilterParameters {
    /** A MPEG-2 TS data filter instance. */
    Mpeg2TsDataFilterParameters mpeg2TsData;

    /** A MPEG-2 TS clock filter instance. */
    Mpeg2TsTunnelFilterParameters mpeg2TsClock;

    /** A MPEG-2 TS video filter instance. */
    Mpeg2TsTunnelFilterParameters mpeg2TsVideo;

    /** A MPEG-2 TS audio filter instance. */
    Mpeg2TsTunnelFilterParameters mpeg2TsAudio;

    /** A MPEG-2 TS supplementary audio filter instance. */
    Mpeg2TsTunnelFilterParameters mpeg2TsSupplementaryAudio;
}
