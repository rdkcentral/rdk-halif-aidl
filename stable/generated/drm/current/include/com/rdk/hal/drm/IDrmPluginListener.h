#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/EventType.h>
#include <com/rdk/hal/drm/KeyStatus.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class IDrmPluginListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DrmPluginListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  static constexpr char* HASHVALUE = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  virtual ::android::binder::Status onEvent(::com::rdk::hal::drm::EventType eventType, const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& data) = 0;
  virtual ::android::binder::Status onExpirationUpdate(const ::std::vector<uint8_t>& sessionId, int64_t expiryTimeInMS) = 0;
  virtual ::android::binder::Status onKeysChange(const ::std::vector<uint8_t>& sessionId, const ::std::vector<::com::rdk::hal::drm::KeyStatus>& keyStatusList, bool hasNewUsableKey) = 0;
  virtual ::android::binder::Status onSessionLostState(const ::std::vector<uint8_t>& sessionId) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDrmPluginListener

class IDrmPluginListenerDefault : public IDrmPluginListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onEvent(::com::rdk::hal::drm::EventType /*eventType*/, const ::std::vector<uint8_t>& /*sessionId*/, const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onExpirationUpdate(const ::std::vector<uint8_t>& /*sessionId*/, int64_t /*expiryTimeInMS*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onKeysChange(const ::std::vector<uint8_t>& /*sessionId*/, const ::std::vector<::com::rdk::hal::drm::KeyStatus>& /*keyStatusList*/, bool /*hasNewUsableKey*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onSessionLostState(const ::std::vector<uint8_t>& /*sessionId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDrmPluginListenerDefault
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
