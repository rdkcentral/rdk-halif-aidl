#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BnHDMIInputManager : public ::android::BnInterface<IHDMIInputManager> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getHDMIInputIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getHDMIInput = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIInputManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIInputManager

class IHDMIInputManagerDelegator : public BnHDMIInputManager {
public:
  explicit IHDMIInputManagerDelegator(::android::sp<IHDMIInputManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::PlatformCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getHDMIInputIds(::std::vector<::com::rdk::hal::hdmiinput::IHDMIInput::Id>* _aidl_return) override {
    return _aidl_delegate->getHDMIInputIds(_aidl_return);
  }
  ::android::binder::Status getHDMIInput(const ::com::rdk::hal::hdmiinput::IHDMIInput::Id& hdmiInputId, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInput>* _aidl_return) override {
    return _aidl_delegate->getHDMIInput(hdmiInputId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIInputManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIInputManager> _aidl_delegate;
};  // class IHDMIInputManagerDelegator
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
