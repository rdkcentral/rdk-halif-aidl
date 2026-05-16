#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/CryptoSchemes.h>
#include <com/rdk/hal/drm/ICryptoPlugin.h>
#include <com/rdk/hal/drm/IDrmPlugin.h>
#include <com/rdk/hal/drm/Uuid.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class IDrmFactory : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DrmFactory)
  static const int32_t VERSION = 1;
  const std::string HASH = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  static constexpr char* HASHVALUE = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  virtual ::android::binder::Status createDrmPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::android::String16& appPackageName, ::android::sp<::com::rdk::hal::drm::IDrmPlugin>* _aidl_return) = 0;
  virtual ::android::binder::Status createCryptoPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::std::vector<uint8_t>& initData, ::android::sp<::com::rdk::hal::drm::ICryptoPlugin>* _aidl_return) = 0;
  virtual ::android::binder::Status getSupportedCryptoSchemes(::com::rdk::hal::drm::CryptoSchemes* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDrmFactory

class IDrmFactoryDefault : public IDrmFactory {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status createDrmPlugin(const ::com::rdk::hal::drm::Uuid& /*uuid*/, const ::android::String16& /*appPackageName*/, ::android::sp<::com::rdk::hal::drm::IDrmPlugin>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createCryptoPlugin(const ::com::rdk::hal::drm::Uuid& /*uuid*/, const ::std::vector<uint8_t>& /*initData*/, ::android::sp<::com::rdk::hal::drm::ICryptoPlugin>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSupportedCryptoSchemes(::com::rdk::hal::drm::CryptoSchemes* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDrmFactoryDefault
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
