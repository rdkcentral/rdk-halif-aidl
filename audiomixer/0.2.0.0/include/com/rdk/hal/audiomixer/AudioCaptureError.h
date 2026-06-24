#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class AudioCaptureError : int32_t {
  ERROR_OVERFLOW = 0,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(AudioCaptureError val) {
  switch(val) {
  case AudioCaptureError::ERROR_OVERFLOW:
    return "ERROR_OVERFLOW";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::AudioCaptureError, 1> enum_values<::com::rdk::hal::audiomixer::AudioCaptureError> = {
  ::com::rdk::hal::audiomixer::AudioCaptureError::ERROR_OVERFLOW,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
