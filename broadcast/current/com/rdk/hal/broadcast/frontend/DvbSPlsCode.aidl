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
package com.rdk.hal.broadcast.frontend;

/**
 * @brief A DVB-S2/S2X physical-layer scrambling code (scrambling-sequence index).
 *
 * The index is in the range MIN to MAX, i.e. 0x00000 to 0x3FFFE. Which values within that range are usable depends on
 * the DvbSPlsMode the code is used with, so a frontend still rejects a code it cannot apply for the requested mode.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable DvbSPlsCode {
    /** No physical-layer scrambling code selected. */
    const int UNDEFINED = -1;

    /** The lowest valid scrambling-sequence index, i.e. 0x00000. */
    const int MIN = 0;

    /** The highest valid scrambling-sequence index, i.e. 0x3FFFE. */
    const int MAX = 262142;

    /** The actual scrambling-sequence index. */
    int value = UNDEFINED;
}
