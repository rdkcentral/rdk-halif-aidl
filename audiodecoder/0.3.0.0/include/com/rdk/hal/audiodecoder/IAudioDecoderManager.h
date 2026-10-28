#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoder.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     Audio Decoder Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IAudioDecoderManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderManager)
  static const int32_t VERSION = 3000;
  const std::string HASH = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  static constexpr char* HASHVALUE = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Get all audio decoder resource IDs.
   *
   * The list of audio decoders is static in the system and does not change
   * between calls.
   *
   * @param[out] _aidl_return IAudioDecoder.Id[]
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getAudioDecoderIds(::std::vector<::com::rdk::hal::audiodecoder::IAudioDecoder::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets an audio decoder resource index interface.
   *
   * @param[in] decoderResourceId     The ID of the audio decoder resource.
   *
   * @param[out] _aidl_return IAudioDecoder which can be null if the resource index is invalid.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& decoderResourceId, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoder>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoderManager

class IAudioDecoderManagerDefault : public IAudioDecoderManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAudioDecoderIds(::std::vector<::com::rdk::hal::audiodecoder::IAudioDecoder::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& /*decoderResourceId*/, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoder>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderManagerDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
