#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmiinput/IHDMIInput.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BnHDMIInput : public ::android::BnInterface<IHDMIInput> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getEDID = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getDefaultEDID = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getHDCPCurrentVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getHDCPStatus = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getSPDInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIInput();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIInput

class IHDMIInputDelegator : public BnHDMIInput {
public:
  explicit IHDMIInputDelegator(::android::sp<IHDMIInput> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::hdmiinput::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status getState(::com::rdk::hal::hdmiinput::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status getEDID(::std::vector<uint8_t>* edid, bool* _aidl_return) override {
    return _aidl_delegate->getEDID(edid, _aidl_return);
  }
  ::android::binder::Status getDefaultEDID(::com::rdk::hal::hdmiinput::HDMIVersion version, ::std::vector<uint8_t>* edid, bool* _aidl_return) override {
    return _aidl_delegate->getDefaultEDID(version, edid, _aidl_return);
  }
  ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmiinput::HDCPProtocolVersion* _aidl_return) override {
    return _aidl_delegate->getHDCPCurrentVersion(_aidl_return);
  }
  ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmiinput::HDCPStatus* _aidl_return) override {
    return _aidl_delegate->getHDCPStatus(_aidl_return);
  }
  ::android::binder::Status getSPDInfoFrame(::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->getSPDInfoFrame(_aidl_return);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputControllerListener>& hdmiInputControllerListener, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>* _aidl_return) override {
    return _aidl_delegate->open(hdmiInputControllerListener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>& hdmiInputController, bool* _aidl_return) override {
    return _aidl_delegate->close(hdmiInputController, _aidl_return);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& hdmiInputEventListener, bool* _aidl_return) override {
    return _aidl_delegate->registerEventListener(hdmiInputEventListener, _aidl_return);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& hdmiInputEventListener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterEventListener(hdmiInputEventListener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIInput::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIInput> _aidl_delegate;
};  // class IHDMIInputDelegator
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
