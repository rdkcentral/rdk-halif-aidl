#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/FrameMetadata.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class IAudioDecoderControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderControllerListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "d1b99af228345a73442defd7876f5d3c03ed3013";
  static constexpr char* HASHVALUE = "d1b99af228345a73442defd7876f5d3c03ed3013";
  virtual ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameAVBufferHandle, const ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata>& metadata) = 0;
  virtual ::android::binder::Status onDecodeBufferAvailable() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoderControllerListener

class IAudioDecoderControllerListenerDefault : public IAudioDecoderControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onFrameOutput(int64_t /*nsPresentationTime*/, int64_t /*frameAVBufferHandle*/, const ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata>& /*metadata*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onDecodeBufferAvailable() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderControllerListenerDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
