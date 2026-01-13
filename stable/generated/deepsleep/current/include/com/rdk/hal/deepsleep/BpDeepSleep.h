#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/deepsleep/IDeepSleep.h>

namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
class BpDeepSleep : public ::android::BpInterface<IDeepSleep> {
public:
  explicit BpDeepSleep(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDeepSleep() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::deepsleep::Capabilities* _aidl_return) override;
  ::android::binder::Status enterDeepSleep(const ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>& triggersToWakeUpon, ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>* wokeUpByTriggers, ::std::optional<::com::rdk::hal::deepsleep::KeyCode>* keyCode, bool* _aidl_return) override;
  ::android::binder::Status setWakeUpTimer(int32_t seconds, bool* _aidl_return) override;
  ::android::binder::Status getWakeUpTimer(int32_t* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDeepSleep
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
