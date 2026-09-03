/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
package com.rdk.hal.broadcast.frontend;

/**
 * Available DvbC bandwidths.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum DvbCBandwidth {
    /** Clean value when default initialized. */
    UNDEFINED = 0,
    /** The Tuner will automatically detect the bandwidth. */
    AUTO,
    /** 5 MHz. */
    MHZ_5,
    /** 6 MHz. */
    MHZ_6,
    /** 7 MHz. */
    MHZ_7,
    /** 8 MHz. */
    MHZ_8,
}
