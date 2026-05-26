#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace demo {
namespace hal {
namespace common {
enum class FuelType : int32_t {
  PETROL = 0,
  DIESEL = 1,
  ELECTRIC = 2,
};
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
namespace com {
namespace demo {
namespace hal {
namespace common {
[[nodiscard]] static inline std::string toString(FuelType val) {
  switch(val) {
  case FuelType::PETROL:
    return "PETROL";
  case FuelType::DIESEL:
    return "DIESEL";
  case FuelType::ELECTRIC:
    return "ELECTRIC";
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
constexpr inline std::array<::com::demo::hal::common::FuelType, 3> enum_values<::com::demo::hal::common::FuelType> = {
  ::com::demo::hal::common::FuelType::PETROL,
  ::com::demo::hal::common::FuelType::DIESEL,
  ::com::demo::hal::common::FuelType::ELECTRIC,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
