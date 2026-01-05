#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputController.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BnHDMIInputController : public ::android::BnInterface<IHDMIInputController> {
public:
  static constexpr uint32_t TRANSACTION_getConnectionState = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_setPropertyMulti = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_setEDID = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIInputController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIInputController

class IHDMIInputControllerDelegator : public BnHDMIInputController {
public:
  explicit IHDMIInputControllerDelegator(::android::sp<IHDMIInputController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getConnectionState(bool* _aidl_return) override {
    return _aidl_delegate->getConnectionState(_aidl_return);
  }
  ::android::binder::Status start() override {
    return _aidl_delegate->start();
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status setProperty(::com::rdk::hal::hdmiinput::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(property, propertyValue, _aidl_return);
  }
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmiinput::PropertyKVPair>& propertyKVList, bool* _aidl_return) override {
    return _aidl_delegate->setPropertyMulti(propertyKVList, _aidl_return);
  }
  ::android::binder::Status setEDID(const ::std::vector<uint8_t>& edid, bool* _aidl_return) override {
    return _aidl_delegate->setEDID(edid, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIInputController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIInputController> _aidl_delegate;
};  // class IHDMIInputControllerDelegator
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
