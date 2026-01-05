#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
enum class HALError : int32_t {
  SUCCESS = 0,
  BUFFER_FULL = 1,
  INVALID_RESOURCE = 2,
  INVALID_CODEC = 3,
  DEFERRED = 4,
  OUT_OF_MEMORY = 5,
  OUT_OF_BOUNDS = 6,
  NOT_EMPTY = 7,
  INVALID_ARGUMENT = 8,
};
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
[[nodiscard]] static inline std::string toString(HALError val) {
  switch(val) {
  case HALError::SUCCESS:
    return "SUCCESS";
  case HALError::BUFFER_FULL:
    return "BUFFER_FULL";
  case HALError::INVALID_RESOURCE:
    return "INVALID_RESOURCE";
  case HALError::INVALID_CODEC:
    return "INVALID_CODEC";
  case HALError::DEFERRED:
    return "DEFERRED";
  case HALError::OUT_OF_MEMORY:
    return "OUT_OF_MEMORY";
  case HALError::OUT_OF_BOUNDS:
    return "OUT_OF_BOUNDS";
  case HALError::NOT_EMPTY:
    return "NOT_EMPTY";
  case HALError::INVALID_ARGUMENT:
    return "INVALID_ARGUMENT";
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
constexpr inline std::array<::com::rdk::hal::HALError, 9> enum_values<::com::rdk::hal::HALError> = {
  ::com::rdk::hal::HALError::SUCCESS,
  ::com::rdk::hal::HALError::BUFFER_FULL,
  ::com::rdk::hal::HALError::INVALID_RESOURCE,
  ::com::rdk::hal::HALError::INVALID_CODEC,
  ::com::rdk::hal::HALError::DEFERRED,
  ::com::rdk::hal::HALError::OUT_OF_MEMORY,
  ::com::rdk::hal::HALError::OUT_OF_BOUNDS,
  ::com::rdk::hal::HALError::NOT_EMPTY,
  ::com::rdk::hal::HALError::INVALID_ARGUMENT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
