#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/Algorithm.h>
#include <com/rdk/hal/cryptoengine/CryptoConfig.h>
#include <com/rdk/hal/cryptoengine/ICryptoEngineController.h>
#include <com/rdk/hal/cryptoengine/KeyType.h>
#include <com/rdk/hal/keyvault/DerivedKeySpec.h>
#include <com/rdk/hal/keyvault/IKeyVaultEventListener.h>
#include <com/rdk/hal/keyvault/KeyDescriptor.h>
#include <com/rdk/hal/keyvault/VaultCapabilities.h>
#include <com/rdk/hal/keyvault/VaultState.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class IKeyVaultController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(KeyVaultController)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status attachCryptoEngine(const ::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>& engine) = 0;
  virtual ::android::binder::Status detachCryptoEngine() = 0;
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::keyvault::VaultCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getVaultState(::com::rdk::hal::keyvault::VaultState* _aidl_return) = 0;
  virtual ::android::binder::Status generateKey(const ::std::string& alias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, int32_t keySizeBits, int32_t usages, bool extractable, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) = 0;
  virtual ::android::binder::Status generateKeyPair(const ::std::string& publicAlias, const ::std::string& privateAlias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, int32_t keySizeBits, int32_t usages, bool extractable, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) = 0;
  virtual ::android::binder::Status importKey(const ::std::string& alias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, ::com::rdk::hal::cryptoengine::KeyType keyType, const ::std::vector<uint8_t>& keyData, int32_t usages, bool extractable, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) = 0;
  virtual ::android::binder::Status exportKey(const ::std::string& alias, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status deleteKey(const ::std::string& alias) = 0;
  virtual ::android::binder::Status deleteAllKeys() = 0;
  virtual ::android::binder::Status rotateKey(const ::std::string& alias, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) = 0;
  virtual ::android::binder::Status listKeys(::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) = 0;
  virtual ::android::binder::Status getKeyInfo(const ::std::string& alias, ::std::optional<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) = 0;
  virtual ::android::binder::Status deriveIntoVault(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::string& sourceKeyAlias, const ::std::optional<::std::vector<uint8_t>>& peerPublicKey, const ::std::vector<::com::rdk::hal::keyvault::DerivedKeySpec>& outputKeys, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) = 0;
  virtual ::android::binder::Status flush() = 0;
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener) = 0;
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IKeyVaultController

class IKeyVaultControllerDefault : public IKeyVaultController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status attachCryptoEngine(const ::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>& /*engine*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status detachCryptoEngine() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::keyvault::VaultCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVaultState(::com::rdk::hal::keyvault::VaultState* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status generateKey(const ::std::string& /*alias*/, ::com::rdk::hal::cryptoengine::Algorithm /*algorithm*/, int32_t /*keySizeBits*/, int32_t /*usages*/, bool /*extractable*/, ::com::rdk::hal::keyvault::KeyDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status generateKeyPair(const ::std::string& /*publicAlias*/, const ::std::string& /*privateAlias*/, ::com::rdk::hal::cryptoengine::Algorithm /*algorithm*/, int32_t /*keySizeBits*/, int32_t /*usages*/, bool /*extractable*/, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status importKey(const ::std::string& /*alias*/, ::com::rdk::hal::cryptoengine::Algorithm /*algorithm*/, ::com::rdk::hal::cryptoengine::KeyType /*keyType*/, const ::std::vector<uint8_t>& /*keyData*/, int32_t /*usages*/, bool /*extractable*/, ::com::rdk::hal::keyvault::KeyDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status exportKey(const ::std::string& /*alias*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status deleteKey(const ::std::string& /*alias*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status deleteAllKeys() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status rotateKey(const ::std::string& /*alias*/, ::com::rdk::hal::keyvault::KeyDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status listKeys(::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getKeyInfo(const ::std::string& /*alias*/, ::std::optional<::com::rdk::hal::keyvault::KeyDescriptor>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status deriveIntoVault(const ::com::rdk::hal::cryptoengine::CryptoConfig& /*config*/, const ::std::string& /*sourceKeyAlias*/, const ::std::optional<::std::vector<uint8_t>>& /*peerPublicKey*/, const ::std::vector<::com::rdk::hal::keyvault::DerivedKeySpec>& /*outputKeys*/, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IKeyVaultControllerDefault
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
