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
namespace audiosink {
class IAudioSinkEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioSinkEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "2c1b84b1b69a8f134c625cde43cdcc185d464a99";
  static constexpr char* HASHVALUE = "2c1b84b1b69a8f134c625cde43cdcc185d464a99";
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) = 0;
  virtual ::android::binder::Status onFirstFrameRendered(int64_t nsPresentationTime) = 0;
  virtual ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) = 0;
  virtual ::android::binder::Status onAudioUnderflow() = 0;
  virtual ::android::binder::Status onAudioResumed(int64_t nsPresentationTime) = 0;
  virtual ::android::binder::Status onFlushComplete() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioSinkEventListener

class IAudioSinkEventListenerDefault : public IAudioSinkEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::State /*oldState*/, ::com::rdk::hal::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFirstFrameRendered(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEndOfStream(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAudioUnderflow() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAudioResumed(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFlushComplete() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioSinkEventListenerDefault
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
