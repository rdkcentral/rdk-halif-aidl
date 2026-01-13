#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace demo {
namespace hal {
namespace common {
enum class TransmissionType : int32_t {
  MANUAL = 0,
};
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
namespace com {
namespace demo {
namespace hal {
namespace common {
[[nodiscard]] static inline std::string toString(TransmissionType val) {
  switch(val) {
  case TransmissionType::MANUAL:
    return "MANUAL";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::demo::hal::common::TransmissionType, 1> enum_values<::com::demo::hal::common::TransmissionType> = {
  ::com::demo::hal::common::TransmissionType::MANUAL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
