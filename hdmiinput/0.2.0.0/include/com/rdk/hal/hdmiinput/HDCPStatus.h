#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     HDCP status type enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class HDCPStatus : int32_t {
  // @aidl-doc
  /**
   * Not connected, not powered.
   *
   * Indicates the state is not yet determined or the operation is not applicable. Clients should poll or retry later.
   */
  UNKNOWN = -1,
  // @aidl-doc
  /** The connection is unauthenticated. */
  UNAUTHENTICATED = 0,
  // @aidl-doc
  /** HDCP authentication is in progress. */
  AUTHENTICATION_IN_PROGRESS = 1,
  // @aidl-doc
  /** HDCP authentication failed. */
  AUTHENTICATION_FAILURE = 2,
  // @aidl-doc
  /** HDCP is successfully authenticated. */
  AUTHENTICATED = 3,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(HDCPStatus val) {
  switch(val) {
  case HDCPStatus::UNKNOWN:
    return "UNKNOWN";
  case HDCPStatus::UNAUTHENTICATED:
    return "UNAUTHENTICATED";
  case HDCPStatus::AUTHENTICATION_IN_PROGRESS:
    return "AUTHENTICATION_IN_PROGRESS";
  case HDCPStatus::AUTHENTICATION_FAILURE:
    return "AUTHENTICATION_FAILURE";
  case HDCPStatus::AUTHENTICATED:
    return "AUTHENTICATED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmiinput::HDCPStatus, 5> enum_values<::com::rdk::hal::hdmiinput::HDCPStatus> = {
  ::com::rdk::hal::hdmiinput::HDCPStatus::UNKNOWN,
  ::com::rdk::hal::hdmiinput::HDCPStatus::UNAUTHENTICATED,
  ::com::rdk::hal::hdmiinput::HDCPStatus::AUTHENTICATION_IN_PROGRESS,
  ::com::rdk::hal::hdmiinput::HDCPStatus::AUTHENTICATION_FAILURE,
  ::com::rdk::hal::hdmiinput::HDCPStatus::AUTHENTICATED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
