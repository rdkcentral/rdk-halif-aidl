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
package com.rdk.hal.cryptoengine;

/**
 * @brief Digest algorithms.
 *
 * Aligned with W3C WebCrypto digest algorithms.
 */
@VintfStability
@Backing(type="int")
enum Digest {
    /** Not configured. Must be explicitly set by the caller. */
    UNSET = -1,
    NONE = 0,
    SHA_2_224 = 2,
    SHA_2_256 = 3,
    SHA_2_384 = 4,
    SHA_2_512 = 5,
    SHA_3_256 = 6,
    SHA_3_384 = 7,
    SHA_3_512 = 8,
}
