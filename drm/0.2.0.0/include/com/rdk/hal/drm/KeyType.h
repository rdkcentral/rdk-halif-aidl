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
/** The type of keys being requested. */
enum class KeyType : int32_t {
  // @aidl-doc
  /**
   * Drm keys can be for offline content or for online streaming.
   * Offline keys are persisted on the device and may be used when the device
   * is disconnected from the network.
   */
  OFFLINE = 0,
  // @aidl-doc
  /**
   * Keys for streaming are not persisted and require the device to be
   * connected to the network for periodic renewal.
   */
  STREAMING = 1,
  // @aidl-doc
  /**
   * The Release type is used to request that offline keys be no longer
   * restricted to offline use.
   */
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
