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

/**
 * @brief An MPEG-2 Transport Stream packet identifier.
 *
 * Used by every filter that selects packets by PID, whether the filtered data is returned to the client through a
 * ring buffer or tunnelled to a decoder.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable Mpeg2TsPid {
    /** No PID selected. */
    const int UNDEFINED = -1;

    /** The lowest valid PID. */
    const int MIN = 0;

    /** The highest valid PID, i.e. 0x1FFF. */
    const int MAX = 8191;

    /** The actual PID. */
    int value = UNDEFINED;
}
