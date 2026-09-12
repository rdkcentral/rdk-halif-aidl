#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/SecurityLevel.h>
#include <com/rdk/hal/keyvault/IKeyVaultController.h>
#include <com/rdk/hal/keyvault/IKeyVaultEventListener.h>
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
class IKeyVault : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(KeyVault)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getVaultNames(::std::vector<::std::string>* _aidl_return) = 0;
  virtual ::android::binder::Status getSecurityLevel(const ::std::string& vaultName, ::com::rdk::hal::cryptoengine::SecurityLevel* _aidl_return) = 0;
  virtual ::android::binder::Status open(const ::std::string& vaultName, const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& listener, ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>& controller, bool* _aidl_return) = 0;
  virtual ::android::binder::Status createVault(const ::std::string& vaultName, ::com::rdk::hal::cryptoengine::SecurityLevel securityLevel, int32_t maxKeys, bool* _aidl_return) = 0;
  virtual ::android::binder::Status destroyVault(const ::std::string& vaultName, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IKeyVault

class IKeyVaultDefault : public IKeyVault {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getVaultNames(::std::vector<::std::string>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSecurityLevel(const ::std::string& /*vaultName*/, ::com::rdk::hal::cryptoengine::SecurityLevel* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::std::string& /*vaultName*/, const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultEventListener>& /*listener*/, ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::keyvault::IKeyVaultController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createVault(const ::std::string& /*vaultName*/, ::com::rdk::hal::cryptoengine::SecurityLevel /*securityLevel*/, int32_t /*maxKeys*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status destroyVault(const ::std::string& /*vaultName*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IKeyVaultDefault
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
