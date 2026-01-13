#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/State.h>
#include <com/rdk/hal/videodecoder/ErrorCode.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class IVideoDecoderEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "d83340f728c7a177fbf5dd725b346b3579fd9aab";
  static constexpr char* HASHVALUE = "d83340f728c7a177fbf5dd725b346b3579fd9aab";
  virtual ::android::binder::Status onDecodeError(::com::rdk::hal::videodecoder::ErrorCode errorCode, int32_t vendorErrorCode) = 0;
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderEventListener

class IVideoDecoderEventListenerDefault : public IVideoDecoderEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onDecodeError(::com::rdk::hal::videodecoder::ErrorCode /*errorCode*/, int32_t /*vendorErrorCode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::State /*oldState*/, ::com::rdk::hal::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoDecoderEventListenerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
