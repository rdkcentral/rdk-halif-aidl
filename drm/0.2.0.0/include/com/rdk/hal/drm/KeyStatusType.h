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
/** The usability status of a key. */
enum class KeyStatusType : int32_t {
  // @aidl-doc
  /** The key is currently usable to decrypt media data. */
  USABLE = 0,
  // @aidl-doc
  /**
   * The key is no longer usable to decrypt media data because its expiration
   * time has passed.
   */
  EXPIRED = 1,
  // @aidl-doc
  /**
   * The key is not currently usable to decrypt media data because its output
   * requirements cannot currently be met.
   */
  OUTPUT_NOT_ALLOWED = 2,
  // @aidl-doc
  /** The status of the key is not yet known and is being determined. */
  STATUS_PENDING = 3,
  // @aidl-doc
  /**
   * The key is not currently usable to decrypt media data because of an
   * internal error in processing unrelated to input parameters.
   */
  INTERNAL_ERROR = 4,
  // @aidl-doc
  /**
   * The key is not yet usable to decrypt media because the start
   * time is in the future. The key must become usable when
   * its start time is reached.
   */
  USABLE_IN_FUTURE = 5,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(KeyStatusType val) {
  switch(val) {
  case KeyStatusType::USABLE:
    return "USABLE";
  case KeyStatusType::EXPIRED:
    return "EXPIRED";
  case KeyStatusType::OUTPUT_NOT_ALLOWED:
    return "OUTPUT_NOT_ALLOWED";
  case KeyStatusType::STATUS_PENDING:
    return "STATUS_PENDING";
  case KeyStatusType::INTERNAL_ERROR:
    return "INTERNAL_ERROR";
  case KeyStatusType::USABLE_IN_FUTURE:
    return "USABLE_IN_FUTURE";
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
constexpr inline std::array<::com::rdk::hal::drm::KeyStatusType, 6> enum_values<::com::rdk::hal::drm::KeyStatusType> = {
  ::com::rdk::hal::drm::KeyStatusType::USABLE,
  ::com::rdk::hal::drm::KeyStatusType::EXPIRED,
  ::com::rdk::hal::drm::KeyStatusType::OUTPUT_NOT_ALLOWED,
  ::com::rdk::hal::drm::KeyStatusType::STATUS_PENDING,
  ::com::rdk::hal::drm::KeyStatusType::INTERNAL_ERROR,
  ::com::rdk::hal::drm::KeyStatusType::USABLE_IN_FUTURE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
