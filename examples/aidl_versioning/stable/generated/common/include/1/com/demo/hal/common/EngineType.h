#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace demo {
namespace hal {
namespace common {
enum class EngineType : int32_t {
  PETROL = 0,
  DIESEL = 1,
};
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
namespace com {
namespace demo {
namespace hal {
namespace common {
[[nodiscard]] static inline std::string toString(EngineType val) {
  switch(val) {
  case EngineType::PETROL:
    return "PETROL";
  case EngineType::DIESEL:
    return "DIESEL";
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
constexpr inline std::array<::com::demo::hal::common::EngineType, 2> enum_values<::com::demo::hal::common::EngineType> = {
  ::com::demo::hal::common::EngineType::PETROL,
  ::com::demo::hal::common::EngineType::DIESEL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
