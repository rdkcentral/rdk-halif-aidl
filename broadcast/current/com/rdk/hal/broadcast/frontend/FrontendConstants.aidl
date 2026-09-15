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
 * @brief Sentinel values for the integer fields of the tune parameter parcelables.
 *
 * Declared on a parcelable with no imports rather than on IFrontend, so that the tune parameter parcelables can import
 * it without forming a circular include in the generated code. This type is never transferred; it exists only to carry
 * the constants.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable FrontendConstants {
    /** Select the PLP automatically (DVB-T2). */
    const int AUTO_PLP_ID = -1;

    /** No PLP selected (DVB-T2). */
    const int INVALID_PLP_ID = -2;

    /** Detect the symbol rate automatically (DVB-C and DVB-S/S2/S2X). */
    const int AUTO_SYMBOL_RATE = -1;

    /** No symbol rate selected (DVB-C and DVB-S/S2/S2X). */
    const int INVALID_SYMBOL_RATE = 0;

    /** No input stream selected (DVB-S2/S2X). */
    const int INVALID_INPUT_STREAM_ID = -1;

    /** No physical-layer scrambling code selected (DVB-S2/S2X). */
    const int INVALID_PLS_CODE = -1;
}
