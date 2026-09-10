#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/sensor/thermal/IThermalSensor.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class BpThermalSensor : public ::android::BpInterface<IThermalSensor> {
public:
  explicit BpThermalSensor(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpThermalSensor() = default;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) override;
  ::android::binder::Status getCurrentThermalState(::com::rdk::hal::sensor::thermal::State* _aidl_return) override;
  ::android::binder::Status getCurrentTemperatures(::std::vector<::com::rdk::hal::sensor::thermal::TemperatureReading>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpThermalSensor
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
