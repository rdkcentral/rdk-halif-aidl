#pragma once

#include <binder/IInterface.h>
#include <com/demo/hal/car/ICarStatusListener.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class BnCarStatusListener : public ::android::BnInterface<ICarStatusListener> {
public:
  static constexpr uint32_t TRANSACTION_onCarStatusChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCarStatusListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCarStatusListener

class ICarStatusListenerDelegator : public BnCarStatusListener {
public:
  explicit ICarStatusListenerDelegator(::android::sp<ICarStatusListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onCarStatusChanged(const ::com::demo::hal::car::CarStatus& newStatus) override {
    return _aidl_delegate->onCarStatusChanged(newStatus);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCarStatusListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICarStatusListener> _aidl_delegate;
};  // class ICarStatusListenerDelegator
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
