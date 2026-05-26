#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
enum class SendMessageStatus : int32_t {
  ACK_STATE_0 = 0,
  ACK_STATE_1 = 1,
  BUSY = 2,
};
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
[[nodiscard]] static inline std::string toString(SendMessageStatus val) {
  switch(val) {
  case SendMessageStatus::ACK_STATE_0:
    return "ACK_STATE_0";
  case SendMessageStatus::ACK_STATE_1:
    return "ACK_STATE_1";
  case SendMessageStatus::BUSY:
    return "BUSY";
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
constexpr inline std::array<::com::rdk::hal::hdmicec::SendMessageStatus, 3> enum_values<::com::rdk::hal::hdmicec::SendMessageStatus> = {
  ::com::rdk::hal::hdmicec::SendMessageStatus::ACK_STATE_0,
  ::com::rdk::hal::hdmicec::SendMessageStatus::ACK_STATE_1,
  ::com::rdk::hal::hdmicec::SendMessageStatus::BUSY,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
