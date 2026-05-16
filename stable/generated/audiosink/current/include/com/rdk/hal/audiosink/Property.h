#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
enum class Property : int32_t {
  RESOURCE_ID = 0,
  REFERENCE_LEVEL = 1,
  RENDER_LATENCY_NS = 2,
  QUEUE_DEPTH_NS = 3,
  MIXER_ID = 4,
  AV_SOURCE = 5,
  DOLBY_ATMOS_LOCK = 6,
  METRIC_xxxx = 1000,
};
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::REFERENCE_LEVEL:
    return "REFERENCE_LEVEL";
  case Property::RENDER_LATENCY_NS:
    return "RENDER_LATENCY_NS";
  case Property::QUEUE_DEPTH_NS:
    return "QUEUE_DEPTH_NS";
  case Property::MIXER_ID:
    return "MIXER_ID";
  case Property::AV_SOURCE:
    return "AV_SOURCE";
  case Property::DOLBY_ATMOS_LOCK:
    return "DOLBY_ATMOS_LOCK";
  case Property::METRIC_xxxx:
    return "METRIC_xxxx";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiosink::Property, 8> enum_values<::com::rdk::hal::audiosink::Property> = {
  ::com::rdk::hal::audiosink::Property::RESOURCE_ID,
  ::com::rdk::hal::audiosink::Property::REFERENCE_LEVEL,
  ::com::rdk::hal::audiosink::Property::RENDER_LATENCY_NS,
  ::com::rdk::hal::audiosink::Property::QUEUE_DEPTH_NS,
  ::com::rdk::hal::audiosink::Property::MIXER_ID,
  ::com::rdk::hal::audiosink::Property::AV_SOURCE,
  ::com::rdk::hal::audiosink::Property::DOLBY_ATMOS_LOCK,
  ::com::rdk::hal::audiosink::Property::METRIC_xxxx,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
