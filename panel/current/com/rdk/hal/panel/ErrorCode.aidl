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
 * @brief Error codes returned by panel control operations.
 */
@VintfStability
@Backing(type = "int")
enum ErrorCode {
    /** The request was applied. */
    SUCCESS = 0,
    /** One or more arguments were invalid. */
    INVALID_ARGUMENT = 1,
    /** The request is not valid in the current state. */
    INVALID_STATE = 2,
    /** The request is not supported by the platform. */
    NOT_SUPPORTED = 3,
    /** The HAL could not apply the request. */
    HARDWARE_FAILURE = 4,
}
