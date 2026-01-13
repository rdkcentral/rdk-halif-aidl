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
class IAudioDecoderManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "cc94c1ee2e601adf7110f14537ecc115ffc83ed9";
  static constexpr char* HASHVALUE = "cc94c1ee2e601adf7110f14537ecc115ffc83ed9";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getAudioDecoderIds(::std::vector<::com::rdk::hal::audiodecoder::IAudioDecoder::Id>* _aidl_return) = 0;
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
