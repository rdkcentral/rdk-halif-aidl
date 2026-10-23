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
 * @brief Capability flags for IDolbyMs12_2_6_Dap runtime command support.
 *
 * Each field indicates whether the corresponding set function in
 * IDolbyMs12_2_6_Dap is supported for the current output port.
 */
@VintfStability
parcelable DolbyMs12_2_6_DapCapabilities {
    /** Whether `setSurroundDecoderEnabled()` is supported. */
    boolean supportsSurroundDecoderEnabled;
    /** Whether `setBassEnhancer()` is supported. */
    boolean supportsBassEnhancer;
    /** Whether `setVolumeLeveller()` is supported. */
    boolean supportsVolumeLeveller;
    /** Whether `setSurroundVirtualizer()` is supported. */
    boolean supportsSurroundVirtualizer;
    /** Whether `setMediaIntelligentSteering()` is supported. */
    boolean supportsMediaIntelligentSteering;
    /** Whether `setPostGain()` is supported. */
    boolean supportsPostGain;
    /** Whether `setDialogueEnhancer()` is supported. */
    boolean supportsDialogueEnhancer;
    /** Whether `setIntelligentEqualizerMode()` is supported. */
    boolean supportsIntelligentEqualizerMode;
    /** Whether `setGraphicEqualizerMode()` is supported. */
    boolean supportsGraphicEqualizerMode;
    /** Whether `setDynamicRangeControlMode()` is supported. */
    boolean supportsDynamicRangeControlMode;
    /** Whether `setAtmosLock()` is supported. */
    boolean supportsAtmosLock;
    /** Whether `setDownmixMode()` is supported. */
    boolean supportsDownmixMode;
    /** Whether `setVolumeModelerEnabled()` is supported. */
    boolean supportsVolumeModelerEnabled;
    /** Whether `setCenterSpreadingEnabled()` is supported. */
    boolean supportsCenterSpreadingEnabled;
    /** Whether `setActiveDownmixEnabled()` is supported. */
    boolean supportsActiveDownmixEnabled;
}
