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
 * @brief A symbol rate, carrying its unit in the type.
 *
 * Applies to DVB-C and DVB-S/S2/S2X only. The valid range is resource-specific: see minSymbolRate and maxSymbolRate on
 * DvbCCapabilities or DvbSCapabilities for the frontend in question.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable SymbolRate {
    /** No symbol rate selected. */
    const int UNDEFINED = 0;

    /**
     * Detect the symbol rate automatically.
     *
     * Only valid where the frontend reports isAutoSymbolRateSupported, see DvbCCapabilities and DvbSCapabilities.
     */
    const int AUTO = -1;

    /** The symbol rate in symbols per second. */
    int symbolsPerSecond = UNDEFINED;
}
