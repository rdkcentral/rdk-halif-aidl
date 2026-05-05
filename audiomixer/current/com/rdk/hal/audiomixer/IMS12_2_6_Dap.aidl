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

import com.rdk.hal.audiomixer.MS12DownmixMode;
import com.rdk.hal.audiomixer.MS12DrcMode;
import com.rdk.hal.audiomixer.MS12GeqMode;
import com.rdk.hal.audiomixer.MS12IeqMode;
import com.rdk.hal.audiomixer.MS12LevellerMode;
import com.rdk.hal.audiomixer.MS12VirtualizerMode;

/**
 * @brief Dolby MS12 2.6 DAP runtime command control interface.
 * Provides one API method for each supported `ms12_runtime` command.
 */
@VintfStability
interface IMS12_2_6_Dap {
    /**
     * @brief Enables or disables DAP surround decoder processing.
     * @param[in] enabled True to enable, false to disable.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setSurroundDecoderEnabled(in boolean enabled);

    /**
     * @brief Sets DAP bass enhancer boost value.
     * @param[in] boost Bass enhancer boost in range 0 to 100.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setBassEnhancer(in int boost);

    /**
     * @brief Sets DAP volume leveller mode and level.
     * @param[in] mode Volume leveller mode.
     * @param[in] level Volume leveller level in range 0 to 10.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setVolumeLeveller(in MS12LevellerMode mode, in int level);

    /**
     * @brief Sets DAP surround virtualizer mode and boost.
     * @param[in] mode Surround virtualizer mode.
     * @param[in] boost Surround virtualizer boost in range 0 to 96.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setSurroundVirtualizer(in MS12VirtualizerMode mode, in int boost);

    /**
     * @brief Enables or disables media intelligent steering.
     * @param[in] enabled True to enable, false to disable.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setMISteering(in boolean enabled);

    /**
     * @brief Sets DAP post gain.
     * @param[in] gain Post gain in range -2080 to 480.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setPostGain(in float gain);

    /**
     * @brief Sets DAP dialogue enhancer level.
     * @param[in] level Dialogue enhancer level in range 0 to 16.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if argument is out of range.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setDialogueEnhancer(in int level);

    /**
     * @brief Sets DAP intelligent equalizer mode.
     * @param[in] mode Intelligent equalizer mode.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setIntelligentEqualizerMode(in MS12IeqMode mode);

    /**
     * @brief Sets DAP graphic equalizer mode.
     * @param[in] mode Graphic equalizer mode.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setGraphicEqualizerMode(in MS12GeqMode mode);

    /**
     * @brief Sets DAP dynamic range control mode.
     * @param[in] mode Dynamic range control mode.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setDRCMode(in MS12DrcMode mode);

    /**
     * @brief Sets Dolby Atmos lock mode.
     * @param[in] enabled True to lock Atmos output, false to unlock.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setAtmosLock(in boolean enabled);

    /**
     * @brief Sets downmix mode.
     * @param[in] mode Downmix mode.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    boolean setDownmixMode(in MS12DownmixMode mode);

    /**
     * @brief Enables or disables volume modeler.
     * @param[in] enabled True to enable, false to disable.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if MS12 2.6 feature not available.
     */
    boolean setVolumeModelerEnabled(in boolean enabled);

    /**
     * @brief Enables or disables centre spreading.
     * @param[in] enabled True to enable, false to disable.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if MS12 2.6 feature not available.
     */
    boolean setCenterSpreadingEnabled(in boolean enabled);

    /**
     * @brief Enables or disables active downmix.
     * @param[in] enabled True to enable, false to disable.
     * @returns True if the command was applied; false on command failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if MS12 2.6 feature not available.
     */
    boolean setActiveDownmixEnabled(in boolean enabled);
}
