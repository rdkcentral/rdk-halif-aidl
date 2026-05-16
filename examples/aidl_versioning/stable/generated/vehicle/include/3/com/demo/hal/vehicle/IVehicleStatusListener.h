#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/demo/hal/vehicle/VehicleStatus.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class IVehicleStatusListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VehicleStatusListener)
  static const int32_t VERSION = 3;
  const std::string HASH = "6558de0adad222857a6ba683301ed012bda98dd6";
  static constexpr char* HASHVALUE = "6558de0adad222857a6ba683301ed012bda98dd6";
  virtual ::android::binder::Status onVehicleStatusChanged(const ::com::demo::hal::vehicle::VehicleStatus& status) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVehicleStatusListener

class IVehicleStatusListenerDefault : public IVehicleStatusListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onVehicleStatusChanged(const ::com::demo::hal::vehicle::VehicleStatus& /*status*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVehicleStatusListenerDefault
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com
