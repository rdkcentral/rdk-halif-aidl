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

/**
 * @file IPanelOutputManager.aidl
 * @brief Service entry point for discovering and accessing panel outputs.
 *
 * The manager enumerates available panel output instances and returns
 * interfaces to them. A typical implementation is a singleton service
 * registered under {@link #serviceName}.
 */
package com.rdk.hal.panel;

import com.rdk.hal.panel.IPanelOutput;

/**
 * @interface IPanelOutputManager
 * @brief Top-level manager interface for Panel Output HAL access.
 */
@VintfStability
interface IPanelOutputManager {
    /**
     * @brief Binder service registration name.
     *
     * Vendors should publish the service with this name at system startup.
     */
    const @utf8InCpp String serviceName = "panel.output";

    /**
     * @brief Enumerate all platform-specific panel output identifiers.
     * @returns Array of available panel output IDs.
     */
    @nullable IPanelOutput.Id[] getPanelOutputIds();

    /**
     * @brief Retrieve a panel output interface by ID.
     * @param panelOutputId The identifier of the requested panel output.
     * @returns The panel output interface, or null if the ID is invalid.
     */
    @nullable IPanelOutput getPanelOutput(in IPanelOutput.Id panelOutputId);
}
