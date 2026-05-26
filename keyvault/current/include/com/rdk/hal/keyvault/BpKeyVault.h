#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/keyvault/IKeyVault.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class BpKeyVault : public ::android::BpInterface<IKeyVault> {
public:
  explicit BpKeyVault(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpKeyVault() = default;
  ::android::binder::Status getVaultNames(::std::vector<::std::string>* _aidl_return) override;
  ::android::binder::Status getSecurityLevel(const ::std::string& vaultName, ::com::rdk::hal::cryptoengine::SecurityLevel* _aidl_return) override;
  ::android::binder::Status open(const ::std::string& vaultName, const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener, ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>& controller, bool* _aidl_return) override;
  ::android::binder::Status createVault(const ::std::string& vaultName, ::com::rdk::hal::cryptoengine::SecurityLevel securityLevel, int32_t maxKeys, bool* _aidl_return) override;
  ::android::binder::Status destroyVault(const ::std::string& vaultName, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpKeyVault
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
