#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/demo/hal/vehicle/IVehicle.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class BpVehicle : public ::android::BpInterface<IVehicle> {
public:
  explicit BpVehicle(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVehicle() = default;
  ::android::binder::Status getVehicleSpecs(::com::demo::hal::vehicle::VehicleSpecs* _aidl_return) override;
  ::android::binder::Status getVehicleStatus(::com::demo::hal::vehicle::VehicleStatus* _aidl_return) override;
  ::android::binder::Status startVehicleEngine() override;
  ::android::binder::Status stopVehicleEngine() override;
  ::android::binder::Status startMoving() override;
  ::android::binder::Status stopMoving() override;
  ::android::binder::Status registerVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& listener) override;
  ::android::binder::Status unregisterVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& listener) override;
  ::android::binder::Status lockVehicle() override;
  ::android::binder::Status unlockVehicle() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVehicle
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com
