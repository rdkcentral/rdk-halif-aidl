#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/demo/hal/vehicle/IVehicleStatusListener.h>
#include <com/demo/hal/vehicle/VehicleSpecs.h>
#include <com/demo/hal/vehicle/VehicleStatus.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class IVehicle : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Vehicle)
  static const int32_t VERSION = 2;
  const std::string HASH = "7851b76373f7299c21887de48f4d7c108dc25e4e";
  static constexpr char* HASHVALUE = "7851b76373f7299c21887de48f4d7c108dc25e4e";
  virtual ::android::binder::Status getVehicleSpecs(::com::demo::hal::vehicle::VehicleSpecs* _aidl_return) = 0;
  virtual ::android::binder::Status getVehicleStatus(::com::demo::hal::vehicle::VehicleStatus* _aidl_return) = 0;
  virtual ::android::binder::Status startVehicleEngine() = 0;
  virtual ::android::binder::Status stopVehicleEngine() = 0;
  virtual ::android::binder::Status startMoving() = 0;
  virtual ::android::binder::Status stopMoving() = 0;
  virtual ::android::binder::Status registerVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& listener) = 0;
  virtual ::android::binder::Status unregisterVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& listener) = 0;
  virtual ::android::binder::Status lockVehicle() = 0;
  virtual ::android::binder::Status unlockVehicle() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVehicle

class IVehicleDefault : public IVehicle {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getVehicleSpecs(::com::demo::hal::vehicle::VehicleSpecs* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVehicleStatus(::com::demo::hal::vehicle::VehicleStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status startVehicleEngine() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stopVehicleEngine() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status startMoving() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stopMoving() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status lockVehicle() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unlockVehicle() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVehicleDefault
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com
