#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/ErrorCode.h>
#include <com/rdk/hal/videodecoder/State.h>
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
  static const int32_t VERSION = 2001;
  const std::string HASH = "52acdb59af5cdef53d7da0c5a3acf3d37c0b8c7c";
  static constexpr char* HASHVALUE = "52acdb59af5cdef53d7da0c5a3acf3d37c0b8c7c";
  virtual ::android::binder::Status onDecodeError(::com::rdk::hal::videodecoder::ErrorCode errorCode, int32_t vendorErrorCode) = 0;
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::videodecoder::State oldState, ::com::rdk::hal::videodecoder::State newState) = 0;
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
  ::android::binder::Status onStateChanged(::com::rdk::hal::videodecoder::State /*oldState*/, ::com::rdk::hal::videodecoder::State /*newState*/) override {
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
