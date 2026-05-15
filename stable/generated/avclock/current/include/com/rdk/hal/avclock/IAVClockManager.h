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
  const std::string HASH = "d051db1ab923600cfd13f483cfb327fb70c083af";
  static constexpr char* HASHVALUE = "d051db1ab923600cfd13f483cfb327fb70c083af";
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
