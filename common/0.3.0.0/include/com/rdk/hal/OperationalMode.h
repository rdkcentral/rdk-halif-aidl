#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
// @aidl-doc
/** @brief The operational output mode currently selected by the vendor. */
enum class OperationalMode : int32_t {
  // @aidl-doc
  /** Output is consumed by the vendor layer and is not returned to the client. */
  TUNNELLED = 1,
  // @aidl-doc
  /** Output is returned to the client. */
  NON_TUNNELLED = 2,
};
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
[[nodiscard]] static inline std::string toString(OperationalMode val) {
  switch(val) {
  case OperationalMode::TUNNELLED:
    return "TUNNELLED";
  case OperationalMode::NON_TUNNELLED:
    return "NON_TUNNELLED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::OperationalMode, 2> enum_values<::com::rdk::hal::OperationalMode> = {
  ::com::rdk::hal::OperationalMode::TUNNELLED,
  ::com::rdk::hal::OperationalMode::NON_TUNNELLED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
