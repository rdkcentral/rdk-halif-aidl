#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiodecoder/CSDAudioFormat.h>
#include <com/rdk/hal/audiodecoder/InputBufferMetadata.h>
#include <com/rdk/hal/audiodecoder/Property.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class IAudioDecoderController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderController)
  static const int32_t VERSION = 1;
  const std::string HASH = "d1b99af228345a73442defd7876f5d3c03ed3013";
  static constexpr char* HASHVALUE = "d1b99af228345a73442defd7876f5d3c03ed3013";
  virtual ::android::binder::Status setProperty(::com::rdk::hal::audiodecoder::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status decodeBufferWithMetadata(int64_t bufferHandle, const ::com::rdk::hal::audiodecoder::InputBufferMetadata& metadata, bool* _aidl_return) = 0;
  virtual ::android::binder::Status flush(bool reset) = 0;
  virtual ::android::binder::Status signalDiscontinuity() = 0;
  virtual ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::audiodecoder::CSDAudioFormat csdAudioFormat, const ::std::vector<uint8_t>& codecData, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setAudioFormat(int32_t channels, int32_t sampleRate) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoderController

class IAudioDecoderControllerDefault : public IAudioDecoderController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiodecoder::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status decodeBufferWithMetadata(int64_t /*bufferHandle*/, const ::com::rdk::hal::audiodecoder::InputBufferMetadata& /*metadata*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush(bool /*reset*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signalDiscontinuity() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::audiodecoder::CSDAudioFormat /*csdAudioFormat*/, const ::std::vector<uint8_t>& /*codecData*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAudioFormat(int32_t /*channels*/, int32_t /*sampleRate*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderControllerDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
