#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
// @aidl-doc
/**
 * @brief     AV source type definitions.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 */
enum class AVSource : int32_t {
  // @aidl-doc
  /** Source is automatically determined by the system. */
  AUTO = -1,
  // @aidl-doc
  /** Source is unknown and should be treated as IP. */
  UNKNOWN = 0,
  // @aidl-doc
  /** Source is streamed over IP. */
  IP = 1,
  // @aidl-doc
  /** Source is from a broadcast tuner. */
  TUNER = 2,
  // @aidl-doc
  /**
   * Source is from a system application.
   * This indicates a PCM system sound clip.
   */
  SYSTEM = 3,
  // @aidl-doc
  /** Source is from a HDMI input port. */
  HDMI_1 = 101,
  HDMI_2 = 102,
  HDMI_3 = 103,
  HDMI_4 = 104,
  HDMI_5 = 105,
  // @aidl-doc
  /** Source is from a composite input port. */
  COMPOSITE_1 = 201,
  COMPOSITE_2 = 202,
  COMPOSITE_3 = 203,
  COMPOSITE_4 = 204,
  COMPOSITE_5 = 205,
};
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
[[nodiscard]] static inline std::string toString(AVSource val) {
  switch(val) {
  case AVSource::AUTO:
    return "AUTO";
  case AVSource::UNKNOWN:
    return "UNKNOWN";
  case AVSource::IP:
    return "IP";
  case AVSource::TUNER:
    return "TUNER";
  case AVSource::SYSTEM:
    return "SYSTEM";
  case AVSource::HDMI_1:
    return "HDMI_1";
  case AVSource::HDMI_2:
    return "HDMI_2";
  case AVSource::HDMI_3:
    return "HDMI_3";
  case AVSource::HDMI_4:
    return "HDMI_4";
  case AVSource::HDMI_5:
    return "HDMI_5";
  case AVSource::COMPOSITE_1:
    return "COMPOSITE_1";
  case AVSource::COMPOSITE_2:
    return "COMPOSITE_2";
  case AVSource::COMPOSITE_3:
    return "COMPOSITE_3";
  case AVSource::COMPOSITE_4:
    return "COMPOSITE_4";
  case AVSource::COMPOSITE_5:
    return "COMPOSITE_5";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::AVSource, 15> enum_values<::com::rdk::hal::AVSource> = {
  ::com::rdk::hal::AVSource::AUTO,
  ::com::rdk::hal::AVSource::UNKNOWN,
  ::com::rdk::hal::AVSource::IP,
  ::com::rdk::hal::AVSource::TUNER,
  ::com::rdk::hal::AVSource::SYSTEM,
  ::com::rdk::hal::AVSource::HDMI_1,
  ::com::rdk::hal::AVSource::HDMI_2,
  ::com::rdk::hal::AVSource::HDMI_3,
  ::com::rdk::hal::AVSource::HDMI_4,
  ::com::rdk::hal::AVSource::HDMI_5,
  ::com::rdk::hal::AVSource::COMPOSITE_1,
  ::com::rdk::hal::AVSource::COMPOSITE_2,
  ::com::rdk::hal::AVSource::COMPOSITE_3,
  ::com::rdk::hal::AVSource::COMPOSITE_4,
  ::com::rdk::hal::AVSource::COMPOSITE_5,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
