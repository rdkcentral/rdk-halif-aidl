#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmicec/IHdmiCecController.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class BnHdmiCecController : public ::android::BnInterface<IHdmiCecController> {
public:
  static constexpr uint32_t TRANSACTION_addLogicalAddresses = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_removeLogicalAddresses = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_sendMessage = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHdmiCecController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHdmiCecController

class IHdmiCecControllerDelegator : public BnHdmiCecController {
public:
  explicit IHdmiCecControllerDelegator(::android::sp<IHdmiCecController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status addLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) override {
    return _aidl_delegate->addLogicalAddresses(logicalAddresses, _aidl_return);
  }
  ::android::binder::Status removeLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) override {
    return _aidl_delegate->removeLogicalAddresses(logicalAddresses, _aidl_return);
  }
  ::android::binder::Status sendMessage(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus* _aidl_return) override {
    return _aidl_delegate->sendMessage(message, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHdmiCecController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHdmiCecController> _aidl_delegate;
};  // class IHdmiCecControllerDelegator
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
