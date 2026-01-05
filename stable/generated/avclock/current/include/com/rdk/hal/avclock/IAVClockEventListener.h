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
namespace avclock {
class IAVClockEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  static constexpr char* HASHVALUE = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockEventListener

class IAVClockEventListenerDefault : public IAVClockEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
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
};  // class IAVClockEventListenerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
