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
 * @brief A DVB-S2/S2X Input Stream Identifier (ISI).
 *
 * Selects one stream of a multiple input stream (MIS) carrier. Input stream selection is optional, so a specific
 * identifier may only be requested where the frontend reports DvbSCapabilities.isInputStreamIdSupported.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable DvbSInputStreamId {
    /** No specific input stream selected. */
    const int UNDEFINED = -1;

    /** The lowest valid input stream identifier. */
    const int MIN = 0;

    /** The highest valid input stream identifier. */
    const int MAX = 255;

    /** The actual input stream identifier. */
    int value = UNDEFINED;
}
