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
 * @brief The type of a cryptographic key.
 *
 * Aligned with W3C WebCrypto CryptoKey.type and Netflix DPI NF_Crypto_KeyType.
 */
@VintfStability
@Backing(type="int")
enum KeyType {
    /** A secret symmetric key (AES, HMAC). */
    SECRET = 0,
    /** The public half of an asymmetric keypair (RSA, EC). */
    PUBLIC = 1,
    /** The private half of an asymmetric keypair (RSA, EC). */
    PRIVATE = 2,
}
