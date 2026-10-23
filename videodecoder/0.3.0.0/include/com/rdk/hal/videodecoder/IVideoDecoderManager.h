#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/IVideoDecoder.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Video Decoder Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */
class IVideoDecoderManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderManager)
  static const int32_t VERSION = 3000;
  const std::string HASH = "922cc8ec92962ec7843061aae427af80fb4c37a1";
  static constexpr char* HASHVALUE = "922cc8ec92962ec7843061aae427af80fb4c37a1";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the platform list of Video Decoder IDs.
   *
   * @param[out] _aidl_return IVideoDecoder.Id[]
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getVideoDecoderIds(::std::vector<::com::rdk::hal::videodecoder::IVideoDecoder::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a Video Decoder interface.
   *
   * @param[in] videoDecoderId	The ID of the video decoder.
   *
   * @param[out] _aidl_return IVideoDecoder or null if the ID is invalid.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoder>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderManager

class IVideoDecoderManagerDefault : public IVideoDecoderManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getVideoDecoderIds(::std::vector<::com::rdk::hal::videodecoder::IVideoDecoder::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& /*videoDecoderId*/, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoder>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoDecoderManagerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
