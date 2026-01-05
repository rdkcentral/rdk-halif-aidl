#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
enum class Property : int32_t {
  HAL_CEC_VERSION = 0,
  METRIC_DIRECTED_MESSAGES_SENT = 1000,
  METRIC_BROADCAST_MESSAGES_SENT = 1001,
  METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED = 1002,
  METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED = 1003,
  METRIC_ARBITRATION_FAILURES = 1004,
};
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::HAL_CEC_VERSION:
    return "HAL_CEC_VERSION";
  case Property::METRIC_DIRECTED_MESSAGES_SENT:
    return "METRIC_DIRECTED_MESSAGES_SENT";
  case Property::METRIC_BROADCAST_MESSAGES_SENT:
    return "METRIC_BROADCAST_MESSAGES_SENT";
  case Property::METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED:
    return "METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED";
  case Property::METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED:
    return "METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED";
  case Property::METRIC_ARBITRATION_FAILURES:
    return "METRIC_ARBITRATION_FAILURES";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmicec::Property, 6> enum_values<::com::rdk::hal::hdmicec::Property> = {
  ::com::rdk::hal::hdmicec::Property::HAL_CEC_VERSION,
  ::com::rdk::hal::hdmicec::Property::METRIC_DIRECTED_MESSAGES_SENT,
  ::com::rdk::hal::hdmicec::Property::METRIC_BROADCAST_MESSAGES_SENT,
  ::com::rdk::hal::hdmicec::Property::METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED,
  ::com::rdk::hal::hdmicec::Property::METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED,
  ::com::rdk::hal::hdmicec::Property::METRIC_ARBITRATION_FAILURES,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
