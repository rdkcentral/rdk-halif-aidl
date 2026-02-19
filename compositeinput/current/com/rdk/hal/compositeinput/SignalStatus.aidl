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

package com.rdk.hal.compositeinput;

/**
 * @brief Composite input signal status.
 * 
 * Describes the current state of the composite video signal detection.
 */
@VintfStability
@Backing(type="int")
enum SignalStatus
{
    /** No signal detected on the port. */
    NO_SIGNAL = 0,
    
    /** Signal detected but unstable or not locked. */
    UNSTABLE = 1,
    
    /** Signal detected but format is not supported. */
    NOT_SUPPORTED = 2,
    
    /** Signal detected, locked, and stable. */
    STABLE = 3,
}
