#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/keyvault/VaultState.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class IKeyVaultEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(KeyVaultEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status onVaultStateChanged(::com::rdk::hal::keyvault::VaultState state) = 0;
  virtual ::android::binder::Status onKeyExpired(const ::std::string& alias) = 0;
  virtual ::android::binder::Status onKeyInvalidated(const ::std::string& alias) = 0;
  virtual ::android::binder::Status onKeyRotated(const ::std::string& alias, int32_t newVersion) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IKeyVaultEventListener

class IKeyVaultEventListenerDefault : public IKeyVaultEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onVaultStateChanged(::com::rdk::hal::keyvault::VaultState /*state*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onKeyExpired(const ::std::string& /*alias*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onKeyInvalidated(const ::std::string& /*alias*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onKeyRotated(const ::std::string& /*alias*/, int32_t /*newVersion*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IKeyVaultEventListenerDefault
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
