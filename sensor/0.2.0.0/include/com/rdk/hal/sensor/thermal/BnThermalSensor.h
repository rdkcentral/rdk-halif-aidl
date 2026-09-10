#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/sensor/thermal/IThermalSensor.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class BnThermalSensor : public ::android::BnInterface<IThermalSensor> {
public:
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getCurrentThermalState = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getCurrentTemperatures = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnThermalSensor();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnThermalSensor

class IThermalSensorDelegator : public BnThermalSensor {
public:
  explicit IThermalSensorDelegator(::android::sp<IThermalSensor> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) override {
    return _aidl_delegate->registerEventListener(listener, _aidl_return);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterEventListener(listener, _aidl_return);
  }
  ::android::binder::Status getCurrentThermalState(::com::rdk::hal::sensor::thermal::State* _aidl_return) override {
    return _aidl_delegate->getCurrentThermalState(_aidl_return);
  }
  ::android::binder::Status getCurrentTemperatures(::std::vector<::com::rdk::hal::sensor::thermal::TemperatureReading>* _aidl_return) override {
    return _aidl_delegate->getCurrentTemperatures(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnThermalSensor::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IThermalSensor> _aidl_delegate;
};  // class IThermalSensorDelegator
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
