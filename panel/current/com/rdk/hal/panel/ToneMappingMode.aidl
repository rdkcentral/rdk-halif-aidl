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
 *
 * How the panel maps HDR content whose luminance exceeds the panel's peak.
 * Whether a mode takes a level is declared per mode in the
 * PQParameter.TONE_MAPPING_SETTINGS capability; a mode that takes none uses
 * ToneMappingLevel.TONE_MAPPING_LEVEL_NOT_APPLICABLE.
 */
@VintfStability
@Backing(type = "int")
enum ToneMappingMode {
    /** Invalid or unset mode. */
    TONE_MAPPING_INVALID = -1,
    /** Tone mapping per scene: the curve follows the content as it changes. */
    TONE_MAPPING_DYNAMIC = 0,
    /**
     * No tone mapping (HGiG). Values up to the panel's peak are shown as
     * mastered; values above it are clipped.
     */
    TONE_MAPPING_CLIPPING = 1,
    /** One fixed tone curve, the same for all content. */
    TONE_MAPPING_STATIC = 2,
}
