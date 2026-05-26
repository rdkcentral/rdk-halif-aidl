#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmicec/IHdmiCec.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class BnHdmiCec : public ::android::BnInterface<IHdmiCec> {
public:
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getLogicalAddresses = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHdmiCec();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHdmiCec

class IHdmiCecDelegator : public BnHdmiCec {
public:
  explicit IHdmiCecDelegator(::android::sp<IHdmiCec> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getState(::com::rdk::hal::hdmicec::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::hdmicec::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status getLogicalAddresses(::std::vector<int32_t>* _aidl_return) override {
    return _aidl_delegate->getLogicalAddresses(_aidl_return);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecControllerListener, ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>* _aidl_return) override {
    return _aidl_delegate->open(cecControllerListener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>& hdmiCecController, bool* _aidl_return) override {
    return _aidl_delegate->close(hdmiCecController, _aidl_return);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecEventListener, bool* _aidl_return) override {
    return _aidl_delegate->registerEventListener(cecEventListener, _aidl_return);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecEventListener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterEventListener(cecEventListener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHdmiCec::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHdmiCec> _aidl_delegate;
};  // class IHdmiCecDelegator
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
