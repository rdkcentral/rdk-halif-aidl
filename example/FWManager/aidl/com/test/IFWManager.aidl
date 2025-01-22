/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright (C) 2024 Sky
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

/** @brief
 * IFWManager.aidl
 *
 * Contains the Firmware Manager service interfaces.
 */

// IFWManager.aidl
package com.test;

import com.test.FirmwareStatus;
import com.test.IFirmwareUpdateStateListener;

interface IFWManager {

    /*
     * Gets the active firmware version.
     */
    String getFirmwareVersion() = 400;

    /*
     * Gets the current active firmware bank.
     */
    int getCurrentBootBank() = 401;

    /*
     * Triggers an immediate check for a new firmware version
     */
    boolean triggerFirmwareUpdateCheck() = 402;

    /*
     * Gets the current state of the OS firmware update component.
     */
    FirmwareStatus getFirmwareUpdateState() = 403;

    /*
     * Registers a listener for firmware update state changes.
     */
    void registerDeviceStateFirmwareUpdateStateChanged(in IFirmwareUpdateStateListener listener) = 404;
}
