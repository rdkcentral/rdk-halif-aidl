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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 package com.rdk.hal.audiomixer;

/**
 * @brief Defines the available mixer operating modes.
 *
 * These modes influence how audio streams are blended within the mixer,
 * including attenuation behavior during interruptive or priority playback scenarios.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
@Backing(type="int")
enum MixingMode {
    /**
     * Standard mixing behavior. All streams mix at their configured volumes.
     */
    NORMAL = 0,

    /**
     * Background streams are attenuated while a priority (interruptive) stream plays.
     */
    DUCKED = 1,

    /**
     * Only the designated stream is played; all others are temporarily muted.
     */
    SOLO = 2,

    /**
     * All streams are forcibly muted at the mixer level.
     */
    MUTED = 3,

    /**
     * Overrides standard mixing rules for special stream behavior (e.g., emergency alerts).
     */
    MIXED_OVERRIDE = 4,

    /**
     * Vendor-specific or extended mixing behavior.
     */
    VENDOR_EXTENSION = 1000
}