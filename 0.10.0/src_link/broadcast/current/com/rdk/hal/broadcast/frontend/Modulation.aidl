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
 *  @brief     Available modulations
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/**
 * Note that this enum is shared across all frontend types and thus includes values that are only
 * usable on some of them. You should always request and consult the list of supported modulations
 * from the frontend before using any of them.
 */
@VintfStability
enum Modulation {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /** Auto-selected modulation */
    AUTO,
    /** QPSK */
    QPSK,
    /** DQPSK */
    DQPSK,
    /** PSK_8 */
    PSK_8,
    /** APSK_16 */
    APSK_16,
    /** APSK_32 */
    APSK_32,
    /** QAM_4 */
    QAM_4,
    /** QAM_4_NR */
    QAM_4_NR,
    /** QAM_16 */
    QAM_16,
    /** QAM_32 */
    QAM_32,
    /** QAM_64 */
    QAM_64,
    /** QAM_128 */
    QAM_128,
    /** QAM_256 */
    QAM_256,
    /** QAM_AUTO */
    QAM_AUTO,
    /** VSB_8 */
    VSB_8,
    /** VSB_16 */
    VSB_16,
    /** COFDM */
    COFDM,
}
