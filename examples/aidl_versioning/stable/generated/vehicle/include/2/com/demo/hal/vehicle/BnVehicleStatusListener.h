#pragma once

#include <binder/IInterface.h>
#include <com/demo/hal/vehicle/IVehicleStatusListener.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class BnVehicleStatusListener : public ::android::BnInterface<IVehicleStatusListener> {
public:
  static constexpr uint32_t TRANSACTION_onVehicleStatusChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVehicleStatusListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVehicleStatusListener

class IVehicleStatusListenerDelegator : public BnVehicleStatusListener {
public:
  explicit IVehicleStatusListenerDelegator(::android::sp<IVehicleStatusListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onVehicleStatusChanged(const ::com::demo::hal::vehicle::VehicleStatus& status) override {
    return _aidl_delegate->onVehicleStatusChanged(status);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVehicleStatusListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVehicleStatusListener> _aidl_delegate;
};  // class IVehicleStatusListenerDelegator
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com
