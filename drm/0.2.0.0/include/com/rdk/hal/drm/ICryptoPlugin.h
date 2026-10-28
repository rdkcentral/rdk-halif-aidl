#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/DecryptArgs.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
// @aidl-doc
/**
 * ICryptoPlugin is the HAL for vendor-provided crypto plugins.
 *
 * It allows crypto sessions to be opened and operated on, to
 * load crypto keys for a codec to decrypt protected video content.
 */
class ICryptoPlugin : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CryptoPlugin)
  static const int32_t VERSION = 2000;
  const std::string HASH = "ef9f0fd6c9a0c25f700ad00f124132011c6de297";
  static constexpr char* HASHVALUE = "ef9f0fd6c9a0c25f700ad00f124132011c6de297";
  // @aidl-doc
  /**
   * Decrypt an array of subsamples from the source memory buffer to the
   * destination memory buffer.
   *
   * Decrypt is a synchronous call.
   * After decryption the source AVBuffer must be recycled/freed by the caller.
   * This approach is the same as Android and is unlike other RDK-E AIDL HALs where the HAL component consumes and
   * frees buffers.
   *
   * @param[in] args The decrypt arguments: key, initialisation vector, crypto mode and pattern, subsamples, and the
   *     source and destination AVBuffer handles.
   *
   * @param[out] _aidl_return Number of decrypted bytes.
   *
   *                 Error codes are returned via binder::status EX_SERVICE_SPECIFIC error codes
   *                     Implicit error codes:
   *                       + ERROR_DRM_CANNOT_HANDLE in other failure cases
   *                       + ERROR_DRM_DECRYPT if the decrypt operation fails
   *                       + ERROR_DRM_FRAME_TOO_LARGE if the frame being decrypted into
   *                             the secure output buffer exceeds the size of the buffer
   *                       + ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION if required output
   *                             protections are not active
   *                       + ERROR_DRM_INSUFFICIENT_SECURITY if the security level of the
   *                             device is not sufficient to meet the requirements in
   *                             the license policy
   *                       + ERROR_DRM_INVALID_STATE if the device is in a state where it
   *                             is not able to perform decryption
   *                       + ERROR_DRM_LICENSE_EXPIRED if the license keys have expired
   *                       + ERROR_DRM_NO_LICENSE if no license keys have been loaded
   *                       + ERROR_DRM_RESOURCE_BUSY if the resources required to perform
   *                             the decryption are not available
   *                       + ERROR_DRM_SESSION_NOT_OPENED if the decrypt session is not
   *                             opened
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status decrypt(const ::com::rdk::hal::drm::DecryptArgs& args, int32_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Notify a plugin of the currently configured resolution.
   *
   * @param width - the display resolution's width
   * @param height - the display resolution's height
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status notifyResolution(int32_t width, int32_t height) = 0;
  // @aidl-doc
  /**
   * Check if the specified mime-type requires a secure decoder
   * component.
   *
   * Video:	video/avc (H.264), video/hevc (H.265), video/x-vnd.on2.vp9, video/av1, video/mp4v-es
   * Audio:	audio/mp4a-latm (AAC), audio/ac3, audio/eac3, audio/vnd.dts, audio/opus
   *
   * @param mime The content mime-type
   * @param[out] _aidl_return must be true only if a secure decoder is required
   *                  for the specified mime-type
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status requiresSecureDecoderComponent(const ::std::string& mime, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Associate a mediadrm session with this crypto session.
   *
   * The session (if known) can be passed in at creation, or this call can be used.
   * Potentially the sessionID can change if there is a key change.
   *
   * @param sessionId the MediaDrm session ID to associate with
   *     this crypto session
   *
   * Errors are reported via binder::status EX_SERVICE_SPECIFIC:
   *     ERROR_DRM_SESSION_NOT_OPENED if the session is not opened, or
   *     ERROR_DRM_CANNOT_HANDLE if the operation is not supported by
   *         the drm scheme
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setMediaDrmSession(const ::std::vector<uint8_t>& sessionId) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICryptoPlugin

class ICryptoPluginDefault : public ICryptoPlugin {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status decrypt(const ::com::rdk::hal::drm::DecryptArgs& /*args*/, int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status notifyResolution(int32_t /*width*/, int32_t /*height*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status requiresSecureDecoderComponent(const ::std::string& /*mime*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setMediaDrmSession(const ::std::vector<uint8_t>& /*sessionId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICryptoPluginDefault
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
