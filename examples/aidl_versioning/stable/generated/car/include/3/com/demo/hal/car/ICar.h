#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/demo/hal/car/CarSpecs.h>
#include <com/demo/hal/car/CarStatus.h>
#include <com/demo/hal/car/ICarStatusListener.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class ICar : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Car)
  static const int32_t VERSION = 3;
  const std::string HASH = "28ca573b15863492751d159acf149320968aa09b";
  static constexpr char* HASHVALUE = "28ca573b15863492751d159acf149320968aa09b";
  virtual ::android::binder::Status getCarSpecs(::com::demo::hal::car::CarSpecs* _aidl_return) = 0;
  virtual ::android::binder::Status getCarStatus(::com::demo::hal::car::CarStatus* _aidl_return) = 0;
  virtual ::android::binder::Status startCarEngine() = 0;
  virtual ::android::binder::Status stopCarEngine() = 0;
  virtual ::android::binder::Status registerCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) = 0;
  virtual ::android::binder::Status unregisterCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) = 0;
  virtual ::android::binder::Status lockCar() = 0;
  virtual ::android::binder::Status unlockCar() = 0;
  virtual ::android::binder::Status resetCarDashboard() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICar

class ICarDefault : public ICar {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCarSpecs(::com::demo::hal::car::CarSpecs* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCarStatus(::com::demo::hal::car::CarStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status startCarEngine() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stopCarEngine() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status lockCar() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unlockCar() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status resetCarDashboard() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICarDefault
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
