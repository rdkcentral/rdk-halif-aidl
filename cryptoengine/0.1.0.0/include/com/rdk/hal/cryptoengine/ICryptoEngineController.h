#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/CryptoConfig.h>
#include <com/rdk/hal/cryptoengine/Digest.h>
#include <com/rdk/hal/cryptoengine/ICryptoOperation.h>
#include <com/rdk/hal/cryptoengine/KeyPurpose.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class ICryptoEngineController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CryptoEngineController)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status begin(::com::rdk::hal::cryptoengine::KeyPurpose purpose, const ::com::rdk::hal::cryptoengine::CryptoConfig& config, ::android::sp<::com::rdk::hal::cryptoengine::ICryptoOperation>* _aidl_return) = 0;
  virtual ::android::binder::Status computeDigest(::com::rdk::hal::cryptoengine::Digest digest, const ::std::vector<uint8_t>& data, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status computeHmac(::com::rdk::hal::cryptoengine::Digest digest, const ::std::vector<uint8_t>& key, const ::std::vector<uint8_t>& data, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status encrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::vector<uint8_t>& plaintext, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status decrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::vector<uint8_t>& ciphertext, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status generateRandom(int32_t length, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICryptoEngineController

class ICryptoEngineControllerDefault : public ICryptoEngineController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status begin(::com::rdk::hal::cryptoengine::KeyPurpose /*purpose*/, const ::com::rdk::hal::cryptoengine::CryptoConfig& /*config*/, ::android::sp<::com::rdk::hal::cryptoengine::ICryptoOperation>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status computeDigest(::com::rdk::hal::cryptoengine::Digest /*digest*/, const ::std::vector<uint8_t>& /*data*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status computeHmac(::com::rdk::hal::cryptoengine::Digest /*digest*/, const ::std::vector<uint8_t>& /*key*/, const ::std::vector<uint8_t>& /*data*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status encrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& /*config*/, const ::std::vector<uint8_t>& /*plaintext*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status decrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& /*config*/, const ::std::vector<uint8_t>& /*ciphertext*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status generateRandom(int32_t /*length*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICryptoEngineControllerDefault
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
