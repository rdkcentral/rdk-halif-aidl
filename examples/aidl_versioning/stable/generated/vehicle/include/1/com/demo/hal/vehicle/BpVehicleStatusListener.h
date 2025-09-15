#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/demo/hal/vehicle/IVehicleStatusListener.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class BpVehicleStatusListener : public ::android::BpInterface<IVehicleStatusListener> {
public:
  explicit BpVehicleStatusListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVehicleStatusListener() = default;
  ::android::binder::Status onVehicleStatusChanged(const ::com::demo::hal::vehicle::VehicleStatus& status) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVehicleStatusListener
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com
