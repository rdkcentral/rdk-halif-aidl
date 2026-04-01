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
import com.rdk.hal.cryptoengine.KeyType;

/**
 * @brief Specification for a key to be produced by a derive-into-vault operation.
 *
 * Each DerivedKeySpec describes one output key: its alias, algorithm,
 * type, size, allowed usages, and extractability. The vault stores
 * the derived key material under the given alias with these properties.
 *
 * For NFLX-DH, three specs are provided (encryption, hmac, wrapping).
 * For HKDF/PBKDF2, typically one spec is provided.
 */
@VintfStability
parcelable DerivedKeySpec {
    /** Alias under which the derived key will be stored in the vault. */
    @utf8InCpp String alias;
    /** Algorithm of the derived key (AES, HMAC, etc.). */
    Algorithm algorithm = Algorithm.UNSET;
    /** Key type (SECRET for symmetric derivation). */
    KeyType keyType = KeyType.SECRET;
    /** Key size in bits. */
    int keySizeBits = 0;
    /** Allowed usages as a bitmask of KeyPurpose values. */
    int usages = 0;
    /** Whether the derived key material can be exported. */
    boolean extractable = false;
    /** Digest algorithm associated with this key (for HMAC keys). */
    Digest digest = Digest.UNSET;
}
