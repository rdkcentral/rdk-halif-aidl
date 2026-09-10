#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/bootreason/IBootReason.h>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
class BpBootReason : public ::android::BpInterface<IBootReason> {
public:
  explicit BpBootReason(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBootReason() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::bootreason::Capabilities* _aidl_return) override;
  ::android::binder::Status getBootCause(::com::rdk::hal::bootreason::BootCause* _aidl_return) override;
  ::android::binder::Status setBootCause(::com::rdk::hal::bootreason::BootCause cause, const ::android::String16& reasonString) override;
  ::android::binder::Status reboot(::com::rdk::hal::bootreason::ResetType resetType, const ::android::String16& reasonString) override;
  ::android::binder::Status getPowerSource(::com::rdk::hal::bootreason::PowerSource* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpBootReason
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
