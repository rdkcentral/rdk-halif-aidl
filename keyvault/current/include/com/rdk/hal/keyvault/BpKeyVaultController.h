#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/keyvault/IKeyVaultController.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class BpKeyVaultController : public ::android::BpInterface<IKeyVaultController> {
public:
  explicit BpKeyVaultController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpKeyVaultController() = default;
  ::android::binder::Status attachCryptoEngine(const ::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>& engine) override;
  ::android::binder::Status detachCryptoEngine() override;
  ::android::binder::Status getCapabilities(::com::rdk::hal::keyvault::VaultCapabilities* _aidl_return) override;
  ::android::binder::Status getVaultState(::com::rdk::hal::keyvault::VaultState* _aidl_return) override;
  ::android::binder::Status generateKey(const ::std::string& alias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, int32_t keySizeBits, int32_t usages, bool extractable, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) override;
  ::android::binder::Status generateKeyPair(const ::std::string& publicAlias, const ::std::string& privateAlias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, int32_t keySizeBits, int32_t usages, bool extractable, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override;
  ::android::binder::Status importKey(const ::std::string& alias, ::com::rdk::hal::cryptoengine::Algorithm algorithm, ::com::rdk::hal::cryptoengine::KeyType keyType, const ::std::vector<uint8_t>& keyData, int32_t usages, bool extractable, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) override;
  ::android::binder::Status exportKey(const ::std::string& alias, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status deleteKey(const ::std::string& alias) override;
  ::android::binder::Status deleteAllKeys() override;
  ::android::binder::Status rotateKey(const ::std::string& alias, ::com::rdk::hal::keyvault::KeyDescriptor* _aidl_return) override;
  ::android::binder::Status listKeys(::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override;
  ::android::binder::Status getKeyInfo(const ::std::string& alias, ::std::optional<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override;
  ::android::binder::Status deriveIntoVault(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::string& sourceKeyAlias, const ::std::optional<::std::vector<uint8_t>>& peerPublicKey, const ::std::vector<::com::rdk::hal::keyvault::DerivedKeySpec>& outputKeys, ::std::vector<::com::rdk::hal::keyvault::KeyDescriptor>* _aidl_return) override;
  ::android::binder::Status flush() override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpKeyVaultController
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
