/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
 *
 * -------------------------------------------------------------------
 * This file is derived from Android 16 drm interface definitions:
 *
 * https://android.googlesource.com/platform/hardware/interfaces/+/refs/tags/android-16.0.0_r4/drm/aidl/android/hardware/drm
 *
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0.
 * -------------------------------------------------------------------
 */
package com.rdk.hal.drm;

import com.rdk.hal.drm.KeyStatusType;
import com.rdk.hal.drm.Mode;
import com.rdk.hal.drm.Pattern;
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
     *
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
     * Input AVBuffer handle for the encrypted data.
     * 
     * It is the responsibility of the caller to recycle/free the allocated AVBuffer after the call to decrypt returns.
     */
    long sourceBufferHandle;

    /**
     * Output AVBuffer handle for the decrypted data.
     */
    long destinationBufferHandle;

}
