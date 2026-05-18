#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
enum class KeyType : int32_t {
  OFFLINE = 0,
  STREAMING = 1,
  RELEASE = 2,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(KeyType val) {
  switch(val) {
  case KeyType::OFFLINE:
    return "OFFLINE";
  case KeyType::STREAMING:
    return "STREAMING";
  case KeyType::RELEASE:
    return "RELEASE";
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
constexpr inline std::array<::com::rdk::hal::drm::KeyType, 3> enum_values<::com::rdk::hal::drm::KeyType> = {
  ::com::rdk::hal::drm::KeyType::OFFLINE,
  ::com::rdk::hal::drm::KeyType::STREAMING,
  ::com::rdk::hal::drm::KeyType::RELEASE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
