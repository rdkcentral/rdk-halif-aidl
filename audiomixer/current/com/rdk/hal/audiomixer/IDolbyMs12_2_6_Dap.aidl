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

import com.rdk.hal.audiomixer.DolbyMs12_2_6_DapCapabilities;
import com.rdk.hal.audiomixer.DolbyMs12_2_6_DownmixMode;
import com.rdk.hal.audiomixer.DolbyMs12_2_6_DrcMode;
import com.rdk.hal.audiomixer.DolbyMs12_2_6_GeqMode;
import com.rdk.hal.audiomixer.DolbyMs12_2_6_IeqMode;
import com.rdk.hal.audiomixer.DolbyMs12_2_6_LevellerMode;
import com.rdk.hal.audiomixer.DolbyMs12_2_6_VirtualizerMode;

/**
 * @brief Dolby MS12 2.6 DAP runtime command control interface.
 * Provides one API method for each supported MS12 function.
 */
@VintfStability
interface IDolbyMs12_2_6_Dap {
    
    /**
     * @brief Gets the MS12 2.6 DAP capabilities supported.
     *
     * The Dolby Audio Processing can be different for each output port.
     * The support for each DAP set function in this interface for the output port is 
     * indicated by the capabilities. 
     * 
     * @returns DolbyMs12_2_6_DapCapabilities description for the output port.
     */
    DolbyMs12_2_6_DapCapabilities getCapabilities();


    /**
     * @brief Enables or disables DAP surround decoder processing.
     * @param[in] enabled True to enable, false to disable.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     * 
     */
    boolean setSurroundDecoderEnabled(in boolean enabled);

    /**
     * @brief Gets DAP surround decoder processing state.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns Current surround decoder enabled state.
     *
     */
    boolean getSurroundDecoderEnabled();

    /**
     * @brief Sets DAP bass enhancer boost value.
     * @param[in] boost Bass enhancer boost in range 0 to 100.
     * 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setBassEnhancer(in int boost);

    /**
     * @brief Gets DAP bass enhancer boost value.
     * @returns Bass enhancer boost in range 0 to 100.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    int getBassEnhancer();

    /**
     * @brief Sets DAP volume leveller mode and level.
     * @param[in] mode Volume leveller mode.
     * @param[in] level Volume leveller level in range 0 to 10.
     * 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setVolumeLeveller(in DolbyMs12_2_6_LevellerMode mode, in int level);

    /**
     * @brief Gets DAP volume leveller mode and level.
     * @param[out] mode Volume leveller mode.
     * @param[out] level Volume leveller level in range 0 to 10.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    void getVolumeLeveller(out DolbyMs12_2_6_LevellerMode mode, out int level);

    /**
     * @brief Sets DAP surround virtualizer mode and boost.
     * @param[in] mode Surround virtualizer mode.
     * @param[in] boost Surround virtualizer boost in range 0 to 96.
     * 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setSurroundVirtualizer(in DolbyMs12_2_6_VirtualizerMode mode, in int boost);

    /**
     * @brief Gets DAP surround virtualizer mode and boost.
     * @param[out] mode Surround virtualizer mode.
     * @param[out] boost Surround virtualizer boost in range 0 to 96.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    void getSurroundVirtualizer(out DolbyMs12_2_6_VirtualizerMode mode, out int boost);

    /**
     * @brief Enables or disables media intelligent steering.
     * @param[in] enabled True to enable, false to disable.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setMediaIntelligentSteering(in boolean enabled);

    /**
     * @brief Gets media intelligent steering state.
     * @returns True if media intelligent steering is enabled; false otherwise.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    boolean getMediaIntelligentSteering();

    /**
     * @brief Sets DAP post gain.
     * @param[in] gain Post gain in range -2080 to 480.
     * 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setPostGain(in float gain);

    /**
     * @brief Gets DAP post gain.
     * @returns Post gain in range -2080 to 480.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    float getPostGain();

    /**
     * @brief Sets DAP dialogue enhancer level.
     * @param[in] level Dialogue enhancer level in range 0 to 12.
     * 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setDialogueEnhancer(in int level);

    /**
     * @brief Gets DAP dialogue enhancer level.
     * @returns Dialogue enhancer level in range 0 to 12.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    int getDialogueEnhancer();

    /**
     * @brief Sets DAP intelligent equalizer mode.
     * @param[in] mode Intelligent equalizer mode.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setIntelligentEqualizerMode(in DolbyMs12_2_6_IeqMode mode);

    /**
     * @brief Gets DAP intelligent equalizer mode.
     * @returns Intelligent equalizer mode.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    DolbyMs12_2_6_IeqMode getIntelligentEqualizerMode();

    /**
     * @brief Sets DAP graphic equalizer mode.
     * @param[in] mode Graphic equalizer mode.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setGraphicEqualizerMode(in DolbyMs12_2_6_GeqMode mode);

    /**
     * @brief Gets DAP graphic equalizer mode.
     * @returns Graphic equalizer mode.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    DolbyMs12_2_6_GeqMode getGraphicEqualizerMode();

    /**
     * @brief Sets DAP dynamic range control mode.
     * @param[in] mode Dynamic range control mode.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setDynamicRangeControlMode(in DolbyMs12_2_6_DrcMode mode);

    /**
     * @brief Gets DAP dynamic range control mode.
     * @returns Dynamic range control mode.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    DolbyMs12_2_6_DrcMode getDynamicRangeControlMode();

    /**
     * @brief Sets Dolby Atmos lock mode.
     * @param[in] enabled True to lock Atmos output, false to unlock.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setAtmosLock(in boolean enabled);

    /**
     * @brief Gets Dolby Atmos lock mode.
     * @returns True if Atmos output lock is enabled; false otherwise.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    boolean getAtmosLock();

    /**
     * @brief Sets downmix mode.
     * @param[in] mode Downmix mode.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setDownmixMode(in DolbyMs12_2_6_DownmixMode mode);

    /**
     * @brief Gets downmix mode.
     * @returns Downmix mode.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    DolbyMs12_2_6_DownmixMode getDownmixMode();

    /**
     * @brief Enables or disables volume modeler.
     * @param[in] enabled True to enable, false to disable.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     * 
     */
    boolean setVolumeModelerEnabled(in boolean enabled);

    /**
     * @brief Gets volume modeler state.
     * @returns True if volume modeler is enabled; false otherwise.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * 
     */
    boolean getVolumeModelerEnabled();

    /**
     * @brief Enables or disables centre spreading.
     * @param[in] enabled True to enable, false to disable.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setCenterSpreadingEnabled(in boolean enabled);

    /**
     * @brief Gets centre spreading state.
     * @returns True if centre spreading is enabled; false otherwise.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * 
     */
    boolean getCenterSpreadingEnabled();

    /**
     * @brief Enables or disables active downmix.
     * @param[in] enabled True to enable, false to disable.
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     * @returns true if the command was applied.
     */
    boolean setActiveDownmixEnabled(in boolean enabled);

    /**
     * @brief Gets active downmix state.
     * @returns True if active downmix is enabled; false otherwise.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
     */
    boolean getActiveDownmixEnabled();
}
