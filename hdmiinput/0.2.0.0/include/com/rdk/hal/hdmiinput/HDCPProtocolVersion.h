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
 *  @brief     HDCP version enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
enum class HDCPProtocolVersion : int32_t {
  // @aidl-doc
  /** HDCP protocol is not supported or unknown. */
  UNDEFINED = 0,
  // @aidl-doc
  /** HDCP protocol version 1.x */
  VERSION_1_X = 1,
  // @aidl-doc
  /** HDCP protocol version 2.x */
  VERSION_2_X = 2,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(HDCPProtocolVersion val) {
  switch(val) {
  case HDCPProtocolVersion::UNDEFINED:
    return "UNDEFINED";
  case HDCPProtocolVersion::VERSION_1_X:
    return "VERSION_1_X";
  case HDCPProtocolVersion::VERSION_2_X:
    return "VERSION_2_X";
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
constexpr inline std::array<::com::rdk::hal::hdmiinput::HDCPProtocolVersion, 3> enum_values<::com::rdk::hal::hdmiinput::HDCPProtocolVersion> = {
  ::com::rdk::hal::hdmiinput::HDCPProtocolVersion::UNDEFINED,
  ::com::rdk::hal::hdmiinput::HDCPProtocolVersion::VERSION_1_X,
  ::com::rdk::hal::hdmiinput::HDCPProtocolVersion::VERSION_2_X,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
