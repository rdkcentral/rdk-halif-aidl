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
 * @brief LNB Voltage enumeration
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */

@VintfStability
@Backing(type="int")
enum LnbVoltage {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /** No voltage on the LNB Controller - The voltage is zero */
    NONE = 1,
    /** The voltage is 13 volt */
    V13 = 13,
    /** The voltage is 14 volt */
    V14 = 14,
    /** The voltage is 15 volt */
    V15 = 15,
    /** The voltage is 18 volt */
    V18 = 18,
    /** The voltage is 19 volt */
    V19 = 19,
    /** The voltage is 20 volt */
    V20 = 20,
}