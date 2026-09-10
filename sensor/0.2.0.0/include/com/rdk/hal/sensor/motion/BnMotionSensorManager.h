#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BnMotionSensorManager : public ::android::BnInterface<IMotionSensorManager> {
public:
  static constexpr uint32_t TRANSACTION_getMotionSensorIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getMotionSensor = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnMotionSensorManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnMotionSensorManager

class IMotionSensorManagerDelegator : public BnMotionSensorManager {
public:
  explicit IMotionSensorManagerDelegator(::android::sp<IMotionSensorManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getMotionSensorIds(::std::optional<::std::vector<::std::optional<::com::rdk::hal::sensor::motion::IMotionSensor::Id>>>* _aidl_return) override {
    return _aidl_delegate->getMotionSensorIds(_aidl_return);
  }
  ::android::binder::Status getMotionSensor(const ::com::rdk::hal::sensor::motion::IMotionSensor::Id& motionSensorId, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensor>* _aidl_return) override {
    return _aidl_delegate->getMotionSensor(motionSensorId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnMotionSensorManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IMotionSensorManager> _aidl_delegate;
};  // class IMotionSensorManagerDelegator
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
