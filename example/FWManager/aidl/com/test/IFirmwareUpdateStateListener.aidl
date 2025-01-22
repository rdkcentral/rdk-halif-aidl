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
 * IFirmwareUpdateStateListener.aidl
 *
 * Contains the Firmware status information notification that the firmware
 * update component state has changed. FirmwareStatus which includes following fields
 * state:
 *     A string containing the state of the OS firmware update component.
 * percentProgress:
 *     Represents the total progress through the check/download/verify an install flow.
 * compulsory:
 *     Used to specify the firmware detected is mandatory or not.
 */

// IFirmwareUpdateStateListener.aidl
package com.test;

import com.test.FirmwareStatus;

interface IFirmwareUpdateStateListener {

    /*
     * Notification that the OS firmware update component state has changed.
     */
    void onFirmwareUpdateStateChanged(in FirmwareStatus status);
}
