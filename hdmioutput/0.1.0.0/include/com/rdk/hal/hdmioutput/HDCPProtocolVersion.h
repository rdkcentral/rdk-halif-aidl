#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class HDCPProtocolVersion : int32_t {
  UNDEFINED = 0,
  VERSION_1_X = 1,
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
