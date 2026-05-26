#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
enum class Property : int32_t {
  RESOURCE_ID = 0,
  SINK_QUEUE_DEPTH = 1,
  AV_SOURCE = 2,
  RENDER_FIRST_FRAME = 3,
  METRIC_FRAMES_RECEIVED = 1000,
  METRIC_FRAMES_PRESENTED = 1001,
  METRIC_FRAMES_DROPPED_LATE = 1002,
  METRIC_FRAMES_DROPPED_FRC = 1003,
  METRIC_FRAMES_REPEATED_FRC = 1004,
  METRIC_FRAMES_REPEATED_MISSING_FRAME = 1005,
  METRIC_UNDERFLOWED = 1006,
};
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videosink {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::SINK_QUEUE_DEPTH:
    return "SINK_QUEUE_DEPTH";
  case Property::AV_SOURCE:
    return "AV_SOURCE";
  case Property::RENDER_FIRST_FRAME:
    return "RENDER_FIRST_FRAME";
  case Property::METRIC_FRAMES_RECEIVED:
    return "METRIC_FRAMES_RECEIVED";
  case Property::METRIC_FRAMES_PRESENTED:
    return "METRIC_FRAMES_PRESENTED";
  case Property::METRIC_FRAMES_DROPPED_LATE:
    return "METRIC_FRAMES_DROPPED_LATE";
  case Property::METRIC_FRAMES_DROPPED_FRC:
    return "METRIC_FRAMES_DROPPED_FRC";
  case Property::METRIC_FRAMES_REPEATED_FRC:
    return "METRIC_FRAMES_REPEATED_FRC";
  case Property::METRIC_FRAMES_REPEATED_MISSING_FRAME:
    return "METRIC_FRAMES_REPEATED_MISSING_FRAME";
  case Property::METRIC_UNDERFLOWED:
    return "METRIC_UNDERFLOWED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videosink::Property, 11> enum_values<::com::rdk::hal::videosink::Property> = {
  ::com::rdk::hal::videosink::Property::RESOURCE_ID,
  ::com::rdk::hal::videosink::Property::SINK_QUEUE_DEPTH,
  ::com::rdk::hal::videosink::Property::AV_SOURCE,
  ::com::rdk::hal::videosink::Property::RENDER_FIRST_FRAME,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_RECEIVED,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_PRESENTED,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_DROPPED_LATE,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_DROPPED_FRC,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_REPEATED_FRC,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_REPEATED_MISSING_FRAME,
  ::com::rdk::hal::videosink::Property::METRIC_UNDERFLOWED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
