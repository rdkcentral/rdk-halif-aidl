#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/thermal/ActionEvent.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class IThermalEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ThermalEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static constexpr char* HASHVALUE = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  virtual ::android::binder::Status onThermalStateChange(const ::com::rdk::hal::sensor::thermal::ActionEvent& event) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IThermalEventListener

class IThermalEventListenerDefault : public IThermalEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onThermalStateChange(const ::com::rdk::hal::sensor::thermal::ActionEvent& /*event*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IThermalEventListenerDefault
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
