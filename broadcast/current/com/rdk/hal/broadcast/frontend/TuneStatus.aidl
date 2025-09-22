/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.broadcast.frontend;

/**
 *  @brief     TuneStatus enum
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

@VintfStability
enum TuneStatus {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /** The frontend is currently idle */
    IDLE,
    /** The frontend is trying to obtain lock */
    TUNING,
    /** The frontend was not able to lock to the requested tune parameters */
    NO_SIGNAL,
    /** The frontend is locked to a signal */
    LOCKED,
}
