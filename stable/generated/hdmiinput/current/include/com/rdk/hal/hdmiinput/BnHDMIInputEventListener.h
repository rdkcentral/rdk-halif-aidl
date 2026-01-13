#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BnHDMIInputEventListener : public ::android::BnInterface<IHDMIInputEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onEDIDChange = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIInputEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIInputEventListener

class IHDMIInputEventListenerDelegator : public BnHDMIInputEventListener {
public:
  explicit IHDMIInputEventListenerDelegator(::android::sp<IHDMIInputEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmiinput::State oldState, ::com::rdk::hal::hdmiinput::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  ::android::binder::Status onEDIDChange(const ::std::vector<uint8_t>& edid) override {
    return _aidl_delegate->onEDIDChange(edid);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIInputEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIInputEventListener> _aidl_delegate;
};  // class IHDMIInputEventListenerDelegator
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
