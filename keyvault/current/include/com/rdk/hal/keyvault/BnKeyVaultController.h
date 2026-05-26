#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/keyvault/IKeyVaultController.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class BnKeyVaultController : public ::android::BnInterface<IKeyVaultController> {
public:
  static constexpr uint32_t TRANSACTION_attachCryptoEngine = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_detachCryptoEngine = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getVaultState = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_generateKey = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_generateKeyPair = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_importKey = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_exportKey = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_deleteKey = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_deleteAllKeys = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_rotateKey = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_listKeys = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_getKeyInfo = ::android::IBinder::FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_deriveIntoVault = ::android::IBinder::FIRST_CALL_TRANSACTION + 13;
  static constexpr uint32_t TRANSACTION_flush = ::android::IBinder::FIRST_CALL_TRANSACTION + 14;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 15;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 16;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnKeyVaultController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnKeyVaultController

class IKeyVaultControllerDelegator : public BnKeyVaultController {
public:
  explicit IKeyVaultControllerDelegator(::android::sp<IKeyVaultController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status attachCryptoEngine(const ::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>& engine) override {
    return _aidl_delegate->attachCryptoEngine(engine);
  }
  ::android::binder::Status detachCryptoEngine() override {
    return _aidl_delegate->detachCryptoEngine();
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::keyvault::VaultCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getVaultState(::com::rdk::hal::keyvault::VaultState* _aidl_return) override {
    return _aidl_delegate->getVaultState(_aidl_return);
  }
  ::android::binder::Status generateKey(const ::std::string& alias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, int32_t keySizeBits, int32_t usages, bool extractable, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) override {
    return _aidl_delegate->generateKey(alias, algorithm, keySizeBits, usages, extractable, _aidl_return);
  }
  ::android::binder::Status generateKeyPair(const ::std::string& publicAlias, const ::std::string& privateAlias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, int32_t keySizeBits, int32_t usages, bool extractable, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override {
    return _aidl_delegate->generateKeyPair(publicAlias, privateAlias, algorithm, keySizeBits, usages, extractable, _aidl_return);
  }
  ::android::binder::Status importKey(const ::std::string& alias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, ::com::rdk::hal::cryptoengine::KeyType keyType, const ::std::vector<uint8_t>& keyData, int32_t usages, bool extractable, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) override {
    return _aidl_delegate->importKey(alias, algorithm, keyType, keyData, usages, extractable, _aidl_return);
  }
  ::android::binder::Status exportKey(const ::std::string& alias, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->exportKey(alias, _aidl_return);
  }
  ::android::binder::Status deleteKey(const ::std::string& alias) override {
    return _aidl_delegate->deleteKey(alias);
  }
  ::android::binder::Status deleteAllKeys() override {
    return _aidl_delegate->deleteAllKeys();
  }
  ::android::binder::Status rotateKey(const ::std::string& alias, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) override {
    return _aidl_delegate->rotateKey(alias, _aidl_return);
  }
  ::android::binder::Status listKeys(::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override {
    return _aidl_delegate->listKeys(_aidl_return);
  }
  ::android::binder::Status getKeyInfo(const ::std::string& alias, ::std::optional<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override {
    return _aidl_delegate->getKeyInfo(alias, _aidl_return);
  }
  ::android::binder::Status deriveIntoVault(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::string& sourceKeyAlias, const ::std::optional<::std::vector<uint8_t>>& peerPublicKey, const ::std::vector<::com::rdk::hal::keyvault::DerivedKeySpec>& outputKeys, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override {
    return _aidl_delegate->deriveIntoVault(config, sourceKeyAlias, peerPublicKey, outputKeys, _aidl_return);
  }
  ::android::binder::Status flush() override {
    return _aidl_delegate->flush();
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener) override {
    return _aidl_delegate->registerEventListener(listener);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener) override {
    return _aidl_delegate->unregisterEventListener(listener);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnKeyVaultController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IKeyVaultController> _aidl_delegate;
};  // class IKeyVaultControllerDelegator
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
