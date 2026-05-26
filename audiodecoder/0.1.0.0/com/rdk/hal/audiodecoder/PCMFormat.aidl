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
 *  @brief     PCM audio formats.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type="int")
/**
* @brief Enumeration defining different Pulse Code Modulation (PCM) formats.
*/
enum PCMFormat {
    F64LE = 0, /**< 64-bit floating-point, little-endian. */
    F64BE = 1, /**< 64-bit floating-point, big-endian. */
    F32LE = 2, /**< 32-bit floating-point, little-endian. */
    F32BE = 3, /**< 32-bit floating-point, big-endian. */
    S32LE = 4, /**< 32-bit signed integer, little-endian. */
    S32BE = 5, /**< 32-bit signed integer, big-endian. */
    U32LE = 6, /**< 32-bit unsigned integer, little-endian. */
    U32BE = 7, /**< 32-bit unsigned integer, big-endian. */
    S24_32LE = 8, /**< 32-bit signed integer with 24 most significant bits, little-endian. */
    S24_32BE = 9, /**< 32-bit signed integer with 24 most significant bits, big-endian. */
    U24_32LE = 10, /**< 32-bit unsigned integer with 24 most significant bits, little-endian. */
    U24_32BE = 11, /**< 32-bit unsigned integer with 24 most significant bits, big-endian. */
    S24LE = 12, /**< 24-bit signed integer, little-endian. */
    S24BE = 13, /**< 24-bit signed integer, big-endian. */
    U24LE = 14, /**< 24-bit unsigned integer, little-endian. */
    U24BE = 15, /**< 24-bit unsigned integer, big-endian. */
    S20LE = 16, /**< 20-bit signed integer, little-endian. */
    S20BE = 17, /**< 20-bit signed integer, big-endian. */
    U20LE = 18, /**< 20-bit unsigned integer, little-endian. */
    U20BE = 19, /**< 20-bit unsigned integer, big-endian. */
    S18LE = 20, /**< 18-bit signed integer, little-endian. */
    S18BE = 21, /**< 18-bit signed integer, big-endian. */
    U18LE = 22, /**< 18-bit unsigned integer, little-endian. */
    U18BE = 23, /**< 18-bit unsigned integer, big-endian. */
    S16LE = 24, /**< 16-bit signed integer, little-endian. */
    S16BE = 25, /**< 16-bit signed integer, big-endian. */
    U16LE = 26, /**< 16-bit unsigned integer, little-endian. */
    U16BE = 27, /**< 16-bit unsigned integer, big-endian. */
    S8 = 28, /**< 8-bit signed integer. */
    U8 = 29  /**< 8-bit unsigned integer. */
}
