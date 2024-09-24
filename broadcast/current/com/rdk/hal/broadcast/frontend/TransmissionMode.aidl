/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.broadcast.frontend;

/**
 *  @brief     Ttransmission modes
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/**
 * Note that this enum is shared across all frontend types and thus includes values that are only
 * usable on some of them. You should always request and consult the list of supported transmission
 * modes from the frontend before using any of them.
 */
@VintfStability
enum TransmissionMode {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /** Auto-selected transmission mode */
    AUTO,
    /** Transmission mode of 2k used in DVB-T */
    MODE_2K,
    /** Transmission mode of 4k used in DVB-T */
    MODE_4K,
    /** Transmission mode of 8k used in DVB-T */
    MODE_8K,
    /** Transmission mode of 1k used in DVB-T2 */
    MODE_1K,
    /** Transmission mode of 16k used in DVB-T2 */
    MODE_16K,
    /** Transmission mode of 32k used in DVB-T2 */
    MODE_32K,
}
