#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
enum class Property : int32_t {
  RESOURCE_ID = 0,
  METRIC_AV_SYNC_ACCURACY_MS = 1000,
  METRIC_AV_RESYNC_COUNT = 1001,
};
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace avclock {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::METRIC_AV_SYNC_ACCURACY_MS:
    return "METRIC_AV_SYNC_ACCURACY_MS";
  case Property::METRIC_AV_RESYNC_COUNT:
    return "METRIC_AV_RESYNC_COUNT";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::avclock::Property, 3> enum_values<::com::rdk::hal::avclock::Property> = {
  ::com::rdk::hal::avclock::Property::RESOURCE_ID,
  ::com::rdk::hal::avclock::Property::METRIC_AV_SYNC_ACCURACY_MS,
  ::com::rdk::hal::avclock::Property::METRIC_AV_RESYNC_COUNT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
