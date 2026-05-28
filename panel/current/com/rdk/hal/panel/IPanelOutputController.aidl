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

/**
 * @file IPanelOutputController.aidl
 * @brief Exclusive controller interface for a panel output instance.
 *
 * Returned by {@link IPanelOutput#open(IPanelOutputControllerListener)}.
 * Provides lifecycle control (start/stop). Only one controller may exist
 * per panel output at a time.
 *
 * If the client that opened this controller crashes, stop() and close()
 * are implicitly called by the HAL to release the panel output.
 */
package com.rdk.hal.panel;

@VintfStability
interface IPanelOutputController {
    /**
     * @brief Start the panel output controller.
     *
     * On success, the state transitions STOPPED -> STARTING -> STARTED.
    * IPanelOutputControllerListener.onStateChanged() fires for each
     * transition. If hardware initialization fails, the state transitions
     * to ERROR (observable via onStateChanged()) and this call fails with
     * EX_SERVICE_SPECIFIC. Use IPanelOutput.close() to release the panel
     * output from ERROR; close() accepts STOPPED or ERROR.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if panel output is not
     *            in STOPPED state.
     * @exception binder::Status EX_SERVICE_SPECIFIC if hardware
     *            initialization fails. The state transitions to ERROR
     *            before the exception is raised.
     */
    void start();

    /**
     * @brief Stop the panel output controller.
     *
     * On success, the state transitions STARTED -> STOPPING -> STOPPED.
    * IPanelOutputControllerListener.onStateChanged() fires for each
     * transition.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if panel output is not
     *            in STARTED state.
     */
    void stop();
}
