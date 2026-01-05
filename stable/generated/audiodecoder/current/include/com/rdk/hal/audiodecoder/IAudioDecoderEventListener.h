#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/ErrorCode.h>
#include <com/rdk/hal/audiodecoder/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class IAudioDecoderEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "cc94c1ee2e601adf7110f14537ecc115ffc83ed9";
  static constexpr char* HASHVALUE = "cc94c1ee2e601adf7110f14537ecc115ffc83ed9";
  virtual ::android::binder::Status onDecodeError(::com::rdk::hal::audiodecoder::ErrorCode errorCode, int32_t vendorErrorCode) = 0;
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::audiodecoder::State oldState, ::com::rdk::hal::audiodecoder::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoderEventListener

class IAudioDecoderEventListenerDefault : public IAudioDecoderEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onDecodeError(::com::rdk::hal::audiodecoder::ErrorCode /*errorCode*/, int32_t /*vendorErrorCode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiodecoder::State /*oldState*/, ::com::rdk::hal::audiodecoder::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderEventListenerDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
