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

import com.rdk.hal.cryptoengine.Algorithm;
import com.rdk.hal.cryptoengine.BlockMode;
import com.rdk.hal.cryptoengine.Digest;
import com.rdk.hal.cryptoengine.EcCurve;
import com.rdk.hal.cryptoengine.KeyDerivation;
import com.rdk.hal.cryptoengine.PaddingMode;

/**
 * @brief Configuration for a crypto operation.
 *
 * Used with ICryptoEngineController.begin() when operating on
 * caller-provided key material (not vault-managed keys).
 *
 * Describes the full set of parameters needed for any supported
 * crypto operation. Callers must explicitly set all fields relevant
 * to the requested operation. Fields default to UNSET and the
 * implementation must reject operations with unconfigured required fields.
 */
@VintfStability
parcelable CryptoConfig {

    // -- Algorithm selection --

    /** Algorithm to use (AES, EC, HMAC, RSA, ChaCha20-Poly1305). Must be set. */
    Algorithm algorithm = Algorithm.UNSET;

    // -- Symmetric cipher parameters --

    /** Block mode for AES operations (CBC, CTR, GCM, ECB, KW). */
    BlockMode blockMode = BlockMode.UNSET;
    /** Padding mode (NONE, PKCS7 for AES; RSA_OAEP, RSA_PSS for RSA). */
    PaddingMode paddingMode = PaddingMode.UNSET;
    /** Key size in bits (128, 192, 256 for AES; 2048, 3072, 4096 for RSA). 0 = not set. */
    int keySizeBits = 0;
    /** Raw key material for standalone operations. Empty when using vault-managed keys. */
    byte[] keyData = {};
    
    /** Initialization vector or nonce.
     *
     *  If null, the engine auto-generates a random IV using the hardware RNG
     *  and prepends it to the ciphertext output. On decrypt, the engine reads
     *  the IV from the first bytes of the ciphertext input.
     *
     *  If provided, the engine uses the given IV as-is and does NOT prepend it
     *  to the output. The caller is responsible for storing and providing the
     *  IV on decrypt.
     *
     *  Sizes: AES-CBC/CTR: 16 bytes. AES-GCM: 12 bytes. ChaCha20: 12 bytes. */
    @nullable byte[] iv;

    // -- Authenticated encryption parameters (GCM, ChaCha20-Poly1305) --

    /** Additional authenticated data. Authenticated but not encrypted. */
    @nullable byte[] aad;
    /** Authentication tag length in bits (GCM: 96, 104, 112, 120, 128). 0 = not set. */
    int macLengthBits = 0;

    // -- Digest / HMAC parameters --

    /** Digest algorithm for HMAC, sign/verify, and KDF operations. */
    Digest digest = Digest.UNSET;

    // -- Elliptic curve parameters --

    /** EC curve for key generation or agreement (P-256, P-384, Ed25519, X25519). */
    EcCurve ecCurve = EcCurve.UNSET;

    // -- Key derivation parameters --

    /** Key derivation function (HKDF, PBKDF2, NFLX-DH, DH). */
    KeyDerivation kdf = KeyDerivation.UNSET;
    /** Salt for HKDF or PBKDF2. Null for unsalted derivation.
     *  HKDF: recommended HashLen bytes (e.g. 32 for SHA-256), any length valid.
     *  PBKDF2: minimum 16 bytes (NIST SP 800-132). */
    @nullable byte[] salt;
    /** Info/context string for HKDF. */
    @nullable byte[] info;
    /** Iteration count for PBKDF2. 0 = not set. */
    int pbkdf2Iterations = 0;
    /** Desired output key length in bits for key derivation. 0 = not set. */
    int derivedKeyLengthBits = 0;

    // -- RSA parameters --

    /** RSA public exponent. Only used for RSA key generation. 0 = not set. */
    long rsaPublicExponent = 0;

    // -- Key wrapping --

    /** Wrapped key data for unwrap operations. */
    @nullable byte[] wrappedKeyData;
}
