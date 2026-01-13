#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/deepsleep/Capabilities.h>
#include <com/rdk/hal/deepsleep/KeyCode.h>
#include <com/rdk/hal/deepsleep/WakeUpTrigger.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
class IDeepSleep : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DeepSleep)
  static const int32_t VERSION = 1;
  const std::string HASH = "e0d5ad156ab90a805d64e9b6a5fbc77512b97725";
  static constexpr char* HASHVALUE = "e0d5ad156ab90a805d64e9b6a5fbc77512b97725";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::deepsleep::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status enterDeepSleep(const ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>& triggersToWakeUpon, ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>* wokeUpByTriggers, ::std::optional<::com::rdk::hal::deepsleep::KeyCode>* keyCode, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setWakeUpTimer(int32_t seconds, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getWakeUpTimer(int32_t* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDeepSleep

class IDeepSleepDefault : public IDeepSleep {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::deepsleep::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status enterDeepSleep(const ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>& /*triggersToWakeUpon*/, ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>* /*wokeUpByTriggers*/, ::std::optional<::com::rdk::hal::deepsleep::KeyCode>* /*keyCode*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setWakeUpTimer(int32_t /*seconds*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getWakeUpTimer(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDeepSleepDefault
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
