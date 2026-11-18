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
package com.rdk.hal.keyvault;

import com.rdk.hal.cryptoengine.Algorithm;
import com.rdk.hal.cryptoengine.Digest;
import com.rdk.hal.cryptoengine.EcCurve;

/**
 * @brief Parameters bound to a key when it is generated or imported.
 *
 * Passed to IKeyVaultController.generateKey(), generateKeyPair() and
 * importKey(). Every value is bound to the key at creation, recorded in
 * its KeyDescriptor, and enforced on every later operation.
 */
@VintfStability
parcelable KeyParameters {
    /** Algorithm of the key. Must be set. */
    Algorithm algorithm = Algorithm.UNSET;
    /**
     * Key size in bits (AES: 128, 192, 256; RSA: 2048, 3072, 4096; DH: 2048, 3072).
     * For EC keys the curve sets the size and this field is ignored.
     * For importKey(), 0 means take the size from the key data.
     */
    int keySizeBits = 0;
    /** Curve for EC keys (P-256, P-384, Ed25519, X25519). Required when algorithm is EC; ignored otherwise. */
    EcCurve ecCurve = EcCurve.UNSET;
    /**
     * Digest bound to the key: required for HMAC keys; optional for SIGN/VERIFY
     * keys, where it restricts the digest used.
     */
    Digest digest = Digest.UNSET;
    /** Allowed usages as a bitmask of KeyPurpose values. For a keypair, the usages of the private key. */
    int usages = 0;
    /** Whether the key material can be exported. For a keypair, applies to the private key only. */
    boolean extractable = false;
}
