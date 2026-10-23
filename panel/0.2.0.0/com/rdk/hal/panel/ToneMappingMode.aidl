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
 * @brief HDR tone-mapping mode.
 */
@VintfStability
@Backing(type="int")
enum ToneMappingMode {
    TONE_MAPPING_INVALID = -1,
    TONE_MAPPING_DYNAMIC = 0,
    TONE_MAPPING_CLIPPING = 1,
    TONE_MAPPING_STATIC = 2,
}