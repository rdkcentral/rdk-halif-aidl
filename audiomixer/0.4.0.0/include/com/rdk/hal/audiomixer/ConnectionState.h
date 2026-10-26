#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief   HAL component connection states.
 *          Used in output port properties to describe physical or logical connection status.
 */
enum class ConnectionState : int32_t {
  // @aidl-doc
  /** Connection state cannot be determined (e.g., not supported by hardware) */
  UNKNOWN = 0,
  // @aidl-doc
  /** Explicitly disconnected */
  DISCONNECTED = 1,
  // @aidl-doc
  /** Explicitly connected */
  CONNECTED = 2,
  // @aidl-doc
  /** Pending connection (e.g., handshake in progress, BT pairing, etc.) */
  PENDING = 3,
  // @aidl-doc
  /** Error/fault state (e.g., shorted, unsupported device, HDCP failure) */
  FAULT = 4,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(ConnectionState val) {
  switch(val) {
  case ConnectionState::UNKNOWN:
    return "UNKNOWN";
  case ConnectionState::DISCONNECTED:
    return "DISCONNECTED";
  case ConnectionState::CONNECTED:
    return "CONNECTED";
  case ConnectionState::PENDING:
    return "PENDING";
  case ConnectionState::FAULT:
    return "FAULT";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::ConnectionState, 5> enum_values<::com::rdk::hal::audiomixer::ConnectionState> = {
  ::com::rdk::hal::audiomixer::ConnectionState::UNKNOWN,
  ::com::rdk::hal::audiomixer::ConnectionState::DISCONNECTED,
  ::com::rdk::hal::audiomixer::ConnectionState::CONNECTED,
  ::com::rdk::hal::audiomixer::ConnectionState::PENDING,
  ::com::rdk::hal::audiomixer::ConnectionState::FAULT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
