#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief Composite input signal status.
 *
 * Describes the current state of the composite video signal detection.
 */
enum class SignalStatus : int32_t {
  // @aidl-doc
  /** No signal detected on the port. */
  NO_SIGNAL = 0,
  // @aidl-doc
  /** Signal detected but unstable or not locked. */
  UNSTABLE = 1,
  // @aidl-doc
  /** Signal detected but format is not supported. */
  NOT_SUPPORTED = 2,
  // @aidl-doc
  /** Signal detected, locked, and stable. */
  STABLE = 3,
};
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
[[nodiscard]] static inline std::string toString(SignalStatus val) {
  switch(val) {
  case SignalStatus::NO_SIGNAL:
    return "NO_SIGNAL";
  case SignalStatus::UNSTABLE:
    return "UNSTABLE";
  case SignalStatus::NOT_SUPPORTED:
    return "NOT_SUPPORTED";
  case SignalStatus::STABLE:
    return "STABLE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::compositeinput::SignalStatus, 4> enum_values<::com::rdk::hal::compositeinput::SignalStatus> = {
  ::com::rdk::hal::compositeinput::SignalStatus::NO_SIGNAL,
  ::com::rdk::hal::compositeinput::SignalStatus::UNSTABLE,
  ::com::rdk::hal::compositeinput::SignalStatus::NOT_SUPPORTED,
  ::com::rdk::hal::compositeinput::SignalStatus::STABLE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
