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
package com.rdk.hal.deepsleep;

/** 
 *  @brief     Deep sleep wake up triggers.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum WakeUpTrigger
{
    /**
     * Deep sleep wakeup reason is unknown.
     * This should never be used but is provided if the wake reason cannot be
     * determined due to an internal error.
     */
    ERROR_UNKNOWN = -1,
 
    /**
     * Deep sleep wakeup reason is due to IR Remote.
     * The specific IR codes to wake upon are product specific and
     * determined by the vendor layer implementation.
     */
    RCU_IR = 0,
 
    /**
     * Deep sleep wakeup reason is due to RCU Bluetooth Remote.
     */
    RCU_BT = 1,
 
    /**
     * Deep sleep wakeup reason is due to RCU RF4CE Remote.
     */
    RCU_RF4CE = 2,
 
    /**
     * Deep sleep wakeup reason is is due to LAN.
     * The standard WOL magic packet is used.
     */
    LAN = 3,
 
    /**
     * Deep sleep wakeup reason is is due to Wireless LAN.
     * The standard WOW magic packet is used.
     */
    WLAN = 4,
 
    /**
     * Deep sleep wakeup reason is is due to Clock Timer.
     */
    TIMER = 5,
 
    /**
     * Deep sleep wakeup reason is is due to Front Panel Button.
     */
    FRONT_PANEL = 6,
 
    /**
     * Deep sleep wakeup reason is due to HDMI CEC Message.
     */
    CEC = 7,
 
    /**
     * Deep sleep wakeup reason is due to Motion Detection.
     */
    PRESENCE = 8,
 
    /**
     * Deep sleep wakeup reason is due to User Voice.
     */
    VOICE = 9, 
}
