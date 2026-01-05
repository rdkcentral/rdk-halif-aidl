#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutput.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BnHDMIOutput : public ::android::BnInterface<IHDMIOutput> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIOutput();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIOutput

class IHDMIOutputDelegator : public BnHDMIOutput {
public:
  explicit IHDMIOutputDelegator(::android::sp<IHDMIOutput> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::hdmioutput::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status getState(::com::rdk::hal::hdmioutput::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputControllerListener>& hdmiOutputControllerListener, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>* _aidl_return) override {
    return _aidl_delegate->open(hdmiOutputControllerListener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>& hdmiOutputController, bool* _aidl_return) override {
    return _aidl_delegate->close(hdmiOutputController, _aidl_return);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& hdmiOutputEventListener, bool* _aidl_return) override {
    return _aidl_delegate->registerEventListener(hdmiOutputEventListener, _aidl_return);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& hdmiOutputEventListener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterEventListener(hdmiOutputEventListener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIOutput::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIOutput> _aidl_delegate;
};  // class IHDMIOutputDelegator
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
