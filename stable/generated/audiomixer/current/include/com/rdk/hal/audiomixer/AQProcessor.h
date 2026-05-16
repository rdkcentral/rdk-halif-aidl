#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class AQProcessor : int32_t {
  UNDEFINED = 0,
  DOLBY_MS12 = 1,
  DTS_ULTRA = 2,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(AQProcessor val) {
  switch(val) {
  case AQProcessor::UNDEFINED:
    return "UNDEFINED";
  case AQProcessor::DOLBY_MS12:
    return "DOLBY_MS12";
  case AQProcessor::DTS_ULTRA:
    return "DTS_ULTRA";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::AQProcessor, 3> enum_values<::com::rdk::hal::audiomixer::AQProcessor> = {
  ::com::rdk::hal::audiomixer::AQProcessor::UNDEFINED,
  ::com::rdk::hal::audiomixer::AQProcessor::DOLBY_MS12,
  ::com::rdk::hal::audiomixer::AQProcessor::DTS_ULTRA,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
