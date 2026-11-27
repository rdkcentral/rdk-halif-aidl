#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDCP protocol version enum.
 *
 *  Identifies the supported version of HDCP (High-bandwidth Digital Content Protection)
 *  that may be used over the HDMI output port.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
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
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
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
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::HDCPProtocolVersion, 3> enum_values<::com::rdk::hal::hdmioutput::HDCPProtocolVersion> = {
  ::com::rdk::hal::hdmioutput::HDCPProtocolVersion::UNDEFINED,
  ::com::rdk::hal::hdmioutput::HDCPProtocolVersion::VERSION_1_X,
  ::com::rdk::hal::hdmioutput::HDCPProtocolVersion::VERSION_2_X,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
