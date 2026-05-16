#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/deviceinfo/IDeviceInfo.h>

namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
class BpDeviceInfo : public ::android::BpInterface<IDeviceInfo> {
public:
  explicit BpDeviceInfo(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDeviceInfo() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::deviceinfo::Capabilities* _aidl_return) override;
  ::android::binder::Status getProperty(const ::android::String16& propertyKey, ::std::optional<::com::rdk::hal::deviceinfo::Property>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDeviceInfo
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
