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
 * @brief     Audio Quality Processor type.
 * @details   Enumerates available audio quality processors supported by the platform,
 *            such as Dolby MS12, DTS, or vendor-specific implementations. Used for
 *            selection and capability discovery on audio output ports.
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 * @author   Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
@Backing(type="int")
enum AQProcessor {
    /** Undefined or no AQ processor. */
    UNDEFINED = 0,

    /** Dolby MS12 audio processor. */
    DOLBY_MS12 = 1,

    /** DTS:X Ultra processor. */
    DTS_ULTRA = 2,

    /** Vendor-extensions or custom AQ processor. */
    VENDOR_EXTENSION = 1000
}
