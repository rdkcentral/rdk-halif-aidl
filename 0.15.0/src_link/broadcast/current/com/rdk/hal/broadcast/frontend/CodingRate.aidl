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
 *  @brief     Code Rate enum
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */


/**
 * Note that this enum is shared across all frontend types and thus includes values that are only
 * usable on some of them. You should always request and consult the list of supported coding rates
 * from the frontend before using any of them.
 */
@VintfStability
enum CodingRate {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /** Auto-selected coding rate */
    AUTO,
    /** 1/2 */
    CR_1_2,
    /** 2/3 */
    CR_2_3,
    /** 3/4 */
    CR_3_4,
    /** 5/6 */
    CR_5_6,
    /** 7/8 */
    CR_7_8,
    /** 8/9 Used by DVB-C */
    CR_8_9,
    /** 3/5 Used by DVB-C */
    CR_3_5,
    /** 4/5 Used by DVB-C */
    CR_4_5,
    /** 9/10 Used by DVB-C */
    CR_9_10,
}
