#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
enum class DrmErrors : int32_t {
  DRM_ERROR_BASE = -2000,
  ERROR_DRM_UNKNOWN = -2000,
  ERROR_DRM_NO_LICENSE = -2001,
  ERROR_DRM_LICENSE_EXPIRED = -2002,
  ERROR_DRM_SESSION_NOT_OPENED = -2003,
  ERROR_DRM_DECRYPT_UNIT_NOT_INITIALIZED = -2004,
  ERROR_DRM_DECRYPT = -2005,
  ERROR_DRM_CANNOT_HANDLE = -2006,
  ERROR_DRM_TAMPER_DETECTED = -2007,
  ERROR_DRM_NOT_PROVISIONED = -2008,
  ERROR_DRM_DEVICE_REVOKED = -2009,
  ERROR_DRM_RESOURCE_BUSY = -2010,
  ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION = -2011,
  ERROR_DRM_INSUFFICIENT_SECURITY = -2012,
  ERROR_DRM_FRAME_TOO_LARGE = -2013,
  ERROR_DRM_RESOURCE_CONTENTION = -2014,
  ERROR_DRM_SESSION_LOST_STATE = -2015,
  ERROR_DRM_INVALID_STATE = -2016,
  ERROR_DRM_CERTIFICATE_MALFORMED = -2017,
  ERROR_DRM_CERTIFICATE_MISSING = -2018,
  ERROR_DRM_CRYPTO_LIBRARY = -2019,
  ERROR_DRM_GENERIC_OEM = -2020,
  ERROR_DRM_GENERIC_PLUGIN = -2021,
  ERROR_DRM_INIT_DATA = -2022,
  ERROR_DRM_KEY_NOT_LOADED = -2023,
  ERROR_DRM_LICENSE_PARSE = -2024,
  ERROR_DRM_LICENSE_POLICY = -2025,
  ERROR_DRM_LICENSE_RELEASE = -2026,
  ERROR_DRM_LICENSE_REQUEST_REJECTED = -2027,
  ERROR_DRM_LICENSE_RESTORE = -2028,
  ERROR_DRM_LICENSE_STATE = -2029,
  ERROR_DRM_MEDIA_FRAMEWORK = -2030,
  ERROR_DRM_PROVISIONING_CERTIFICATE = -2031,
  ERROR_DRM_PROVISIONING_CONFIG = -2032,
  ERROR_DRM_PROVISIONING_PARSE = -2033,
  ERROR_DRM_PROVISIONING_REQUEST_REJECTED = -2034,
  ERROR_DRM_PROVISIONING_RETRY = -2035,
  ERROR_DRM_SECURE_STOP_RELEASE = -2036,
  ERROR_DRM_STORAGE_READ = -2037,
  ERROR_DRM_STORAGE_WRITE = -2038,
  ERROR_DRM_ZERO_SUBSAMPLES = -2039,
  ERROR_DRM_LAST_USED_ERRORCODE = -2039,
  ERROR_DRM_VENDOR_MAX = -2500,
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
