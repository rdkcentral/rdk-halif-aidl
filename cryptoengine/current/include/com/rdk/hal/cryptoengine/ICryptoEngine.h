#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/EngineCapabilities.h>
#include <com/rdk/hal/cryptoengine/ICryptoEngineController.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class ICryptoEngine : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CryptoEngine)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::cryptoengine::EngineCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status open(::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>& controller, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICryptoEngine

class ICryptoEngineDefault : public ICryptoEngine {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::cryptoengine::EngineCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICryptoEngineDefault
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
