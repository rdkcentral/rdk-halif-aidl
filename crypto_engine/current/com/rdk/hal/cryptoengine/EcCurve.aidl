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
 * @brief Elliptic curve identifiers.
 *
 * Aligned with W3C WebCrypto named curves.
 */
@VintfStability
@Backing(type="int")
enum EcCurve {
    /** Not configured. Must be explicitly set by the caller. */
    UNSET = -1,
    /** NIST P-256 (secp256r1). Used by ECDSA and ECDH. */
    P_256 = 0,
    /** NIST P-384 (secp384r1). */
    P_384 = 1,
    /** NIST P-521 (secp521r1). */
    P_521 = 2,
    /** Curve25519 for Ed25519 signing. */
    ED25519 = 3,
    /** Curve25519 for X25519 key agreement. */
    X25519 = 4,
}
