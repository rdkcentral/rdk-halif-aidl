#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class IVideoSinkEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoSinkEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "4dc98af4f8977cf8c6c7e7f353161287f0b7b106";
  static constexpr char* HASHVALUE = "4dc98af4f8977cf8c6c7e7f353161287f0b7b106";
  virtual ::android::binder::Status onFirstFrameRendered(int64_t nsPresentationTime) = 0;
  virtual ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) = 0;
  virtual ::android::binder::Status onVideoUnderflow() = 0;
  virtual ::android::binder::Status onVideoResumed() = 0;
  virtual ::android::binder::Status onFlushComplete() = 0;
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoSinkEventListener

class IVideoSinkEventListenerDefault : public IVideoSinkEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onFirstFrameRendered(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEndOfStream(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoUnderflow() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoResumed() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFlushComplete() override {
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
};  // class IVideoSinkEventListenerDefault
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
