#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/compositeinput/ICompositeInputManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BnCompositeInputManager : public ::android::BnInterface<ICompositeInputManager> {
public:
  static constexpr uint32_t TRANSACTION_getPlatformCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getPortIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getPort = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCompositeInputManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCompositeInputManager

class ICompositeInputManagerDelegator : public BnCompositeInputManager {
public:
  explicit ICompositeInputManagerDelegator(::android::sp<ICompositeInputManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::compositeinput::PlatformCapabilities* _aidl_return) override {
    return _aidl_delegate->getPlatformCapabilities(_aidl_return);
  }
  ::android::binder::Status getPortIds(::std::vector<int32_t>* _aidl_return) override {
    return _aidl_delegate->getPortIds(_aidl_return);
  }
  ::android::binder::Status getPort(int32_t portId, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputPort>* _aidl_return) override {
    return _aidl_delegate->getPort(portId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCompositeInputManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICompositeInputManager> _aidl_delegate;
};  // class ICompositeInputManagerDelegator
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
