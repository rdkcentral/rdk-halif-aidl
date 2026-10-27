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
/** The status codes used by the drm plugins. */
enum class Status : int32_t {
  // @aidl-doc
  /**
   * The DRM plugin must return OK when an operation completes without any
   * errors.
   */
  OK = 0,
  // @aidl-doc
  /**
   * The DRM plugin must return ERROR_DRM_NO_LICENSE, when decryption is
   * attempted and no license keys have been provided.
   */
  ERROR_DRM_NO_LICENSE = 1,
  // @aidl-doc
  /**
   * ERROR_DRM_LICENSE_EXPIRED must be returned when an attempt is made
   * to use a license and the keys in that license have expired.
   */
  ERROR_DRM_LICENSE_EXPIRED = 2,
  // @aidl-doc
  /**
   * The DRM plugin must return ERROR_DRM_SESSION_NOT_OPENED when an
   * attempt is made to use a session that has not been opened.
   */
  ERROR_DRM_SESSION_NOT_OPENED = 3,
  // @aidl-doc
  /**
   * The DRM plugin must return ERROR_DRM_CANNOT_HANDLE when an unsupported
   * data format or operation is attempted.
   */
  ERROR_DRM_CANNOT_HANDLE = 4,
  // @aidl-doc
  /**
   * ERROR_DRM_INVALID_STATE must be returned when the device is in a state
   * where it is not able to perform decryption.
   */
  ERROR_DRM_INVALID_STATE = 5,
  // @aidl-doc
  /**
   * The DRM plugin must return BAD_VALUE whenever an illegal parameter is
   * passed to one of the interface functions.
   */
  BAD_VALUE = 6,
  // @aidl-doc
  /**
   * The DRM plugin must return ERROR_DRM_NOT_PROVISIONED from getKeyRequest,
   * openSession or provideKeyResponse when the device has not yet been
   * provisioned.
   */
  ERROR_DRM_NOT_PROVISIONED = 7,
  // @aidl-doc
  /**
   * ERROR_DRM_RESOURCE_BUSY must be returned when resources, such as drm
   * sessions or secure buffers are not available to perform a requested
   * operation because they are already in use.
   */
  ERROR_DRM_RESOURCE_BUSY = 8,
  // @aidl-doc
  /**
   * The DRM Plugin must return ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION
   * when the output protection level enabled on the device is not
   * sufficient to meet the requirements in the license policy.  HDCP is an
   * example of a form of output protection.
   */
  ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION = 9,
  // @aidl-doc
  /**
   * The DRM Plugin must return ERROR_DRM_DEVICE_REVOKED from
   * provideProvisionResponse and provideKeyResponse if the response indicates
   * that the device has been revoked. Device revocation means that the device
   * is no longer permitted to play content.
   */
  ERROR_DRM_DEVICE_REVOKED = 10,
  // @aidl-doc
  /**
   * The DRM Plugin must return ERROR_DRM_DECRYPT if the CryptoPlugin
   * decrypt operation fails.
   */
  ERROR_DRM_DECRYPT = 11,
  // @aidl-doc
  /**
   * ERROR_DRM_UNKNOWN must be returned when a fatal failure occurs and no
   * other defined error is appropriate.
   */
  ERROR_DRM_UNKNOWN = 12,
  // @aidl-doc
  /**
   * The drm HAL module must return ERROR_DRM_INSUFFICIENT_SECURITY
   * from the crypto plugin decrypt method when the security level
   * of the device is not sufficient to meet the requirements in the
   * license policy.
   */
  ERROR_DRM_INSUFFICIENT_SECURITY = 13,
  // @aidl-doc
  /**
   * The drm HAL module must return ERROR_FRAME_TOO_LARGE from the
   * decrypt method when the frame being decrypted into the secure
   * output buffer exceeds the size of the buffer.
   */
  ERROR_DRM_FRAME_TOO_LARGE = 14,
  // @aidl-doc
  /**
   * This error must be returned from any session method when an
   * attempt is made to use the session after the crypto hardware
   * state has been invalidated. Some devices are not able to
   * retain crypto session state across device suspend/resume which
   * results in invalid session state.
   */
  ERROR_DRM_SESSION_LOST_STATE = 15,
  // @aidl-doc
  /**
   * The drm HAL module must return this error if client
   * applications using the hal are temporarily exceeding the
   * capacity of available crypto resources such that a retry of
   * the operation is likely to succeed.
   */
  ERROR_DRM_RESOURCE_CONTENTION = 16,
  // @aidl-doc
  /** queueSecureInput buffer called with 0 subsamples. */
  CANNOT_DECRYPT_ZERO_SUBSAMPLES = 17,
  // @aidl-doc
  /** An error happened within the crypto library used by the drm plugin. */
  CRYPTO_LIBRARY_ERROR = 18,
  // @aidl-doc
  /** Non-specific error reported by the device OEM subsystem. */
  GENERAL_OEM_ERROR = 19,
  // @aidl-doc
  /** Unexpected internal failure in the drm/crypto plugin. */
  GENERAL_PLUGIN_ERROR = 20,
  // @aidl-doc
  /** The init data parameter passed to getKeyRequest is empty or invalid. */
  INIT_DATA_INVALID = 21,
  // @aidl-doc
  /**
   * Either the key was not loaded from the license before attempting the
   * operation, or the key ID parameter provided by the app is incorrect.
   */
  KEY_NOT_LOADED = 22,
  // @aidl-doc
  /**
   * The license response was empty, fields are missing or otherwise unable
   * to be parsed.
   */
  LICENSE_PARSE_ERROR = 23,
  // @aidl-doc
  /**
   * The operation (e.g. to renew or persist a license) is prohibited by the
   * license policy.
   */
  LICENSE_POLICY_ERROR = 24,
  // @aidl-doc
  /**
   * Failed to generate a release request because a field in the stored
   * license is empty or malformed.
   */
  LICENSE_RELEASE_ERROR = 25,
  // @aidl-doc
  /** The license server detected an error in the license request. */
  LICENSE_REQUEST_REJECTED = 26,
  // @aidl-doc
  /**
   * Failed to restore an offline license because a field is empty or
   * malformed.
   */
  LICENSE_RESTORE_ERROR = 27,
  // @aidl-doc
  /** License is in an invalid state for the attempted operation. */
  LICENSE_STATE_ERROR = 28,
  // @aidl-doc
  /** Certificate is malformed or is of the wrong type. */
  MALFORMED_CERTIFICATE = 29,
  // @aidl-doc
  /** Failure in the media framework. */
  MEDIA_FRAMEWORK_ERROR = 30,
  // @aidl-doc
  /** Certificate has not been set. */
  MISSING_CERTIFICATE = 31,
  // @aidl-doc
  /** There was an error loading the provisioned certificate. */
  PROVISIONING_CERTIFICATE_ERROR = 32,
  // @aidl-doc
  /** Required steps where not performed before provisioning was attempted. */
  PROVISIONING_CONFIGURATION_ERROR = 33,
  // @aidl-doc
  /**
   * The provisioning response was empty, fields are missing or otherwise
   * unable to be parsed.
   */
  PROVISIONING_PARSE_ERROR = 34,
  // @aidl-doc
  /** The provisioning server detected an error in the provisioning request. */
  PROVISIONING_REQUEST_REJECTED = 35,
  // @aidl-doc
  /**
   * Provisioning failed in a way that is likely to succeed on a subsequent
   * attempt.
   */
  RETRYABLE_PROVISIONING_ERROR = 36,
  // @aidl-doc
  /**
   * Failed to generate a secure stop request because a field in the stored
   * license is empty or malformed.
   */
  SECURE_STOP_RELEASE_ERROR = 37,
  // @aidl-doc
  /** The plugin was unable to read data from the filesystem. */
  STORAGE_READ_FAILURE = 38,
  // @aidl-doc
  /** The plugin was unable to write data to the filesystem. */
  STORAGE_WRITE_FAILURE = 39,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(Status val) {
  switch(val) {
  case Status::OK:
    return "OK";
  case Status::ERROR_DRM_NO_LICENSE:
    return "ERROR_DRM_NO_LICENSE";
  case Status::ERROR_DRM_LICENSE_EXPIRED:
    return "ERROR_DRM_LICENSE_EXPIRED";
  case Status::ERROR_DRM_SESSION_NOT_OPENED:
    return "ERROR_DRM_SESSION_NOT_OPENED";
  case Status::ERROR_DRM_CANNOT_HANDLE:
    return "ERROR_DRM_CANNOT_HANDLE";
  case Status::ERROR_DRM_INVALID_STATE:
    return "ERROR_DRM_INVALID_STATE";
  case Status::BAD_VALUE:
    return "BAD_VALUE";
  case Status::ERROR_DRM_NOT_PROVISIONED:
    return "ERROR_DRM_NOT_PROVISIONED";
  case Status::ERROR_DRM_RESOURCE_BUSY:
    return "ERROR_DRM_RESOURCE_BUSY";
  case Status::ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION:
    return "ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION";
  case Status::ERROR_DRM_DEVICE_REVOKED:
    return "ERROR_DRM_DEVICE_REVOKED";
  case Status::ERROR_DRM_DECRYPT:
    return "ERROR_DRM_DECRYPT";
  case Status::ERROR_DRM_UNKNOWN:
    return "ERROR_DRM_UNKNOWN";
  case Status::ERROR_DRM_INSUFFICIENT_SECURITY:
    return "ERROR_DRM_INSUFFICIENT_SECURITY";
  case Status::ERROR_DRM_FRAME_TOO_LARGE:
    return "ERROR_DRM_FRAME_TOO_LARGE";
  case Status::ERROR_DRM_SESSION_LOST_STATE:
    return "ERROR_DRM_SESSION_LOST_STATE";
  case Status::ERROR_DRM_RESOURCE_CONTENTION:
    return "ERROR_DRM_RESOURCE_CONTENTION";
  case Status::CANNOT_DECRYPT_ZERO_SUBSAMPLES:
    return "CANNOT_DECRYPT_ZERO_SUBSAMPLES";
  case Status::CRYPTO_LIBRARY_ERROR:
    return "CRYPTO_LIBRARY_ERROR";
  case Status::GENERAL_OEM_ERROR:
    return "GENERAL_OEM_ERROR";
  case Status::GENERAL_PLUGIN_ERROR:
    return "GENERAL_PLUGIN_ERROR";
  case Status::INIT_DATA_INVALID:
    return "INIT_DATA_INVALID";
  case Status::KEY_NOT_LOADED:
    return "KEY_NOT_LOADED";
  case Status::LICENSE_PARSE_ERROR:
    return "LICENSE_PARSE_ERROR";
  case Status::LICENSE_POLICY_ERROR:
    return "LICENSE_POLICY_ERROR";
  case Status::LICENSE_RELEASE_ERROR:
    return "LICENSE_RELEASE_ERROR";
  case Status::LICENSE_REQUEST_REJECTED:
    return "LICENSE_REQUEST_REJECTED";
  case Status::LICENSE_RESTORE_ERROR:
    return "LICENSE_RESTORE_ERROR";
  case Status::LICENSE_STATE_ERROR:
    return "LICENSE_STATE_ERROR";
  case Status::MALFORMED_CERTIFICATE:
    return "MALFORMED_CERTIFICATE";
  case Status::MEDIA_FRAMEWORK_ERROR:
    return "MEDIA_FRAMEWORK_ERROR";
  case Status::MISSING_CERTIFICATE:
    return "MISSING_CERTIFICATE";
  case Status::PROVISIONING_CERTIFICATE_ERROR:
    return "PROVISIONING_CERTIFICATE_ERROR";
  case Status::PROVISIONING_CONFIGURATION_ERROR:
    return "PROVISIONING_CONFIGURATION_ERROR";
  case Status::PROVISIONING_PARSE_ERROR:
    return "PROVISIONING_PARSE_ERROR";
  case Status::PROVISIONING_REQUEST_REJECTED:
    return "PROVISIONING_REQUEST_REJECTED";
  case Status::RETRYABLE_PROVISIONING_ERROR:
    return "RETRYABLE_PROVISIONING_ERROR";
  case Status::SECURE_STOP_RELEASE_ERROR:
    return "SECURE_STOP_RELEASE_ERROR";
  case Status::STORAGE_READ_FAILURE:
    return "STORAGE_READ_FAILURE";
  case Status::STORAGE_WRITE_FAILURE:
    return "STORAGE_WRITE_FAILURE";
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
constexpr inline std::array<::com::rdk::hal::drm::Status, 40> enum_values<::com::rdk::hal::drm::Status> = {
  ::com::rdk::hal::drm::Status::OK,
  ::com::rdk::hal::drm::Status::ERROR_DRM_NO_LICENSE,
  ::com::rdk::hal::drm::Status::ERROR_DRM_LICENSE_EXPIRED,
  ::com::rdk::hal::drm::Status::ERROR_DRM_SESSION_NOT_OPENED,
  ::com::rdk::hal::drm::Status::ERROR_DRM_CANNOT_HANDLE,
  ::com::rdk::hal::drm::Status::ERROR_DRM_INVALID_STATE,
  ::com::rdk::hal::drm::Status::BAD_VALUE,
  ::com::rdk::hal::drm::Status::ERROR_DRM_NOT_PROVISIONED,
  ::com::rdk::hal::drm::Status::ERROR_DRM_RESOURCE_BUSY,
  ::com::rdk::hal::drm::Status::ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION,
  ::com::rdk::hal::drm::Status::ERROR_DRM_DEVICE_REVOKED,
  ::com::rdk::hal::drm::Status::ERROR_DRM_DECRYPT,
  ::com::rdk::hal::drm::Status::ERROR_DRM_UNKNOWN,
  ::com::rdk::hal::drm::Status::ERROR_DRM_INSUFFICIENT_SECURITY,
  ::com::rdk::hal::drm::Status::ERROR_DRM_FRAME_TOO_LARGE,
  ::com::rdk::hal::drm::Status::ERROR_DRM_SESSION_LOST_STATE,
  ::com::rdk::hal::drm::Status::ERROR_DRM_RESOURCE_CONTENTION,
  ::com::rdk::hal::drm::Status::CANNOT_DECRYPT_ZERO_SUBSAMPLES,
  ::com::rdk::hal::drm::Status::CRYPTO_LIBRARY_ERROR,
  ::com::rdk::hal::drm::Status::GENERAL_OEM_ERROR,
  ::com::rdk::hal::drm::Status::GENERAL_PLUGIN_ERROR,
  ::com::rdk::hal::drm::Status::INIT_DATA_INVALID,
  ::com::rdk::hal::drm::Status::KEY_NOT_LOADED,
  ::com::rdk::hal::drm::Status::LICENSE_PARSE_ERROR,
  ::com::rdk::hal::drm::Status::LICENSE_POLICY_ERROR,
  ::com::rdk::hal::drm::Status::LICENSE_RELEASE_ERROR,
  ::com::rdk::hal::drm::Status::LICENSE_REQUEST_REJECTED,
  ::com::rdk::hal::drm::Status::LICENSE_RESTORE_ERROR,
  ::com::rdk::hal::drm::Status::LICENSE_STATE_ERROR,
  ::com::rdk::hal::drm::Status::MALFORMED_CERTIFICATE,
  ::com::rdk::hal::drm::Status::MEDIA_FRAMEWORK_ERROR,
  ::com::rdk::hal::drm::Status::MISSING_CERTIFICATE,
  ::com::rdk::hal::drm::Status::PROVISIONING_CERTIFICATE_ERROR,
  ::com::rdk::hal::drm::Status::PROVISIONING_CONFIGURATION_ERROR,
  ::com::rdk::hal::drm::Status::PROVISIONING_PARSE_ERROR,
  ::com::rdk::hal::drm::Status::PROVISIONING_REQUEST_REJECTED,
  ::com::rdk::hal::drm::Status::RETRYABLE_PROVISIONING_ERROR,
  ::com::rdk::hal::drm::Status::SECURE_STOP_RELEASE_ERROR,
  ::com::rdk::hal::drm::Status::STORAGE_READ_FAILURE,
  ::com::rdk::hal::drm::Status::STORAGE_WRITE_FAILURE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
