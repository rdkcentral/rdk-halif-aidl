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
 * @brief Type-specific parameters for opening a demux filter.
 *
 * Exactly one member is set. The active member selects which type of filter openFilter() creates, and carries the
 * parameters for that filter type.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 *
 * @see IDemuxController.openFilter()
 */
@VintfStability
union FilterParameters {
    /** Parameters for a MPEG-2 TS data filter. */
    Mpeg2TsDataFilterParameters mpeg2TsData;

    /** Parameters for a MPEG-2 TS clock filter. */
    Mpeg2TsTunnelFilterParameters mpeg2TsClock;

    /** Parameters for a MPEG-2 TS video filter. */
    Mpeg2TsTunnelFilterParameters mpeg2TsVideo;

    /** Parameters for a MPEG-2 TS audio filter. */
    Mpeg2TsTunnelFilterParameters mpeg2TsAudio;

    /** Parameters for a MPEG-2 TS supplementary audio filter. */
    Mpeg2TsTunnelFilterParameters mpeg2TsSupplementaryAudio;
}
