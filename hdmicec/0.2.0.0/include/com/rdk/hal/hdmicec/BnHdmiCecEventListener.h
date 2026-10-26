#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmicec/IHdmiCecEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class BnHdmiCecEventListener : public ::android::BnInterface<IHdmiCecEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onMessageReceived = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onMessageSent = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHdmiCecEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHdmiCecEventListener

class IHdmiCecEventListenerDelegator : public BnHdmiCecEventListener {
public:
  explicit IHdmiCecEventListenerDelegator(::android::sp<IHdmiCecEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onMessageReceived(const ::std::vector<uint8_t>& message) override {
    return _aidl_delegate->onMessageReceived(message);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmicec::State oldState, ::com::rdk::hal::hdmicec::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  ::android::binder::Status onMessageSent(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus status) override {
    return _aidl_delegate->onMessageSent(message, status);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHdmiCecEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHdmiCecEventListener> _aidl_delegate;
};  // class IHdmiCecEventListenerDelegator
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
