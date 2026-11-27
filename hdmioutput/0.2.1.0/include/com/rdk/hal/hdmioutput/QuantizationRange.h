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
 *  @brief     HDMI quantization range.
 *
 *  The range of code values the output uses. Maps to the AVI InfoFrame Q
 *  field for RGB and YQ field for YCbCr.
 *
 *  @author    Gerald Weatherup
 */
enum class QuantizationRange : int32_t {
  // @aidl-doc
  /** Limited range (e.g. 16-235 at 8 bits). AVI InfoFrame Q=1 or YQ=0. */
  LIMITED = 0,
  // @aidl-doc
  /** Full range (e.g. 0-255 at 8 bits). AVI InfoFrame Q=2 or YQ=1. */
  FULL = 1,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(QuantizationRange val) {
  switch(val) {
  case QuantizationRange::LIMITED:
    return "LIMITED";
  case QuantizationRange::FULL:
    return "FULL";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::QuantizationRange, 2> enum_values<::com::rdk::hal::hdmioutput::QuantizationRange> = {
  ::com::rdk::hal::hdmioutput::QuantizationRange::LIMITED,
  ::com::rdk::hal::hdmioutput::QuantizationRange::FULL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
