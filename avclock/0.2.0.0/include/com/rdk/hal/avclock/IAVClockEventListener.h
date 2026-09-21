#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/avclock/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class IAVClockEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockEventListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "746091a1d249271c6ce051d120d292928e6491ab";
  static constexpr char* HASHVALUE = "746091a1d249271c6ce051d120d292928e6491ab";
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::avclock::State oldState, ::com::rdk::hal::avclock::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockEventListener

class IAVClockEventListenerDefault : public IAVClockEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::avclock::State /*oldState*/, ::com::rdk::hal::avclock::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockEventListenerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
