#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
enum class FilterType : int32_t {
  UNDEFINED = 0,
  MPEG2TS_DATA = 1,
  MPEG2TS_CLOCK = 2,
  MPEG2TS_VIDEO = 3,
  MPEG2TS_AUDIO = 4,
  MPEG2TS_SUPPLEMENTARY_AUDIO = 5,
};
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
[[nodiscard]] static inline std::string toString(FilterType val) {
  switch(val) {
  case FilterType::UNDEFINED:
    return "UNDEFINED";
  case FilterType::MPEG2TS_DATA:
    return "MPEG2TS_DATA";
  case FilterType::MPEG2TS_CLOCK:
    return "MPEG2TS_CLOCK";
  case FilterType::MPEG2TS_VIDEO:
    return "MPEG2TS_VIDEO";
  case FilterType::MPEG2TS_AUDIO:
    return "MPEG2TS_AUDIO";
  case FilterType::MPEG2TS_SUPPLEMENTARY_AUDIO:
    return "MPEG2TS_SUPPLEMENTARY_AUDIO";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::demux::FilterType, 6> enum_values<::com::rdk::hal::broadcast::demux::FilterType> = {
  ::com::rdk::hal::broadcast::demux::FilterType::UNDEFINED,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_DATA,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_CLOCK,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_VIDEO,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_AUDIO,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_SUPPLEMENTARY_AUDIO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
