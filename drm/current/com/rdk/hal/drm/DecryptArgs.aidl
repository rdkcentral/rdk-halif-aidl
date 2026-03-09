/*
 * Copyright (C) 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -------------------------------------------------------------------
 * This file was inspired by Android 16 and derived from 
 * the following work:
 *
 *     Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0.
 * -------------------------------------------------------------------
 */
package com.rdk.hal.drm;

import com.rdk.hal.drm.DestinationBuffer;
import com.rdk.hal.drm.KeyStatusType;
import com.rdk.hal.drm.Mode;
import com.rdk.hal.drm.Pattern;
import com.rdk.hal.drm.SharedBuffer;
import com.rdk.hal.drm.SubSample;

/**
 * Arguments to ICryptoPlugin decrypt
 */
@VintfStability
parcelable DecryptArgs {

    /**
     * A flag to indicate if a secure decoder is being used.
     *
     * This enables the plugin to configure buffer modes to work consistently
     * with a secure decoder.
     */
    boolean secure;

    /**
     * The keyId for the key that is used to do the decryption.
     *
     * The keyId refers to a key in the associated MediaDrm instance.
     */
    byte[] keyId;

    /**
     * The initialization vector
     */
    byte[] iv;

    /**
     * Crypto mode
     */
    Mode mode;

    /**
     * Crypto pattern
     */
    Pattern pattern;

    /**
     * A vector of subsamples indicating the number of clear and encrypted
     * bytes to process.
     *
     * This allows the decrypt call to operate on a range of subsamples in a
     * single call
     */
    SubSample[] subSamples;

    /**
     * Input buffer for the decryption
     */
    SharedBuffer source;

    /**
     * The offset of the first byte of encrypted data from the base of the
     * source buffer
     */
    long offset;

    /**
     * Output buffer for the decryption
     */
    DestinationBuffer destination;

}
