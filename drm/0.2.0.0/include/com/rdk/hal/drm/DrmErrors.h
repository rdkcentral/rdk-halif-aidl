#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
// @aidl-doc
/**
 * Enumerate the supported DRM errors
 * Errors from Android 16
 * https://android.googlesource.com/platform/frameworks/av/+/refs/tags/android-16.0.0_r4/media/libstagefright/include/media/stagefright/MediaErrors.h
 *
 * Errors added as a convenience for Clients and Interface plug-ins
 */
enum class DrmErrors : int32_t {
  // @aidl-doc
  /** The base value of the DRM error code range. */
  DRM_ERROR_BASE = -2000,
  // @aidl-doc
  /** A fatal failure occurred and no other defined error is appropriate. */
  ERROR_DRM_UNKNOWN = -2000,
  // @aidl-doc
  /** Decryption was attempted and no license keys have been provided. */
  ERROR_DRM_NO_LICENSE = -2001,
  // @aidl-doc
  /** An attempt was made to use a license whose keys have expired. */
  ERROR_DRM_LICENSE_EXPIRED = -2002,
  // @aidl-doc
  /** An attempt was made to use a session that has not been opened. */
  ERROR_DRM_SESSION_NOT_OPENED = -2003,
  // @aidl-doc
  /** The decrypt unit has not been initialised. */
  ERROR_DRM_DECRYPT_UNIT_NOT_INITIALIZED = -2004,
  // @aidl-doc
  /** The decrypt operation failed. */
  ERROR_DRM_DECRYPT = -2005,
  // @aidl-doc
  /** An unsupported data format or operation was attempted. */
  ERROR_DRM_CANNOT_HANDLE = -2006,
  // @aidl-doc
  /** Tampering with the drm subsystem was detected. */
  ERROR_DRM_TAMPER_DETECTED = -2007,
  // @aidl-doc
  /** The device has not yet been provisioned. */
  ERROR_DRM_NOT_PROVISIONED = -2008,
  // @aidl-doc
  /** The device has been revoked and is no longer permitted to play content. */
  ERROR_DRM_DEVICE_REVOKED = -2009,
  // @aidl-doc
  /** Resources, such as drm sessions or secure buffers, are not available because they are already in use. */
  ERROR_DRM_RESOURCE_BUSY = -2010,
  // @aidl-doc
  /** The output protection enabled on the device is not sufficient to meet the license policy. */
  ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION = -2011,
  // @aidl-doc
  /** The security level of the device is not sufficient to meet the license policy. */
  ERROR_DRM_INSUFFICIENT_SECURITY = -2012,
  // @aidl-doc
  /** The frame being decrypted exceeds the size of the secure output buffer. */
  ERROR_DRM_FRAME_TOO_LARGE = -2013,
  // @aidl-doc
  /** Crypto resources are temporarily exceeded, so a retry is likely to succeed. */
  ERROR_DRM_RESOURCE_CONTENTION = -2014,
  // @aidl-doc
  /** The session was used after the crypto hardware state was invalidated. */
  ERROR_DRM_SESSION_LOST_STATE = -2015,
  // @aidl-doc
  /** The device is in a state where it is not able to perform the operation. */
  ERROR_DRM_INVALID_STATE = -2016,
  // @aidl-doc
  /** The certificate is malformed or is of the wrong type. */
  ERROR_DRM_CERTIFICATE_MALFORMED = -2017,
  // @aidl-doc
  /** The certificate has not been set. */
  ERROR_DRM_CERTIFICATE_MISSING = -2018,
  // @aidl-doc
  /** An error occurred in the crypto library used by the drm plugin. */
  ERROR_DRM_CRYPTO_LIBRARY = -2019,
  // @aidl-doc
  /** A non-specific error was reported by the device OEM subsystem. */
  ERROR_DRM_GENERIC_OEM = -2020,
  // @aidl-doc
  /** An unexpected internal failure occurred in the drm or crypto plugin. */
  ERROR_DRM_GENERIC_PLUGIN = -2021,
  // @aidl-doc
  /** The init data passed to the key request is empty or invalid. */
  ERROR_DRM_INIT_DATA = -2022,
  // @aidl-doc
  /** The key was not loaded from the license, or the key ID is incorrect. */
  ERROR_DRM_KEY_NOT_LOADED = -2023,
  // @aidl-doc
  /** The license response was empty, has missing fields, or could not be parsed. */
  ERROR_DRM_LICENSE_PARSE = -2024,
  // @aidl-doc
  /** The operation is prohibited by the license policy. */
  ERROR_DRM_LICENSE_POLICY = -2025,
  // @aidl-doc
  /** A release request could not be generated because a field in the stored license is empty or malformed. */
  ERROR_DRM_LICENSE_RELEASE = -2026,
  // @aidl-doc
  /** The license server detected an error in the license request. */
  ERROR_DRM_LICENSE_REQUEST_REJECTED = -2027,
  // @aidl-doc
  /** An offline license could not be restored because a field is empty or malformed. */
  ERROR_DRM_LICENSE_RESTORE = -2028,
  // @aidl-doc
  /** The license is in an invalid state for the attempted operation. */
  ERROR_DRM_LICENSE_STATE = -2029,
  // @aidl-doc
  /** A failure occurred in the media framework. */
  ERROR_DRM_MEDIA_FRAMEWORK = -2030,
  // @aidl-doc
  /** There was an error loading the provisioned certificate. */
  ERROR_DRM_PROVISIONING_CERTIFICATE = -2031,
  // @aidl-doc
  /** Required steps were not performed before provisioning was attempted. */
  ERROR_DRM_PROVISIONING_CONFIG = -2032,
  // @aidl-doc
  /** The provisioning response was empty, has missing fields, or could not be parsed. */
  ERROR_DRM_PROVISIONING_PARSE = -2033,
  // @aidl-doc
  /** The provisioning server detected an error in the provisioning request. */
  ERROR_DRM_PROVISIONING_REQUEST_REJECTED = -2034,
  // @aidl-doc
  /** Provisioning failed in a way that is likely to succeed on a subsequent attempt. */
  ERROR_DRM_PROVISIONING_RETRY = -2035,
  // @aidl-doc
  /** A secure stop request could not be generated because a field in the stored license is empty or malformed. */
  ERROR_DRM_SECURE_STOP_RELEASE = -2036,
  // @aidl-doc
  /** The plugin was unable to read data from the filesystem. */
  ERROR_DRM_STORAGE_READ = -2037,
  // @aidl-doc
  /** The plugin was unable to write data to the filesystem. */
  ERROR_DRM_STORAGE_WRITE = -2038,
  // @aidl-doc
  /** Secure input was queued with zero subsamples. */
  ERROR_DRM_ZERO_SUBSAMPLES = -2039,
  // @aidl-doc
  /** The last error code in use. */
  ERROR_DRM_LAST_USED_ERRORCODE = -2039,
  // @aidl-doc
  /** The upper end of the range reserved for vendor-specific errors. */
  ERROR_DRM_VENDOR_MAX = -2500,
  // @aidl-doc
  /** The lower end of the range reserved for vendor-specific errors. */
  ERROR_DRM_VENDOR_MIN = -2999,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(DrmErrors val) {
  switch(val) {
  case DrmErrors::DRM_ERROR_BASE:
    return "DRM_ERROR_BASE";
  case DrmErrors::ERROR_DRM_NO_LICENSE:
    return "ERROR_DRM_NO_LICENSE";
  case DrmErrors::ERROR_DRM_LICENSE_EXPIRED:
    return "ERROR_DRM_LICENSE_EXPIRED";
  case DrmErrors::ERROR_DRM_SESSION_NOT_OPENED:
    return "ERROR_DRM_SESSION_NOT_OPENED";
  case DrmErrors::ERROR_DRM_DECRYPT_UNIT_NOT_INITIALIZED:
    return "ERROR_DRM_DECRYPT_UNIT_NOT_INITIALIZED";
  case DrmErrors::ERROR_DRM_DECRYPT:
    return "ERROR_DRM_DECRYPT";
  case DrmErrors::ERROR_DRM_CANNOT_HANDLE:
    return "ERROR_DRM_CANNOT_HANDLE";
  case DrmErrors::ERROR_DRM_TAMPER_DETECTED:
    return "ERROR_DRM_TAMPER_DETECTED";
  case DrmErrors::ERROR_DRM_NOT_PROVISIONED:
    return "ERROR_DRM_NOT_PROVISIONED";
  case DrmErrors::ERROR_DRM_DEVICE_REVOKED:
    return "ERROR_DRM_DEVICE_REVOKED";
  case DrmErrors::ERROR_DRM_RESOURCE_BUSY:
    return "ERROR_DRM_RESOURCE_BUSY";
  case DrmErrors::ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION:
    return "ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION";
  case DrmErrors::ERROR_DRM_INSUFFICIENT_SECURITY:
    return "ERROR_DRM_INSUFFICIENT_SECURITY";
  case DrmErrors::ERROR_DRM_FRAME_TOO_LARGE:
    return "ERROR_DRM_FRAME_TOO_LARGE";
  case DrmErrors::ERROR_DRM_RESOURCE_CONTENTION:
    return "ERROR_DRM_RESOURCE_CONTENTION";
  case DrmErrors::ERROR_DRM_SESSION_LOST_STATE:
    return "ERROR_DRM_SESSION_LOST_STATE";
  case DrmErrors::ERROR_DRM_INVALID_STATE:
    return "ERROR_DRM_INVALID_STATE";
  case DrmErrors::ERROR_DRM_CERTIFICATE_MALFORMED:
    return "ERROR_DRM_CERTIFICATE_MALFORMED";
  case DrmErrors::ERROR_DRM_CERTIFICATE_MISSING:
    return "ERROR_DRM_CERTIFICATE_MISSING";
  case DrmErrors::ERROR_DRM_CRYPTO_LIBRARY:
    return "ERROR_DRM_CRYPTO_LIBRARY";
  case DrmErrors::ERROR_DRM_GENERIC_OEM:
    return "ERROR_DRM_GENERIC_OEM";
  case DrmErrors::ERROR_DRM_GENERIC_PLUGIN:
    return "ERROR_DRM_GENERIC_PLUGIN";
  case DrmErrors::ERROR_DRM_INIT_DATA:
    return "ERROR_DRM_INIT_DATA";
  case DrmErrors::ERROR_DRM_KEY_NOT_LOADED:
    return "ERROR_DRM_KEY_NOT_LOADED";
  case DrmErrors::ERROR_DRM_LICENSE_PARSE:
    return "ERROR_DRM_LICENSE_PARSE";
  case DrmErrors::ERROR_DRM_LICENSE_POLICY:
    return "ERROR_DRM_LICENSE_POLICY";
  case DrmErrors::ERROR_DRM_LICENSE_RELEASE:
    return "ERROR_DRM_LICENSE_RELEASE";
  case DrmErrors::ERROR_DRM_LICENSE_REQUEST_REJECTED:
    return "ERROR_DRM_LICENSE_REQUEST_REJECTED";
  case DrmErrors::ERROR_DRM_LICENSE_RESTORE:
    return "ERROR_DRM_LICENSE_RESTORE";
  case DrmErrors::ERROR_DRM_LICENSE_STATE:
    return "ERROR_DRM_LICENSE_STATE";
  case DrmErrors::ERROR_DRM_MEDIA_FRAMEWORK:
    return "ERROR_DRM_MEDIA_FRAMEWORK";
  case DrmErrors::ERROR_DRM_PROVISIONING_CERTIFICATE:
    return "ERROR_DRM_PROVISIONING_CERTIFICATE";
  case DrmErrors::ERROR_DRM_PROVISIONING_CONFIG:
    return "ERROR_DRM_PROVISIONING_CONFIG";
  case DrmErrors::ERROR_DRM_PROVISIONING_PARSE:
    return "ERROR_DRM_PROVISIONING_PARSE";
  case DrmErrors::ERROR_DRM_PROVISIONING_REQUEST_REJECTED:
    return "ERROR_DRM_PROVISIONING_REQUEST_REJECTED";
  case DrmErrors::ERROR_DRM_PROVISIONING_RETRY:
    return "ERROR_DRM_PROVISIONING_RETRY";
  case DrmErrors::ERROR_DRM_SECURE_STOP_RELEASE:
    return "ERROR_DRM_SECURE_STOP_RELEASE";
  case DrmErrors::ERROR_DRM_STORAGE_READ:
    return "ERROR_DRM_STORAGE_READ";
  case DrmErrors::ERROR_DRM_STORAGE_WRITE:
    return "ERROR_DRM_STORAGE_WRITE";
  case DrmErrors::ERROR_DRM_ZERO_SUBSAMPLES:
    return "ERROR_DRM_ZERO_SUBSAMPLES";
  case DrmErrors::ERROR_DRM_VENDOR_MAX:
    return "ERROR_DRM_VENDOR_MAX";
  case DrmErrors::ERROR_DRM_VENDOR_MIN:
    return "ERROR_DRM_VENDOR_MIN";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::drm::DrmErrors, 44> enum_values<::com::rdk::hal::drm::DrmErrors> = {
  ::com::rdk::hal::drm::DrmErrors::DRM_ERROR_BASE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_UNKNOWN,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_NO_LICENSE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LICENSE_EXPIRED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_SESSION_NOT_OPENED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_DECRYPT_UNIT_NOT_INITIALIZED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_DECRYPT,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_CANNOT_HANDLE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_TAMPER_DETECTED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_NOT_PROVISIONED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_DEVICE_REVOKED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_RESOURCE_BUSY,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_INSUFFICIENT_SECURITY,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_FRAME_TOO_LARGE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_RESOURCE_CONTENTION,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_SESSION_LOST_STATE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_INVALID_STATE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_CERTIFICATE_MALFORMED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_CERTIFICATE_MISSING,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_CRYPTO_LIBRARY,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_GENERIC_OEM,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_GENERIC_PLUGIN,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_INIT_DATA,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_KEY_NOT_LOADED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LICENSE_PARSE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LICENSE_POLICY,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LICENSE_RELEASE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LICENSE_REQUEST_REJECTED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LICENSE_RESTORE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LICENSE_STATE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_MEDIA_FRAMEWORK,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_PROVISIONING_CERTIFICATE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_PROVISIONING_CONFIG,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_PROVISIONING_PARSE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_PROVISIONING_REQUEST_REJECTED,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_PROVISIONING_RETRY,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_SECURE_STOP_RELEASE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_STORAGE_READ,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_STORAGE_WRITE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_ZERO_SUBSAMPLES,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_LAST_USED_ERRORCODE,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_VENDOR_MAX,
  ::com::rdk::hal::drm::DrmErrors::ERROR_DRM_VENDOR_MIN,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
