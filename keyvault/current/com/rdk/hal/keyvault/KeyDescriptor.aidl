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
 * @brief Metadata describing a key stored in a vault.
 *
 * Returned by key generation, import, listing, and lookup operations.
 * The key material itself is never exposed — only the descriptor is
 * visible to callers. All fields are set at key creation time and
 * immutable for the lifetime of the key (except keyVersion on rotation).
 */
@VintfStability
parcelable KeyDescriptor {
    /** Unique alias for this key within the vault. */
    @utf8InCpp String alias;
    /** Algorithm associated with this key (AES, EC, HMAC, RSA, ChaCha20-Poly1305). */
    Algorithm algorithm = Algorithm.UNSET;
    /** Key type: SECRET (symmetric), PUBLIC, or PRIVATE (asymmetric). */
    KeyType keyType = KeyType.SECRET;
    /** Key size in bits. */
    int keySizeBits = 0;
    /** Allowed usages as a bitmask of KeyPurpose values (ENCRYPT|DECRYPT, SIGN|VERIFY, etc.). */
    int usages = 0;
    /** Whether the raw key material can be exported. */
    boolean extractable = false;
    /** Digest algorithm associated with this key (e.g. SHA_2_256 for HMAC keys). */
    Digest digest = Digest.UNSET;
    /** Current key version (incremented on rotation). */
    int keyVersion = 0;
    /** Creation timestamp (milliseconds since epoch). */
    long createdAtMs = 0;
    /** Expiry timestamp (milliseconds since epoch). 0 = no expiry. */
    long expiresAtMs = 0;
}
