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
// @aidl-doc
/**
 * IDrmPluginListener is a listener interface for Drm events sent from an
 * IDrmPlugin instance.
 */
class IDrmPluginListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DrmPluginListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "ef9f0fd6c9a0c25f700ad00f124132011c6de297";
  static constexpr char* HASHVALUE = "ef9f0fd6c9a0c25f700ad00f124132011c6de297";
  // @aidl-doc
  /**
   * Legacy event sending method, it sends events of various types using a
   * single overloaded set of parameters. This form is deprecated.
   *
   * @param eventType the type of the event
   * @param sessionId identifies the session the event originated from
   * @param data event-specific data blob
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEvent(::com::rdk::hal::drm::EventType eventType, const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& data) = 0;
  // @aidl-doc
  /**
   * Send a license expiration update to the listener. The expiration
   * update indicates how long the current keys are valid before they
   * need to be renewed.
   *
   * @param sessionId identifies the session the event originated from
   * @param expiryTimeInMS the time when the keys need to be renewed.
   * The time is in milliseconds, relative to the Unix epoch. A time
   * of 0 indicates that the keys never expire.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onExpirationUpdate(const ::std::vector<uint8_t>& sessionId, int64_t expiryTimeInMS) = 0;
  // @aidl-doc
  /**
   * Send a keys change event to the listener. The keys change event
   * indicates the status of each key in the session. Keys can be
   * indicated as being usable, expired, outputnotallowed or statuspending.
   *
   * @param sessionId identifies the session the event originated from
   * @param keyStatusList indicates the status for each key ID in the
   * session.
   * @param hasNewUsableKey indicates if the event includes at least one
   * key that has become usable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onKeysChange(const ::std::vector<uint8_t>& sessionId, const ::std::vector<::com::rdk::hal::drm::KeyStatus>& keyStatusList, bool hasNewUsableKey) = 0;
  // @aidl-doc
  /**
   * Some device crypto hardware is incapable of retaining crypto
   * session state across suspend and resume cycles. A
   * SessionLostState event must be signaled when a session has
   * become invalid for this reason. This event must not be used to
   * indicate a failure in the crypto system. Closing the session
   * and opening a new one must allow the application to resume
   * normal use of the drm hal module.
   *
   * @param sessionId identifies the session that has been invalidated
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
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
