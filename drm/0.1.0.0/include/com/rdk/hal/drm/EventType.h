#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
enum class EventType : int32_t {
  PROVISION_REQUIRED = 0,
  KEY_NEEDED = 1,
  KEY_EXPIRED = 2,
  VENDOR_DEFINED = 3,
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
