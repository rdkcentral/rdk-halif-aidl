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
package com.rdk.hal.audiodecoder;
 
/** 
 *  @brief     Audio decoder error code definitions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type="int")
/*!<
 * @brief Defines error codes for audio decoder operations.
 */
enum ErrorCode {
    SUCCESS = 0,            /*!< Operation completed successfully. */
    BUFFER_FULL = 1,        /*!< The buffer is full and cannot accept more data. */
    INVALID_RESOURCE = 2,   /*!< The requested resource is invalid or unavailable. */
    INVALID_CODEC = 3,      /*!< The specified codec is not supported or recognized. */
    DEFERRED = 4,           /*!< The operation has been deferred and will be retried later. */
    OUT_OF_MEMORY = 5,      /*!< Memory allocation failed. */
    OUT_OF_BOUNDS = 6,      /*!< Operation attempted to access data out of valid bounds. */
    NOT_EMPTY = 7,          /*!< Expected container is not empty when it should be. */
    INVALID_ARGUMENT = 8,   /*!< An invalid argument was passed to the function. */
};


