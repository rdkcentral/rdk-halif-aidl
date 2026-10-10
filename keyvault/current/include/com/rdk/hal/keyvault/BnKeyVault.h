#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/keyvault/IKeyVault.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class BnKeyVault : public ::android::BnInterface<IKeyVault> {
public:
  static constexpr uint32_t TRANSACTION_getVaultNames = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getSecurityLevel = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_createVault = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_destroyVault = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnKeyVault();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnKeyVault

class IKeyVaultDelegator : public BnKeyVault {
public:
  explicit IKeyVaultDelegator(::android::sp<IKeyVault> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getVaultNames(::std::vector<::std::string>* _aidl_return) override {
    return _aidl_delegate->getVaultNames(_aidl_return);
  }
  ::android::binder::Status getSecurityLevel(const ::std::string& vaultName, ::com::rdk::hal::cryptoengine::SecurityLevel* _aidl_return) override {
    return _aidl_delegate->getSecurityLevel(vaultName, _aidl_return);
  }
  ::android::binder::Status open(const ::std::string& vaultName, const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener, ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>* _aidl_return) override {
    return _aidl_delegate->open(vaultName, listener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>& controller, bool* _aidl_return) override {
    return _aidl_delegate->close(controller, _aidl_return);
  }
  ::android::binder::Status createVault(const ::std::string& vaultName, ::com::rdk::hal::cryptoengine::SecurityLevel securityLevel, int32_t maxKeys, bool* _aidl_return) override {
    return _aidl_delegate->createVault(vaultName, securityLevel, maxKeys, _aidl_return);
  }
  ::android::binder::Status destroyVault(const ::std::string& vaultName, bool* _aidl_return) override {
    return _aidl_delegate->destroyVault(vaultName, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnKeyVault::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IKeyVault> _aidl_delegate;
};  // class IKeyVaultDelegator
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
