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
 * Values are power-of-two flags for use as a bitmask in KeyDescriptor.usages
 * and DerivedKeySpec.usages (e.g. ENCRYPT | DECRYPT).
 *
 * When used as the purpose parameter in begin(), a single value is passed.
 * When stored as key usages, values are OR'd together.
 *
 * Aligned with W3C WebCrypto KeyUsages.
 */
@VintfStability
@Backing(type="int")
enum KeyPurpose {
    ENCRYPT = 1 << 0,
    DECRYPT = 1 << 1,
    SIGN = 1 << 2,
    VERIFY = 1 << 3,
    /** Key agreement (ECDH, DH). */
    AGREE_KEY = 1 << 4,
    /** Wrap a key for transport or storage (AES-KW, RSA-OAEP). */
    WRAP_KEY = 1 << 5,
    /** Unwrap a wrapped key. */
    UNWRAP_KEY = 1 << 6,
    /** Derive a new key from this key (HKDF, PBKDF2, NFLX-DH). */
    DERIVE_KEY = 1 << 7,
    /** Derive raw secret bits from a key. */
    DERIVE_BITS = 1 << 8,
}
