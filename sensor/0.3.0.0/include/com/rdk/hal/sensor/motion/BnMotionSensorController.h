#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorController.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BnMotionSensorController : public ::android::BnInterface<IMotionSensorController> {
public:
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getStartConfig = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getLastEventInfo = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getSensitivity = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_setSensitivity = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_setAutonomousDuringDeepSleep = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_isAutonomousDuringDeepSleepEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_setActiveWindows = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getActiveWindows = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_clearActiveWindows = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnMotionSensorController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnMotionSensorController

class IMotionSensorControllerDelegator : public BnMotionSensorController {
public:
  explicit IMotionSensorControllerDelegator(::android::sp<IMotionSensorController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status start(const ::com::rdk::hal::sensor::motion::StartConfig& config) override {
    return _aidl_delegate->start(config);
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status getStartConfig(::com::rdk::hal::sensor::motion::StartConfig* _aidl_return) override {
    return _aidl_delegate->getStartConfig(_aidl_return);
  }
  ::android::binder::Status getLastEventInfo(::std::optional<::com::rdk::hal::sensor::motion::LastEventInfo>* _aidl_return) override {
    return _aidl_delegate->getLastEventInfo(_aidl_return);
  }
  ::android::binder::Status getSensitivity(int32_t* _aidl_return) override {
    return _aidl_delegate->getSensitivity(_aidl_return);
  }
  ::android::binder::Status setSensitivity(int32_t sensitivity, bool* _aidl_return) override {
    return _aidl_delegate->setSensitivity(sensitivity, _aidl_return);
  }
  ::android::binder::Status setAutonomousDuringDeepSleep(bool enabled, bool* _aidl_return) override {
    return _aidl_delegate->setAutonomousDuringDeepSleep(enabled, _aidl_return);
  }
  ::android::binder::Status isAutonomousDuringDeepSleepEnabled(bool* _aidl_return) override {
    return _aidl_delegate->isAutonomousDuringDeepSleepEnabled(_aidl_return);
  }
  ::android::binder::Status setActiveWindows(const ::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>& windows, bool* _aidl_return) override {
    return _aidl_delegate->setActiveWindows(windows, _aidl_return);
  }
  ::android::binder::Status getActiveWindows(::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>* _aidl_return) override {
    return _aidl_delegate->getActiveWindows(_aidl_return);
  }
  ::android::binder::Status clearActiveWindows(bool* _aidl_return) override {
    return _aidl_delegate->clearActiveWindows(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnMotionSensorController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IMotionSensorController> _aidl_delegate;
};  // class IMotionSensorControllerDelegator
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
