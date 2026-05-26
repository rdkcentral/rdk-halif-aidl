#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
enum class PortProperty : int32_t {
  SIGNAL_STRENGTH = 0,
  SIGNAL_QUALITY = 1,
  METRIC_SIGNAL_LOCK_TIME = 1000,
  METRIC_SIGNAL_DROPS = 1001,
  METRIC_UPTIME = 1002,
  METRIC_SIGNAL_LOCK_COUNT = 1003,
  METRIC_LAST_SIGNAL_LOCK_TIME = 1004,
  METRIC_LAST_RESET_TIMESTAMP = 1005,
};
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
[[nodiscard]] static inline std::string toString(PortProperty val) {
  switch(val) {
  case PortProperty::SIGNAL_STRENGTH:
    return "SIGNAL_STRENGTH";
  case PortProperty::SIGNAL_QUALITY:
    return "SIGNAL_QUALITY";
  case PortProperty::METRIC_SIGNAL_LOCK_TIME:
    return "METRIC_SIGNAL_LOCK_TIME";
  case PortProperty::METRIC_SIGNAL_DROPS:
    return "METRIC_SIGNAL_DROPS";
  case PortProperty::METRIC_UPTIME:
    return "METRIC_UPTIME";
  case PortProperty::METRIC_SIGNAL_LOCK_COUNT:
    return "METRIC_SIGNAL_LOCK_COUNT";
  case PortProperty::METRIC_LAST_SIGNAL_LOCK_TIME:
    return "METRIC_LAST_SIGNAL_LOCK_TIME";
  case PortProperty::METRIC_LAST_RESET_TIMESTAMP:
    return "METRIC_LAST_RESET_TIMESTAMP";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::compositeinput::PortProperty, 8> enum_values<::com::rdk::hal::compositeinput::PortProperty> = {
  ::com::rdk::hal::compositeinput::PortProperty::SIGNAL_STRENGTH,
  ::com::rdk::hal::compositeinput::PortProperty::SIGNAL_QUALITY,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_SIGNAL_LOCK_TIME,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_SIGNAL_DROPS,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_UPTIME,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_SIGNAL_LOCK_COUNT,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_LAST_SIGNAL_LOCK_TIME,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_LAST_RESET_TIMESTAMP,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
