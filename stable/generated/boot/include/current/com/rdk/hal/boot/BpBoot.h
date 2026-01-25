#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/boot/IBoot.h>

namespace com {
namespace rdk {
namespace hal {
namespace boot {
class BpBoot : public ::android::BpInterface<IBoot> {
public:
  explicit BpBoot(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBoot() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::boot::Capabilities* _aidl_return) override;
  ::android::binder::Status getBootReason(::com::rdk::hal::boot::BootReason* _aidl_return) override;
  ::android::binder::Status setBootReason(::com::rdk::hal::boot::BootReason reason, const ::android::String16& reasonString) override;
  ::android::binder::Status reboot(::com::rdk::hal::boot::ResetType resetType, const ::android::String16& reasonString) override;
  ::android::binder::Status getPowerSource(::com::rdk::hal::boot::PowerSource* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpBoot
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
