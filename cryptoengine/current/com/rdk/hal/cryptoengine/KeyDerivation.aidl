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
 * @brief Key derivation function identifiers.
 *
 * Used with KeyPurpose.DERIVE_KEY and KeyPurpose.DERIVE_BITS.
 */
@VintfStability
@Backing(type="int")
enum KeyDerivation {
    /** Not configured. Must be explicitly set by the caller. */
    UNSET = -1,
    /** HMAC-based Extract-and-Expand Key Derivation Function (RFC 5869). */
    HKDF = 0,
    /** Password-Based Key Derivation Function 2 (RFC 2898). */
    PBKDF2 = 1,
    /** Netflix authenticated Diffie-Hellman key derivation. */
    NFLX_DH = 2,
    /** Standard Diffie-Hellman key exchange. */
    DH = 3,
}
