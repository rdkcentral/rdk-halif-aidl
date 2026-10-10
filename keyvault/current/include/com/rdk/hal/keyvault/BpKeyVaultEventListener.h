#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/keyvault/IKeyVaultEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class BpKeyVaultEventListener : public ::android::BpInterface<IKeyVaultEventListener> {
public:
  explicit BpKeyVaultEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpKeyVaultEventListener() = default;
  ::android::binder::Status onVaultStateChanged(::com::rdk::hal::keyvault::VaultState state) override;
  ::android::binder::Status onKeyExpired(const ::std::string& alias) override;
  ::android::binder::Status onKeyInvalidated(const ::std::string& alias) override;
  ::android::binder::Status onKeyRotated(const ::std::string& alias, int32_t newVersion) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpKeyVaultEventListener
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
