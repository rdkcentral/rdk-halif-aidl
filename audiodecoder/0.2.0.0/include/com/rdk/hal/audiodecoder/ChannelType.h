#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
enum class ChannelType : int32_t {
  MONO = 0,
  FRONT_LEFT = 1,
  FRONT_RIGHT = 2,
  FRONT_CENTER = 3,
  LFE = 4,
  SIDE_LEFT = 5,
  SIDE_RIGHT = 6,
  UP_LEFT = 7,
  UP_RIGHT = 8,
  BACK_LEFT = 9,
  BACK_RIGHT = 10,
  BACK_CENTER = 11,
};
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(ChannelType val) {
  switch(val) {
  case ChannelType::MONO:
    return "MONO";
  case ChannelType::FRONT_LEFT:
    return "FRONT_LEFT";
  case ChannelType::FRONT_RIGHT:
    return "FRONT_RIGHT";
  case ChannelType::FRONT_CENTER:
    return "FRONT_CENTER";
  case ChannelType::LFE:
    return "LFE";
  case ChannelType::SIDE_LEFT:
    return "SIDE_LEFT";
  case ChannelType::SIDE_RIGHT:
    return "SIDE_RIGHT";
  case ChannelType::UP_LEFT:
    return "UP_LEFT";
  case ChannelType::UP_RIGHT:
    return "UP_RIGHT";
  case ChannelType::BACK_LEFT:
    return "BACK_LEFT";
  case ChannelType::BACK_RIGHT:
    return "BACK_RIGHT";
  case ChannelType::BACK_CENTER:
    return "BACK_CENTER";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiodecoder::ChannelType, 12> enum_values<::com::rdk::hal::audiodecoder::ChannelType> = {
  ::com::rdk::hal::audiodecoder::ChannelType::MONO,
  ::com::rdk::hal::audiodecoder::ChannelType::FRONT_LEFT,
  ::com::rdk::hal::audiodecoder::ChannelType::FRONT_RIGHT,
  ::com::rdk::hal::audiodecoder::ChannelType::FRONT_CENTER,
  ::com::rdk::hal::audiodecoder::ChannelType::LFE,
  ::com::rdk::hal::audiodecoder::ChannelType::SIDE_LEFT,
  ::com::rdk::hal::audiodecoder::ChannelType::SIDE_RIGHT,
  ::com::rdk::hal::audiodecoder::ChannelType::UP_LEFT,
  ::com::rdk::hal::audiodecoder::ChannelType::UP_RIGHT,
  ::com::rdk::hal::audiodecoder::ChannelType::BACK_LEFT,
  ::com::rdk::hal::audiodecoder::ChannelType::BACK_RIGHT,
  ::com::rdk::hal::audiodecoder::ChannelType::BACK_CENTER,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
