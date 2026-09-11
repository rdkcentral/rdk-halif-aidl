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
 * DVB-S, DVB-S2, and DVB-S2X inner FEC enum.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum DvbSInnerFec {
    UNDEFINED = 0,
    AUTO,

    /** FEC_1_2 applies to DVB-S, DVB-S2, and DVB-S2X. */
    FEC_1_2,
    /** FEC_1_3 applies to DVB-S2 and DVB-S2X. */
    FEC_1_3,
    /** FEC_1_4 applies to DVB-S2 and DVB-S2X. */
    FEC_1_4,
    /** FEC_1_5 applies to DVB-S2X. */
    FEC_1_5,
    /** FEC_2_3 applies to DVB-S, DVB-S2, and DVB-S2X. */
    FEC_2_3,
    /** FEC_2_5 applies to DVB-S2 and DVB-S2X. */
    FEC_2_5,
    /** FEC_2_9 applies to DVB-S2X. */
    FEC_2_9,
    /** FEC_3_4 applies to DVB-S, DVB-S2, and DVB-S2X. */
    FEC_3_4,
    /** FEC_3_5 applies to DVB-S2 and DVB-S2X. */
    FEC_3_5,
    /** FEC_4_5 applies to DVB-S2 and DVB-S2X. */
    FEC_4_5,
    /** FEC_4_15 applies to DVB-S2X. */
    FEC_4_15,
    /** FEC_5_6 applies to DVB-S, DVB-S2, and DVB-S2X. */
    FEC_5_6,
    /** FEC_7_8 applies to DVB-S. */
    FEC_7_8,
    /** FEC_7_9 applies to DVB-S2X. */
    FEC_7_9,
    /** FEC_7_10 applies to DVB-S2X. */
    FEC_7_10,
    /** FEC_7_15 applies to DVB-S2X. */
    FEC_7_15,
    /** FEC_8_9 applies to DVB-S2 and DVB-S2X. */
    FEC_8_9,
    /** FEC_8_15 applies to DVB-S2X. */
    FEC_8_15,
    /** FEC_9_10 applies to DVB-S2 and DVB-S2X. */
    FEC_9_10,
    /** FEC_11_15 applies to DVB-S2X. */
    FEC_11_15,
    /** FEC_11_20 applies to DVB-S2X. */
    FEC_11_20,
    /** FEC_11_45 applies to DVB-S2X. */
    FEC_11_45,
    /** FEC_13_18 applies to DVB-S2X. */
    FEC_13_18,
    /** FEC_14_45 applies to DVB-S2X. */
    FEC_14_45,
    /** FEC_23_36 applies to DVB-S2X. */
    FEC_23_36,
    /** FEC_25_36 applies to DVB-S2X. */
    FEC_25_36,
    /** FEC_26_45 applies to DVB-S2X. */
    FEC_26_45,
    /** FEC_28_45 applies to DVB-S2X. */
    FEC_28_45,
    /** FEC_32_45 applies to DVB-S2X. */
    FEC_32_45,
    /** FEC_77_90 applies to DVB-S2X. */
    FEC_77_90,
}
