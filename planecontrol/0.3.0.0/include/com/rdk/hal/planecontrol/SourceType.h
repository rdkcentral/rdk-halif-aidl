#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
// @aidl-doc
/**
 *  @brief     Video plane sources definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class SourceType : int32_t {
  // @aidl-doc
  /** No video source is set for the video plane. Default value for all planes. */
  NONE = 0,
  // @aidl-doc
  /** A video sink is set as the source for the video plane. */
  VIDEO_SINK = 1,
  // @aidl-doc
  /** A HDMI input is set as the source for the video plane. */
  HDMI = 2,
  // @aidl-doc
  /** A composite input is set as the source for the video plane. */
  COMPOSITE = 3,
};
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
[[nodiscard]] static inline std::string toString(SourceType val) {
  switch(val) {
  case SourceType::NONE:
    return "NONE";
  case SourceType::VIDEO_SINK:
    return "VIDEO_SINK";
  case SourceType::HDMI:
    return "HDMI";
  case SourceType::COMPOSITE:
    return "COMPOSITE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::planecontrol::SourceType, 4> enum_values<::com::rdk::hal::planecontrol::SourceType> = {
  ::com::rdk::hal::planecontrol::SourceType::NONE,
  ::com::rdk::hal::planecontrol::SourceType::VIDEO_SINK,
  ::com::rdk::hal::planecontrol::SourceType::HDMI,
  ::com::rdk::hal::planecontrol::SourceType::COMPOSITE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
