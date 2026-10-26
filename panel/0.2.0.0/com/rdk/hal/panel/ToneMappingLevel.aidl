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
 * @brief HDR tone-mapping level.
 */
@VintfStability
@Backing(type = "int")
enum ToneMappingLevel {
    /** Invalid or unset level. */
    TONE_MAPPING_LEVEL_INVALID = -1,
    /** The tone-mapping mode has no selectable levels. */
    TONE_MAPPING_LEVEL_NOT_APPLICABLE = 0,
    /** Low tone-mapping level. */
    TONE_MAPPING_LEVEL_LOW = 1,
    /** Medium tone-mapping level. */
    TONE_MAPPING_LEVEL_MEDIUM = 2,
    /** High tone-mapping level. */
    TONE_MAPPING_LEVEL_HIGH = 3,
}
