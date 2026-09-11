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
 * @file      AQParameter.aidl
 * @brief     Canonical spelling reference for AQ (Audio Quality) parameter names.
 *
 *            IMPORTANT: This enum exists ONLY as a spelling reference for HFP
 *            authors. It is NOT consulted at runtime and NOT used in any
 *            binder signature.
 *
 *            The authoritative source of which parameters a given AQ processor
 *            exposes is the platform HFP YAML
 *            (hfp-audiomixer.yaml -> aqProcessors[].parameters[].name), surfaced
 *            at runtime by IAQProcessor.getSupportedParameters() returning
 *            AQParameterMetadata records keyed by @utf8InCpp String name.
 *
 *            Use these enumerator labels as canonical spellings when authoring
 *            an HFP entry so platforms do not diverge on capitalisation or
 *            abbreviation (e.g. "BASS_ENHANCER_GAIN" not "bassGain"). New
 *            parameters may be added to a vendor HFP without changing this
 *            enum; the enum is not exhaustive and is not part of the wire
 *            contract.
 *
 * @see       IAQProcessor.getSupportedParameters()
 * @see       AQParameterMetadata
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
@Backing(type="int")
enum AQParameter {
    VOLUME_LEVELLER = 0,          /**< Automatic volume levelling. */
    DIALOGUE_ENHANCER = 1,        /**< Enhanced speech/dialogue clarity. */
    DIALOGUE_CLARITY = 2,         /**< Fine-tune dialogue frequency range. */
    AC4_DIALOGUE_ENHANCER = 3,    /**< AC-4 specific dialogue enhancer. */
    BASS_ENHANCER_GAIN = 4,       /**< Bass boost gain. */
    BASS_ENHANCER_WIDTH = 5,      /**< Bass enhancement bandwidth. */
    BASS_ENHANCER_CUTOFF = 6,     /**< Bass enhancer cutoff frequency. */
    SURROUND_DECODER = 7,         /**< Enable/disable surround decoding. */
    SURROUND_VIRTUALIZER = 8,     /**< Virtual surround effect. */
    MI_STEERING = 9,              /**< Main/associated mix steering. */
    GRAPHIC_EQUALIZER = 10,       /**< Multi-band graphic EQ. */
    INTELLIGENT_EQUALIZER = 11,   /**< Content-adaptive EQ. */
    POST_GAIN = 12,               /**< Final output gain adjustment. */
    VOLUME_MODELER = 13,          /**< Dynamic loudness/volume shaping. */
    AUDIO_OPTIMIZER = 14,         /**< Generic audio post-processing. */
    ACTIVE_DOWNMIX = 15,          /**< Downmix multichannel to stereo. */
    CENTER_SPREADING = 16,        /**< Centre channel spreading. */
    DRC = 17,                     /**< Dynamic Range Compression. */
    ATMOS_LOCK = 18,              /**< Lock output to Dolby Atmos rendering. */
    DOWNMIX_MODE = 19,            /**< Lt/Rt vs Lo/Ro downmix selection. */
}
