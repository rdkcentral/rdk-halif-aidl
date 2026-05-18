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
package com.rdk.hal;
 
/** 
 * @brief       RDK HAL common error codes returned by HAL interface functions.
 * @author      Luc Kennedy-Lamb
 * @author      Peter Stieglitz
 * @author      Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum HALError {
    SUCCESS = 0,
    BUFFER_FULL = 1,
    INVALID_RESOURCE = 2,
    INVALID_CODEC = 3,
    DEFERRED = 4,
    OUT_OF_MEMORY = 5,
    OUT_OF_BOUNDS = 6,
    NOT_EMPTY = 7,	
    INVALID_ARGUMENT = 8,
}
