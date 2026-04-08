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
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0.
 * -------------------------------------------------------------------
 */

package com.rdk.hal.drm;

/**
 * Enumerate the supported DRM errors
 * Errors from Android 16
 * https://android.googlesource.com/platform/frameworks/av/+/refs/tags/android-16.0.0_r4/media/libstagefright/include/media/stagefright/MediaErrors.h
 *
 * Errors added as a convenience for Clients and Interface plug-ins
 */
@VintfStability
@Backing(type="int")
enum DrmErrors {

    DRM_ERROR_BASE = -2000,

    ERROR_DRM_UNKNOWN                        = DRM_ERROR_BASE,
    ERROR_DRM_NO_LICENSE                     = DRM_ERROR_BASE - 1,
    ERROR_DRM_LICENSE_EXPIRED                = DRM_ERROR_BASE - 2,
    ERROR_DRM_SESSION_NOT_OPENED             = DRM_ERROR_BASE - 3,
    ERROR_DRM_DECRYPT_UNIT_NOT_INITIALIZED   = DRM_ERROR_BASE - 4,
    ERROR_DRM_DECRYPT                        = DRM_ERROR_BASE - 5,
    ERROR_DRM_CANNOT_HANDLE                  = DRM_ERROR_BASE - 6,
    ERROR_DRM_TAMPER_DETECTED                = DRM_ERROR_BASE - 7,
    ERROR_DRM_NOT_PROVISIONED                = DRM_ERROR_BASE - 8,
    ERROR_DRM_DEVICE_REVOKED                 = DRM_ERROR_BASE - 9,
    ERROR_DRM_RESOURCE_BUSY                  = DRM_ERROR_BASE - 10,
    ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION = DRM_ERROR_BASE - 11,
    ERROR_DRM_INSUFFICIENT_SECURITY          = DRM_ERROR_BASE - 12,
    ERROR_DRM_FRAME_TOO_LARGE                = DRM_ERROR_BASE - 13,
    ERROR_DRM_RESOURCE_CONTENTION            = DRM_ERROR_BASE - 14,
    ERROR_DRM_SESSION_LOST_STATE             = DRM_ERROR_BASE - 15,
    ERROR_DRM_INVALID_STATE                  = DRM_ERROR_BASE - 16,

    // New in S / drm@1.4:
    ERROR_DRM_CERTIFICATE_MALFORMED          = DRM_ERROR_BASE - 17,
    ERROR_DRM_CERTIFICATE_MISSING            = DRM_ERROR_BASE - 18,
    ERROR_DRM_CRYPTO_LIBRARY                 = DRM_ERROR_BASE - 19,
    ERROR_DRM_GENERIC_OEM                    = DRM_ERROR_BASE - 20,
    ERROR_DRM_GENERIC_PLUGIN                 = DRM_ERROR_BASE - 21,
    ERROR_DRM_INIT_DATA                      = DRM_ERROR_BASE - 22,
    ERROR_DRM_KEY_NOT_LOADED                 = DRM_ERROR_BASE - 23,
    ERROR_DRM_LICENSE_PARSE                  = DRM_ERROR_BASE - 24,
    ERROR_DRM_LICENSE_POLICY                 = DRM_ERROR_BASE - 25,
    ERROR_DRM_LICENSE_RELEASE                = DRM_ERROR_BASE - 26,
    ERROR_DRM_LICENSE_REQUEST_REJECTED       = DRM_ERROR_BASE - 27,
    ERROR_DRM_LICENSE_RESTORE                = DRM_ERROR_BASE - 28,
    ERROR_DRM_LICENSE_STATE                  = DRM_ERROR_BASE - 29,
    ERROR_DRM_MEDIA_FRAMEWORK                = DRM_ERROR_BASE - 30,
    ERROR_DRM_PROVISIONING_CERTIFICATE       = DRM_ERROR_BASE - 31,
    ERROR_DRM_PROVISIONING_CONFIG            = DRM_ERROR_BASE - 32,
    ERROR_DRM_PROVISIONING_PARSE             = DRM_ERROR_BASE - 33,
    ERROR_DRM_PROVISIONING_REQUEST_REJECTED  = DRM_ERROR_BASE - 34,
    ERROR_DRM_PROVISIONING_RETRY             = DRM_ERROR_BASE - 35,
    ERROR_DRM_SECURE_STOP_RELEASE            = DRM_ERROR_BASE - 36,
    ERROR_DRM_STORAGE_READ                   = DRM_ERROR_BASE - 37,
    ERROR_DRM_STORAGE_WRITE                  = DRM_ERROR_BASE - 38,
    ERROR_DRM_ZERO_SUBSAMPLES                = DRM_ERROR_BASE - 39,
    ERROR_DRM_LAST_USED_ERRORCODE            = ERROR_DRM_ZERO_SUBSAMPLES,

    ERROR_DRM_VENDOR_MAX                     = DRM_ERROR_BASE - 500,
    ERROR_DRM_VENDOR_MIN                     = DRM_ERROR_BASE - 999,
}
