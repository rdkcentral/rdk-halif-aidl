#pragma once

#include <binder/IInterface.h>
#include <com/demo/hal/vehicle/IVehicle.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class BnVehicle : public ::android::BnInterface<IVehicle> {
public:
  static constexpr uint32_t TRANSACTION_getVehicleSpecs = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getVehicleStatus = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_startVehicleEngine = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_stopVehicleEngine = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_startMoving = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_stopMoving = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_registerVehicleStatusListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_unregisterVehicleStatusListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_lockVehicle = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_unlockVehicle = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVehicle();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVehicle

class IVehicleDelegator : public BnVehicle {
public:
  explicit IVehicleDelegator(::android::sp<IVehicle> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getVehicleSpecs(::com::demo::hal::vehicle::VehicleSpecs* _aidl_return) override {
    return _aidl_delegate->getVehicleSpecs(_aidl_return);
  }
  ::android::binder::Status getVehicleStatus(::com::demo::hal::vehicle::VehicleStatus* _aidl_return) override {
    return _aidl_delegate->getVehicleStatus(_aidl_return);
  }
  ::android::binder::Status startVehicleEngine() override {
    return _aidl_delegate->startVehicleEngine();
  }
  ::android::binder::Status stopVehicleEngine() override {
    return _aidl_delegate->stopVehicleEngine();
  }
  ::android::binder::Status startMoving() override {
    return _aidl_delegate->startMoving();
  }
  ::android::binder::Status stopMoving() override {
    return _aidl_delegate->stopMoving();
  }
  ::android::binder::Status registerVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& listener) override {
    return _aidl_delegate->registerVehicleStatusListener(listener);
  }
  ::android::binder::Status unregisterVehicleStatusListener(const ::android::sp<::com::demo::hal::vehicle::IVehicleStatusListener>& listener) override {
    return _aidl_delegate->unregisterVehicleStatusListener(listener);
  }
  ::android::binder::Status lockVehicle() override {
    return _aidl_delegate->lockVehicle();
  }
  ::android::binder::Status unlockVehicle() override {
    return _aidl_delegate->unlockVehicle();
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVehicle::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVehicle> _aidl_delegate;
};  // class IVehicleDelegator
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com
