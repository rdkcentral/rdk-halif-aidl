#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/** @brief Error codes returned by panel control operations. */
enum class ErrorCode : int32_t {
  // @aidl-doc
  /** The request was applied. */
  SUCCESS = 0,
  // @aidl-doc
  /** One or more arguments were invalid. */
  INVALID_ARGUMENT = 1,
  // @aidl-doc
  /** The request is not valid in the current state. */
  INVALID_STATE = 2,
  // @aidl-doc
  /** The request is not supported by the platform. */
  NOT_SUPPORTED = 3,
  // @aidl-doc
  /** The HAL could not apply the request. */
  HARDWARE_FAILURE = 4,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(ErrorCode val) {
  switch(val) {
  case ErrorCode::SUCCESS:
    return "SUCCESS";
  case ErrorCode::INVALID_ARGUMENT:
    return "INVALID_ARGUMENT";
  case ErrorCode::INVALID_STATE:
    return "INVALID_STATE";
  case ErrorCode::NOT_SUPPORTED:
    return "NOT_SUPPORTED";
  case ErrorCode::HARDWARE_FAILURE:
    return "HARDWARE_FAILURE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::ErrorCode, 5> enum_values<::com::rdk::hal::panel::ErrorCode> = {
  ::com::rdk::hal::panel::ErrorCode::SUCCESS,
  ::com::rdk::hal::panel::ErrorCode::INVALID_ARGUMENT,
  ::com::rdk::hal::panel::ErrorCode::INVALID_STATE,
  ::com::rdk::hal::panel::ErrorCode::NOT_SUPPORTED,
  ::com::rdk::hal::panel::ErrorCode::HARDWARE_FAILURE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
