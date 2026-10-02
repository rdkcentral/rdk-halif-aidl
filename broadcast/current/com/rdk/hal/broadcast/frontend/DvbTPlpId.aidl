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
 * @brief A DVB-T2 Physical Layer Pipe (PLP) identifier.
 *
 * Applies to DVB-T2 only and is ignored when tuning DVB-T. PLP selection is mandatory for a DVB-T2 frontend, so any
 * frontend reporting DvbTStandard.T2 in DvbTCapabilities.dvbTStandards accepts an identifier in the range MIN to MAX,
 * as well as AUTO.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable DvbTPlpId {
    /** No PLP selected. */
    const int UNDEFINED = -2;

    /** Select the PLP automatically. */
    const int AUTO = -1;

    /** The lowest valid PLP identifier. */
    const int MIN = 0;

    /** The highest valid PLP identifier. */
    const int MAX = 255;

    /** The actual PLP identifier. */
    int value = UNDEFINED;
}
