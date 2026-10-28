#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/compositeinput/ICompositeInputEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BnCompositeInputEventListener : public ::android::BnInterface<ICompositeInputEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onPropertyChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCompositeInputEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCompositeInputEventListener

class ICompositeInputEventListenerDelegator : public BnCompositeInputEventListener {
public:
  explicit ICompositeInputEventListenerDelegator(::android::sp<ICompositeInputEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onStateChanged(::com::rdk::hal::compositeinput::State oldState, ::com::rdk::hal::compositeinput::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  ::android::binder::Status onPropertyChanged(::com::rdk::hal::compositeinput::PortProperty property, const ::com::rdk::hal::PropertyValue& value) override {
    return _aidl_delegate->onPropertyChanged(property, value);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCompositeInputEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICompositeInputEventListener> _aidl_delegate;
};  // class ICompositeInputEventListenerDelegator
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
