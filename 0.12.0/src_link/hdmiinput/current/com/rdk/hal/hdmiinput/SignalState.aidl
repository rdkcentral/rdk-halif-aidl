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
package com.rdk.hal.hdmiinput;
 
/** 
 *  @brief     HDMI Input Signal State enumeration.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum SignalState
{
    /**
     * Unknown signal state.
     */
    UNKNOWN = -1,

    /**
     * No signal detected.
     * 
     * HDMI source device may be disconnected, powered off or in standby.
     */
    NO_SIGNAL = 0,

    /**
     * Unstable signal detected.
     * 
     * Potential problem with cable, cable connection, port or transitionally during start up.
     */
    UNSTABLE = 1,

    /**
     * Unsupported signal detected.
     * 
     * An aspect of the incoming signal is out of range of the HDMI port capabilities.
     * e.g. resolution, color depth, frame rate.
     */
    NOT_SUPPORTED = 2,

    /**
     * A stable and supported signal is detected and locked.
     */
    LOCKED = 3,

}
