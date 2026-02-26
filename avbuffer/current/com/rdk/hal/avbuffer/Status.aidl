/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.avbuffer;

/** 
 * @brief AVBuffer operation status codes.
 *
 * Status codes returned by AVBuffer HAL interface operations to indicate
 * success or specific failure conditions.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */
 
@VintfStability
@Backing(type="int")
enum Status {
    /** @brief Operation completed successfully. */
    SUCCESS = 0,

    /** @brief Buffer pool is full, cannot allocate more buffers. */
    BUFFER_FULL = 1,

    /** @brief Invalid resource identifier provided. */
    INVALID_RESOURCE = 2,

    /** @brief Invalid codec specified. */
    INVALID_CODEC = 3,

    /** @brief Operation deferred for asynchronous completion. */
    DEFERRED = 4,

    /** @brief Insufficient memory available to complete operation. */
    OUT_OF_MEMORY = 5,

    /** @brief Request exceeds valid bounds or limits. */
    OUT_OF_BOUNDS = 6,

    /** @brief Pool or buffer is not empty when expected to be. */
    NOT_EMPTY = 7,

    /** @brief Invalid argument provided to operation. */
    INVALID_ARGUMENT = 8,
}
