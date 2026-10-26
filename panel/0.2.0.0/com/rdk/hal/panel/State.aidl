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
 * @file State.aidl
 * @brief Lifecycle states for a panel output instance.
 */
package com.rdk.hal.panel;

@VintfStability
@Backing(type = "int")
enum State {
    /** The controller is stopped; start() may be called. */
    STOPPED = 0,
    /** A start() is in progress. */
    STARTING = 1,
    /** The panel output is running; control operations are valid. */
    STARTED = 2,
    /** A stop() is in progress. */
    STOPPING = 3,
    /** A state transition failed; release the controller with close(). */
    ERROR = 4,
}
