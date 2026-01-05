#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/avclock/IAVClock.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class IAVClockManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  static constexpr char* HASHVALUE = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getAVClockIds(::std::vector<::com::rdk::hal::avclock::IAVClock::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getAVClock(const ::com::rdk::hal::avclock::IAVClock::Id& avClockId, ::android::sp<::com::rdk::hal::avclock::IAVClock>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockManager

class IAVClockManagerDefault : public IAVClockManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAVClockIds(::std::vector<::com::rdk::hal::avclock::IAVClock::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAVClock(const ::com::rdk::hal::avclock::IAVClock::Id& /*avClockId*/, ::android::sp<::com::rdk::hal::avclock::IAVClock>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockManagerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
