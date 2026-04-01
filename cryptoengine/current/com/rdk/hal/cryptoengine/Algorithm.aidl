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
 * @brief Cryptographic algorithms.
 *
 * Based on PRD Firebolt Cryptography Capabilities requirements and
 * W3C WebCrypto algorithm registry.
 */
@VintfStability
@Backing(type="int")
enum Algorithm {
    /** Not configured. Must be explicitly set by the caller. */
    UNSET = -1,
    /** AES symmetric cipher (128, 192, 256-bit). */
    AES = 0,
    /** Elliptic Curve (ECDSA sign/verify, ECDH key agreement, Ed25519). */
    EC = 1,
    /** HMAC message authentication code. */
    HMAC = 2,
    /** RSA asymmetric cipher (RSA-OAEP, RSA-PSS, RSASSA-PKCS1-v1_5). */
    RSA = 3,
    /** ChaCha20-Poly1305 authenticated encryption. */
    CHACHA20_POLY1305 = 4,
    /** CMAC message authentication code (AES-128). Required by Widevine OEMCrypto for key derivation. */
    CMAC = 5,
}
