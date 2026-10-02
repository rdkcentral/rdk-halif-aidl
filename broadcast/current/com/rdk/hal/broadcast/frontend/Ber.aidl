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
 * @brief A bit error rate, expressed as a count of error bits per 1 billion bits.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.BER and SignalInfoProperty.PRE_BER, the latter being the
 * rate measured before error correction.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable Ber {
    /** No bit error rate reading. Distinct from MIN, which is a real reading of zero errors. */
    const int UNDEFINED = -1;

    /** The lowest valid bit error rate. */
    const int MIN = 0;

    /** The highest valid bit error rate, i.e. every bit in error. */
    const int MAX = 1000000000;

    /** The number of error bits per 1 billion bits. */
    int errorBitsPerBillion = UNDEFINED;
}
