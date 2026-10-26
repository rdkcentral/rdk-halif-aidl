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
/** An app determines the type of a key request returned from getKeyRequest. */
enum class KeyRequestType : int32_t {
  // @aidl-doc
  /** Key request type is for an initial license request */
  INITIAL = 0,
  // @aidl-doc
  /**
   * Key request type is for license renewal. Renewal requests are used
   * to extend the validity period for streaming keys.
   */
  RENEWAL = 1,
  // @aidl-doc
  /**
   * Key request type is a release. A key release causes offline keys
   * to become available for streaming.
   */
  RELEASE = 2,
  // @aidl-doc
  /** Key request type is unknown due to some error condition. */
  UNKNOWN = 3,
  // @aidl-doc
  /** Keys are already loaded. No key request is needed. */
  NONE = 4,
  // @aidl-doc
  /**
   * Keys have previously been loaded. An additional (non-renewal) license
   * request is needed.
   */
  UPDATE = 5,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(KeyRequestType val) {
  switch(val) {
  case KeyRequestType::INITIAL:
    return "INITIAL";
  case KeyRequestType::RENEWAL:
    return "RENEWAL";
  case KeyRequestType::RELEASE:
    return "RELEASE";
  case KeyRequestType::UNKNOWN:
    return "UNKNOWN";
  case KeyRequestType::NONE:
    return "NONE";
  case KeyRequestType::UPDATE:
    return "UPDATE";
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
constexpr inline std::array<::com::rdk::hal::drm::KeyRequestType, 6> enum_values<::com::rdk::hal::drm::KeyRequestType> = {
  ::com::rdk::hal::drm::KeyRequestType::INITIAL,
  ::com::rdk::hal::drm::KeyRequestType::RENEWAL,
  ::com::rdk::hal::drm::KeyRequestType::RELEASE,
  ::com::rdk::hal::drm::KeyRequestType::UNKNOWN,
  ::com::rdk::hal::drm::KeyRequestType::NONE,
  ::com::rdk::hal::drm::KeyRequestType::UPDATE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
