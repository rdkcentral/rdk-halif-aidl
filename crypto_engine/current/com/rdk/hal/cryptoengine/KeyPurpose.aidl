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
 * @brief Permitted purposes for a key.
 *
 * Bound to the key at creation time and enforced at operation begin().
 * Aligned with W3C WebCrypto KeyUsages.
 */
@VintfStability
@Backing(type="int")
enum KeyPurpose {
    /** Not configured. Must be explicitly set by the caller. */
    UNSET = -1,
    ENCRYPT = 0,
    DECRYPT = 1,
    SIGN = 2,
    VERIFY = 3,
    /** Key agreement (ECDH, DH). */
    AGREE_KEY = 4,
    /** Wrap a key for transport or storage (AES-KW, RSA-OAEP). */
    WRAP_KEY = 5,
    /** Unwrap a wrapped key. */
    UNWRAP_KEY = 6,
    /** Derive a new key from this key (HKDF, PBKDF2, NFLX-DH). */
    DERIVE_KEY = 7,
    /** Derive raw secret bits from a key. */
    DERIVE_BITS = 8,
}
