#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/DecryptArgs.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class ICryptoPlugin : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CryptoPlugin)
  static const int32_t VERSION = 1;
  const std::string HASH = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  static constexpr char* HASHVALUE = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  virtual ::android::binder::Status decrypt(const ::com::rdk::hal::drm::DecryptArgs& args, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status notifyResolution(int32_t width, int32_t height) = 0;
  virtual ::android::binder::Status requiresSecureDecoderComponent(const ::android::String16& mime, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setMediaDrmSession(const ::std::vector<uint8_t>& sessionId) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICryptoPlugin

class ICryptoPluginDefault : public ICryptoPlugin {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status decrypt(const ::com::rdk::hal::drm::DecryptArgs& /*args*/, int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status notifyResolution(int32_t /*width*/, int32_t /*height*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status requiresSecureDecoderComponent(const ::android::String16& /*mime*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setMediaDrmSession(const ::std::vector<uint8_t>& /*sessionId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICryptoPluginDefault
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
