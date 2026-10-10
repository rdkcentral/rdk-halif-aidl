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
import com.rdk.hal.cryptoengine.SecurityLevel;

/**
 * @brief Capabilities of a crypto engine instance.
 *
 * Returned by ICryptoEngine.getCapabilities() to allow callers to
 * introspect what the engine supports on this platform.
 */
@VintfStability
parcelable EngineCapabilities {
    /** HAL version string. */
    @utf8InCpp String halVersion;
    /** Security level of this engine (SOFTWARE or TEE). */
    SecurityLevel securityLevel = SecurityLevel.SOFTWARE;
    /** Supported algorithms. */
    Algorithm[] algorithms = {};
    /** Supported block modes. */
    BlockMode[] blockModes = {};
    /** Supported digests. */
    Digest[] digests = {};
    /** Supported key sizes in bits. */
    int[] keySizes = {};
    /** Maximum concurrent operations. */
    int maxConcurrentOperations = 0;
    /** Whether hardware crypto acceleration is available. */
    boolean hardwareAccelerated = false;
}
