#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class ICryptoOperation : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CryptoOperation)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status update(const ::std::vector<uint8_t>& input, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status finish(const ::std::optional<::std::vector<uint8_t>>& input, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status abort() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICryptoOperation

class ICryptoOperationDefault : public ICryptoOperation {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status update(const ::std::vector<uint8_t>& /*input*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status finish(const ::std::optional<::std::vector<uint8_t>>& /*input*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status abort() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICryptoOperationDefault
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
