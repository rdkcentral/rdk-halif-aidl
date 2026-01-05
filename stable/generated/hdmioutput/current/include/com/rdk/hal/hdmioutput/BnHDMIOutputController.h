#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputController.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BnHDMIOutputController : public ::android::BnInterface<IHDMIOutputController> {
public:
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getHotPlugDetectState = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_setPropertyMulti = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getHDCPCurrentVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getHDCPReceiverVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getHDCPStatus = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_setSPDInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getSPDInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIOutputController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIOutputController

class IHDMIOutputControllerDelegator : public BnHDMIOutputController {
public:
  explicit IHDMIOutputControllerDelegator(::android::sp<IHDMIOutputController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status start() override {
    return _aidl_delegate->start();
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status getHotPlugDetectState(bool* _aidl_return) override {
    return _aidl_delegate->getHotPlugDetectState(_aidl_return);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::hdmioutput::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(property, propertyValue, _aidl_return);
  }
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmioutput::PropertyKVPair>& propertyKVList, bool* _aidl_return) override {
    return _aidl_delegate->setPropertyMulti(propertyKVList, _aidl_return);
  }
  ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) override {
    return _aidl_delegate->getHDCPCurrentVersion(_aidl_return);
  }
  ::android::binder::Status getHDCPReceiverVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) override {
    return _aidl_delegate->getHDCPReceiverVersion(_aidl_return);
  }
  ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmioutput::HDCPStatus* _aidl_return) override {
    return _aidl_delegate->getHDCPStatus(_aidl_return);
  }
  ::android::binder::Status setSPDInfoFrame(const ::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>& spdInfoFrame) override {
    return _aidl_delegate->setSPDInfoFrame(spdInfoFrame);
  }
  ::android::binder::Status getSPDInfoFrame(::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>* _aidl_return) override {
    return _aidl_delegate->getSPDInfoFrame(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIOutputController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIOutputController> _aidl_delegate;
};  // class IHDMIOutputControllerDelegator
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
