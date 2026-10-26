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
 * Copyright (C) 2009 The Android Open Source Project
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
@Backing(type = "int")
enum DrmErrors {

    /** The base value of the DRM error code range. */
    DRM_ERROR_BASE = -2000,

    /** A fatal failure occurred and no other defined error is appropriate. */
    ERROR_DRM_UNKNOWN = DRM_ERROR_BASE,
    /** Decryption was attempted and no license keys have been provided. */
    ERROR_DRM_NO_LICENSE = DRM_ERROR_BASE - 1,
    /** An attempt was made to use a license whose keys have expired. */
    ERROR_DRM_LICENSE_EXPIRED = DRM_ERROR_BASE - 2,
    /** An attempt was made to use a session that has not been opened. */
    ERROR_DRM_SESSION_NOT_OPENED = DRM_ERROR_BASE - 3,
    /** The decrypt unit has not been initialised. */
    ERROR_DRM_DECRYPT_UNIT_NOT_INITIALIZED = DRM_ERROR_BASE - 4,
    /** The decrypt operation failed. */
    ERROR_DRM_DECRYPT = DRM_ERROR_BASE - 5,
    /** An unsupported data format or operation was attempted. */
    ERROR_DRM_CANNOT_HANDLE = DRM_ERROR_BASE - 6,
    /** Tampering with the drm subsystem was detected. */
    ERROR_DRM_TAMPER_DETECTED = DRM_ERROR_BASE - 7,
    /** The device has not yet been provisioned. */
    ERROR_DRM_NOT_PROVISIONED = DRM_ERROR_BASE - 8,
    /** The device has been revoked and is no longer permitted to play content. */
    ERROR_DRM_DEVICE_REVOKED = DRM_ERROR_BASE - 9,
    /** Resources, such as drm sessions or secure buffers, are not available because they are already in use. */
    ERROR_DRM_RESOURCE_BUSY = DRM_ERROR_BASE - 10,
    /** The output protection enabled on the device is not sufficient to meet the license policy. */
    ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION = DRM_ERROR_BASE - 11,
    /** The security level of the device is not sufficient to meet the license policy. */
    ERROR_DRM_INSUFFICIENT_SECURITY = DRM_ERROR_BASE - 12,
    /** The frame being decrypted exceeds the size of the secure output buffer. */
    ERROR_DRM_FRAME_TOO_LARGE = DRM_ERROR_BASE - 13,
    /** Crypto resources are temporarily exceeded, so a retry is likely to succeed. */
    ERROR_DRM_RESOURCE_CONTENTION = DRM_ERROR_BASE - 14,
    /** The session was used after the crypto hardware state was invalidated. */
    ERROR_DRM_SESSION_LOST_STATE = DRM_ERROR_BASE - 15,
    /** The device is in a state where it is not able to perform the operation. */
    ERROR_DRM_INVALID_STATE = DRM_ERROR_BASE - 16,

    // New in S / drm@1.4:
    /** The certificate is malformed or is of the wrong type. */
    ERROR_DRM_CERTIFICATE_MALFORMED = DRM_ERROR_BASE - 17,
    /** The certificate has not been set. */
    ERROR_DRM_CERTIFICATE_MISSING = DRM_ERROR_BASE - 18,
    /** An error occurred in the crypto library used by the drm plugin. */
    ERROR_DRM_CRYPTO_LIBRARY = DRM_ERROR_BASE - 19,
    /** A non-specific error was reported by the device OEM subsystem. */
    ERROR_DRM_GENERIC_OEM = DRM_ERROR_BASE - 20,
    /** An unexpected internal failure occurred in the drm or crypto plugin. */
    ERROR_DRM_GENERIC_PLUGIN = DRM_ERROR_BASE - 21,
    /** The init data passed to the key request is empty or invalid. */
    ERROR_DRM_INIT_DATA = DRM_ERROR_BASE - 22,
    /** The key was not loaded from the license, or the key ID is incorrect. */
    ERROR_DRM_KEY_NOT_LOADED = DRM_ERROR_BASE - 23,
    /** The license response was empty, has missing fields, or could not be parsed. */
    ERROR_DRM_LICENSE_PARSE = DRM_ERROR_BASE - 24,
    /** The operation is prohibited by the license policy. */
    ERROR_DRM_LICENSE_POLICY = DRM_ERROR_BASE - 25,
    /** A release request could not be generated because a field in the stored license is empty or malformed. */
    ERROR_DRM_LICENSE_RELEASE = DRM_ERROR_BASE - 26,
    /** The license server detected an error in the license request. */
    ERROR_DRM_LICENSE_REQUEST_REJECTED = DRM_ERROR_BASE - 27,
    /** An offline license could not be restored because a field is empty or malformed. */
    ERROR_DRM_LICENSE_RESTORE = DRM_ERROR_BASE - 28,
    /** The license is in an invalid state for the attempted operation. */
    ERROR_DRM_LICENSE_STATE = DRM_ERROR_BASE - 29,
    /** A failure occurred in the media framework. */
    ERROR_DRM_MEDIA_FRAMEWORK = DRM_ERROR_BASE - 30,
    /** There was an error loading the provisioned certificate. */
    ERROR_DRM_PROVISIONING_CERTIFICATE = DRM_ERROR_BASE - 31,
    /** Required steps were not performed before provisioning was attempted. */
    ERROR_DRM_PROVISIONING_CONFIG = DRM_ERROR_BASE - 32,
    /** The provisioning response was empty, has missing fields, or could not be parsed. */
    ERROR_DRM_PROVISIONING_PARSE = DRM_ERROR_BASE - 33,
    /** The provisioning server detected an error in the provisioning request. */
    ERROR_DRM_PROVISIONING_REQUEST_REJECTED = DRM_ERROR_BASE - 34,
    /** Provisioning failed in a way that is likely to succeed on a subsequent attempt. */
    ERROR_DRM_PROVISIONING_RETRY = DRM_ERROR_BASE - 35,
    /** A secure stop request could not be generated because a field in the stored license is empty or malformed. */
    ERROR_DRM_SECURE_STOP_RELEASE = DRM_ERROR_BASE - 36,
    /** The plugin was unable to read data from the filesystem. */
    ERROR_DRM_STORAGE_READ = DRM_ERROR_BASE - 37,
    /** The plugin was unable to write data to the filesystem. */
    ERROR_DRM_STORAGE_WRITE = DRM_ERROR_BASE - 38,
    /** Secure input was queued with zero subsamples. */
    ERROR_DRM_ZERO_SUBSAMPLES = DRM_ERROR_BASE - 39,
    /** The last error code in use. */
    ERROR_DRM_LAST_USED_ERRORCODE = ERROR_DRM_ZERO_SUBSAMPLES,

    /** The upper end of the range reserved for vendor-specific errors. */
    ERROR_DRM_VENDOR_MAX = DRM_ERROR_BASE - 500,
    /** The lower end of the range reserved for vendor-specific errors. */
    ERROR_DRM_VENDOR_MIN = DRM_ERROR_BASE - 999,
}
