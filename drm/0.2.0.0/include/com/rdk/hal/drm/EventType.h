#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
// @aidl-doc
/** EventType enumerates the events that can be delivered by sendEvent */
enum class EventType : int32_t {
  // @aidl-doc
  /**
   * This event type indicates that the app needs to request a certificate
   * from the provisioning server. The request message data is obtained using
   * getProvisionRequest().
   */
  PROVISION_REQUIRED = 0,
  // @aidl-doc
  /**
   * This event type indicates that the app needs to request keys from a
   * license server. The request message data is obtained using getKeyRequest.
   */
  KEY_NEEDED = 1,
  // @aidl-doc
  /**
   * This event type indicates that the licensed usage duration for keys in a
   * session has expired. The keys are no longer valid.
   */
  KEY_EXPIRED = 2,
  // @aidl-doc
  /**
   * This event may indicate some specific vendor-defined condition, see your
   * DRM provider documentation for details.
   */
  VENDOR_DEFINED = 3,
  // @aidl-doc
  /**
   * This event indicates that a session opened by the app has been reclaimed
   * by the resource manager.
   */
  SESSION_RECLAIMED = 4,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(EventType val) {
  switch(val) {
  case EventType::PROVISION_REQUIRED:
    return "PROVISION_REQUIRED";
  case EventType::KEY_NEEDED:
    return "KEY_NEEDED";
  case EventType::KEY_EXPIRED:
    return "KEY_EXPIRED";
  case EventType::VENDOR_DEFINED:
    return "VENDOR_DEFINED";
  case EventType::SESSION_RECLAIMED:
    return "SESSION_RECLAIMED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::drm::EventType, 5> enum_values<::com::rdk::hal::drm::EventType> = {
  ::com::rdk::hal::drm::EventType::PROVISION_REQUIRED,
  ::com::rdk::hal::drm::EventType::KEY_NEEDED,
  ::com::rdk::hal::drm::EventType::KEY_EXPIRED,
  ::com::rdk::hal::drm::EventType::VENDOR_DEFINED,
  ::com::rdk::hal::drm::EventType::SESSION_RECLAIMED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
