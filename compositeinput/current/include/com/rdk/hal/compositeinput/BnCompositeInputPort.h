#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/compositeinput/ICompositeInputPort.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BnCompositeInputPort : public ::android::BnInterface<ICompositeInputPort> {
public:
  static constexpr uint32_t TRANSACTION_getId = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getPortInfo = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getStatus = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getPropertyMulti = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCompositeInputPort();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCompositeInputPort

class ICompositeInputPortDelegator : public BnCompositeInputPort {
public:
  explicit ICompositeInputPortDelegator(::android::sp<ICompositeInputPort> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getId(int32_t* _aidl_return) override {
    return _aidl_delegate->getId(_aidl_return);
  }
  ::android::binder::Status getPortInfo(::com::rdk::hal::compositeinput::Port* _aidl_return) override {
    return _aidl_delegate->getPortInfo(_aidl_return);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::compositeinput::PortCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getState(::com::rdk::hal::compositeinput::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status getStatus(::com::rdk::hal::compositeinput::PortStatus* _aidl_return) override {
    return _aidl_delegate->getStatus(_aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::compositeinput::PortProperty property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PortProperty>& properties, ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>* _aidl_return) override {
    return _aidl_delegate->getPropertyMulti(properties, _aidl_return);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputControllerListener>& listener, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>* _aidl_return) override {
    return _aidl_delegate->open(listener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>& controller, bool* _aidl_return) override {
    return _aidl_delegate->close(controller, _aidl_return);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) override {
    return _aidl_delegate->registerEventListener(listener);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) override {
    return _aidl_delegate->unregisterEventListener(listener);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCompositeInputPort::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICompositeInputPort> _aidl_delegate;
};  // class ICompositeInputPortDelegator
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
