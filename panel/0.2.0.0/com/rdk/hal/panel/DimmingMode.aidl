/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.panel;

/**
 * @brief Local dimming mode.
 */
@VintfStability
@Backing(type = "int")
enum DimmingMode {
    /** Invalid or unset mode. */
    DIMMING_MODE_INVALID = -1,
    /** The backlight is fixed and is not dimmed. */
    DIMMING_MODE_FIXED = 0,
    /** The backlight is dimmed for the whole panel. */
    DIMMING_MODE_GLOBAL = 1,
    /** The backlight is dimmed per zone. */
    DIMMING_MODE_LOCAL = 2,
}
