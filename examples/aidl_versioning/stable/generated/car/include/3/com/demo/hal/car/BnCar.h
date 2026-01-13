#pragma once

#include <binder/IInterface.h>
#include <com/demo/hal/car/ICar.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class BnCar : public ::android::BnInterface<ICar> {
public:
  static constexpr uint32_t TRANSACTION_getCarSpecs = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getCarStatus = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_startCarEngine = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_stopCarEngine = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_registerCarStatusListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_unregisterCarStatusListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_lockCar = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_unlockCar = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_resetCarDashboard = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCar();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCar

class ICarDelegator : public BnCar {
public:
  explicit ICarDelegator(::android::sp<ICar> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCarSpecs(::com::demo::hal::car::CarSpecs* _aidl_return) override {
    return _aidl_delegate->getCarSpecs(_aidl_return);
  }
  ::android::binder::Status getCarStatus(::com::demo::hal::car::CarStatus* _aidl_return) override {
    return _aidl_delegate->getCarStatus(_aidl_return);
  }
  ::android::binder::Status startCarEngine() override {
    return _aidl_delegate->startCarEngine();
  }
  ::android::binder::Status stopCarEngine() override {
    return _aidl_delegate->stopCarEngine();
  }
  ::android::binder::Status registerCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) override {
    return _aidl_delegate->registerCarStatusListener(listener);
  }
  ::android::binder::Status unregisterCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) override {
    return _aidl_delegate->unregisterCarStatusListener(listener);
  }
  ::android::binder::Status lockCar() override {
    return _aidl_delegate->lockCar();
  }
  ::android::binder::Status unlockCar() override {
    return _aidl_delegate->unlockCar();
  }
  ::android::binder::Status resetCarDashboard() override {
    return _aidl_delegate->resetCarDashboard();
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCar::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICar> _aidl_delegate;
};  // class ICarDelegator
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
