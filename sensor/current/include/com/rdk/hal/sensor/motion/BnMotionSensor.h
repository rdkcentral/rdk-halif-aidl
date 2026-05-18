#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/sensor/motion/IMotionSensor.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BnMotionSensor : public ::android::BnInterface<IMotionSensor> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnMotionSensor();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnMotionSensor

class IMotionSensorDelegator : public BnMotionSensor {
public:
  explicit IMotionSensorDelegator(::android::sp<IMotionSensor> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::sensor::motion::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getState(::com::rdk::hal::sensor::motion::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorControllerListener>& listener, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>* _aidl_return) override {
    return _aidl_delegate->open(listener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>& controller, bool* _aidl_return) override {
    return _aidl_delegate->close(controller, _aidl_return);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) override {
    return _aidl_delegate->registerEventListener(motionSensorEventListener, _aidl_return);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterEventListener(motionSensorEventListener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnMotionSensor::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IMotionSensor> _aidl_delegate;
};  // class IMotionSensorDelegator
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
