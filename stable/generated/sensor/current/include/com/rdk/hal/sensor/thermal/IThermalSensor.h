#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/thermal/IThermalEventListener.h>
#include <com/rdk/hal/sensor/thermal/State.h>
#include <com/rdk/hal/sensor/thermal/TemperatureReading.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class IThermalSensor : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ThermalSensor)
  static const int32_t VERSION = 1;
  const std::string HASH = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static constexpr char* HASHVALUE = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getCurrentThermalState(::com::rdk::hal::sensor::thermal::State* _aidl_return) = 0;
  virtual ::android::binder::Status getCurrentTemperatures(::std::vector<::com::rdk::hal::sensor::thermal::TemperatureReading>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IThermalSensor

class IThermalSensorDefault : public IThermalSensor {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentThermalState(::com::rdk::hal::sensor::thermal::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentTemperatures(::std::vector<::com::rdk::hal::sensor::thermal::TemperatureReading>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IThermalSensorDefault
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
