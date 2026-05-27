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
package com.rdk.hal.farfieldvoice;

/**
 *  @brief     Far Field Voice listening-mode definitions.
 *
 *  Describes the externally-observable listening behaviour of the FFV module.
 *  Deliberately uses listening-capability vocabulary rather than platform
 *  power-state names to avoid implying this module drives system power; the
 *  system owns power control. Each platform advertises the modes it supports
 *  in the HFP (Capabilities.supportedListeningModes).
 *
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
@Backing(type="int")
enum ListeningMode
{
    /**
     * Mode never set, or a mode change is in progress (not ready).
     */
    NONE = 0,

    /**
     * Module is actively streaming voice audio (post-wake-word).
     * Equivalent to the former FULL_POWER.
     */
    ACTIVE_LISTEN = 1,

    /**
     * Module is in low-power keyword-detect / wake-word watch mode.
     * Equivalent to the former STANDBY.
     */
    KEYWORD_ALERT = 2,

    /**
     * Module is powered down; no detection, no streaming.
     * Equivalent to the former DEEP_SLEEP.
     */
    POWERED_OFF = 3,
}
