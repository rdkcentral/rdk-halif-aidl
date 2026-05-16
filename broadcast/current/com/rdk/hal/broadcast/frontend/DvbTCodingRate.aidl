/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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

import com.rdk.hal.broadcast.frontend.CodingRate;

/**
 *  @brief  DVB-T LP and HP coding rates, used as a signal info value.
 *
 *  Returned for @ref SignalInfoProperty::DVB_T_CODING_RATE.
 */
@VintfStability
parcelable DvbTCodingRate {
    /** Low-priority stream coding rate */
    CodingRate lp;
    /** High-priority stream coding rate */
    CodingRate hp;
}
