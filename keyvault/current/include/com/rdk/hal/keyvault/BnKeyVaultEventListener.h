#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/keyvault/IKeyVaultEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class BnKeyVaultEventListener : public ::android::BnInterface<IKeyVaultEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onVaultStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onKeyExpired = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onKeyInvalidated = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onKeyRotated = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnKeyVaultEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnKeyVaultEventListener

class IKeyVaultEventListenerDelegator : public BnKeyVaultEventListener {
public:
  explicit IKeyVaultEventListenerDelegator(::android::sp<IKeyVaultEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onVaultStateChanged(::com::rdk::hal::keyvault::VaultState state) override {
    return _aidl_delegate->onVaultStateChanged(state);
  }
  ::android::binder::Status onKeyExpired(const ::std::string& alias) override {
    return _aidl_delegate->onKeyExpired(alias);
  }
  ::android::binder::Status onKeyInvalidated(const ::std::string& alias) override {
    return _aidl_delegate->onKeyInvalidated(alias);
  }
  ::android::binder::Status onKeyRotated(const ::std::string& alias, int32_t newVersion) override {
    return _aidl_delegate->onKeyRotated(alias, newVersion);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnKeyVaultEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IKeyVaultEventListener> _aidl_delegate;
};  // class IKeyVaultEventListenerDelegator
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
