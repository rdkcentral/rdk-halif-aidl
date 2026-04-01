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
 * @brief Padding modes for cipher and signature operations.
 */
@VintfStability
@Backing(type="int")
enum PaddingMode {
    /** Not configured. Must be explicitly set by the caller. */
    UNSET = -1,
    /** No padding. Caller must ensure data is block-aligned. */
    NONE = 0,
    /** PKCS#7 padding for AES block ciphers. */
    PKCS7 = 1,
    /** RSA Optimal Asymmetric Encryption Padding. */
    RSA_OAEP = 2,
    /** RSA Probabilistic Signature Scheme. */
    RSA_PSS = 3,
    /** RSA PKCS#1 v1.5 signature. */
    RSA_PKCS1_V1_5 = 4,
}
