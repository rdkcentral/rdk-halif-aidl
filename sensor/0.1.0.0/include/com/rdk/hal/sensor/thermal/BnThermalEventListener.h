#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/sensor/thermal/IThermalEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class BnThermalEventListener : public ::android::BnInterface<IThermalEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onThermalStateChange = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnThermalEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnThermalEventListener

class IThermalEventListenerDelegator : public BnThermalEventListener {
public:
  explicit IThermalEventListenerDelegator(::android::sp<IThermalEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onThermalStateChange(const ::com::rdk::hal::sensor::thermal::ActionEvent& event) override {
    return _aidl_delegate->onThermalStateChange(event);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnThermalEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IThermalEventListener> _aidl_delegate;
};  // class IThermalEventListenerDelegator
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
