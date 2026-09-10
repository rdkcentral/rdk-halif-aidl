#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class OutputPortType : int32_t {
  UNKNOWN = 0,
  HDMI = 1,
  SPDIF = 2,
  OPTICAL = 3,
  SPEAKERS = 4,
  BLUETOOTH = 5,
  ARC = 6,
  EARC = 7,
  COMPOSITE = 8,
  INTERNAL = 1000,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(OutputPortType val) {
  switch(val) {
  case OutputPortType::UNKNOWN:
    return "UNKNOWN";
  case OutputPortType::HDMI:
    return "HDMI";
  case OutputPortType::SPDIF:
    return "SPDIF";
  case OutputPortType::OPTICAL:
    return "OPTICAL";
  case OutputPortType::SPEAKERS:
    return "SPEAKERS";
  case OutputPortType::BLUETOOTH:
    return "BLUETOOTH";
  case OutputPortType::ARC:
    return "ARC";
  case OutputPortType::EARC:
    return "EARC";
  case OutputPortType::COMPOSITE:
    return "COMPOSITE";
  case OutputPortType::INTERNAL:
    return "INTERNAL";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::OutputPortType, 10> enum_values<::com::rdk::hal::audiomixer::OutputPortType> = {
  ::com::rdk::hal::audiomixer::OutputPortType::UNKNOWN,
  ::com::rdk::hal::audiomixer::OutputPortType::HDMI,
  ::com::rdk::hal::audiomixer::OutputPortType::SPDIF,
  ::com::rdk::hal::audiomixer::OutputPortType::OPTICAL,
  ::com::rdk::hal::audiomixer::OutputPortType::SPEAKERS,
  ::com::rdk::hal::audiomixer::OutputPortType::BLUETOOTH,
  ::com::rdk::hal::audiomixer::OutputPortType::ARC,
  ::com::rdk::hal::audiomixer::OutputPortType::EARC,
  ::com::rdk::hal::audiomixer::OutputPortType::COMPOSITE,
  ::com::rdk::hal::audiomixer::OutputPortType::INTERNAL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
