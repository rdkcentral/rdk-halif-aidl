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
 * DVB-T and DVB-T2 code rate enum.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum DvbTCodeRate {
    UNDEFINED = 0,
    AUTO,

    /** CR_1_2 applies to DVB-T and DVB-T2. */
    CR_1_2,
    /** CR_2_3 applies to DVB-T and DVB-T2. */
    CR_2_3,
    /** CR_3_4 applies to DVB-T and DVB-T2. */
    CR_3_4,
    /** CR_3_5 applies to DVB-T2. */
    CR_3_5,
    /** CR_4_5 applies to DVB-T2. */
    CR_4_5,
    /** CR_5_6 applies to DVB-T and DVB-T2. */
    CR_5_6,
    /** CR_7_8 applies to DVB-T. */
    CR_7_8,
}
