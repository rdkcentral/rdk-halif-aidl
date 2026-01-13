#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/demo/hal/car/ICar.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class BpCar : public ::android::BpInterface<ICar> {
public:
  explicit BpCar(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCar() = default;
  ::android::binder::Status getCarSpecs(::com::demo::hal::car::CarSpecs* _aidl_return) override;
  ::android::binder::Status getCarStatus(::com::demo::hal::car::CarStatus* _aidl_return) override;
  ::android::binder::Status startCarEngine() override;
  ::android::binder::Status stopCarEngine() override;
  ::android::binder::Status registerCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) override;
  ::android::binder::Status unregisterCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) override;
  ::android::binder::Status lockCar() override;
  ::android::binder::Status unlockCar() override;
  ::android::binder::Status resetCarDashboard() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCar
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
