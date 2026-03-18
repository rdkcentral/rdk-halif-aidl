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
 * This file is derived from Android 16 drm interface definitions:
 *
 * https://android.googlesource.com/platform/hardware/interfaces/+/refs/tags/android-16.0.0_r4/drm/aidl/android/hardware/drm    
 * 
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0.
 * -------------------------------------------------------------------
 */
package com.rdk.hal.drm;

@VintfStability
parcelable ProvideProvisionResponseResult {
    /**
     * The public certificate resulting from the provisioning
     * operation, if any. An empty vector indicates that no
     * certificate was returned.
     */
    byte[] certificate;

    /**
     * An opaque object containing encrypted private key material
     * to be used by signRSA when computing an RSA signature on a
     * message, see the signRSA method.
     */
    byte[] wrappedKey;
}
