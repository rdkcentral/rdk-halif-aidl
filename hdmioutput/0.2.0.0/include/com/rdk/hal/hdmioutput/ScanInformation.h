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
 *  @brief     HDMI AVI InfoFrame Scan Information enum.
 *
 *  Defines how the HDMI signal describes scan handling. This affects how the
 *  display should scale or crop content, particularly in SD/HD modes.
 *
 *  Mapped to the AVI InfoFrame `S[1:0]` field (Scan Information).
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class ScanInformation : int32_t {
  // @aidl-doc
  /**
   * No scan information is provided to the sink.
   * The receiver may infer default scan behaviour.
   * AVI InfoFrame S = 0
   */
  NO_DATA = 0,
  // @aidl-doc
  /**
   * Content is composed for an overscanned display.
   * The sink is expected to apply overscan, cropping part of the active image.
   * AVI InfoFrame S = 1
   */
  OVERSCAN = 1,
  // @aidl-doc
  /**
   * Content is composed for an underscanned display.
   * The sink is expected to show the full active image area without cropping.
   * AVI InfoFrame S = 2
   */
  UNDERSCAN = 2,
  // @aidl-doc
  /**
   * Reserved value per HDMI/CTA-861 spec.
   * Should not be used unless explicitly defined in future standards.
   * AVI InfoFrame S = 3
   */
  RESERVED = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(ScanInformation val) {
  switch(val) {
  case ScanInformation::NO_DATA:
    return "NO_DATA";
  case ScanInformation::OVERSCAN:
    return "OVERSCAN";
  case ScanInformation::UNDERSCAN:
    return "UNDERSCAN";
  case ScanInformation::RESERVED:
    return "RESERVED";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::ScanInformation, 4> enum_values<::com::rdk::hal::hdmioutput::ScanInformation> = {
  ::com::rdk::hal::hdmioutput::ScanInformation::NO_DATA,
  ::com::rdk::hal::hdmioutput::ScanInformation::OVERSCAN,
  ::com::rdk::hal::hdmioutput::ScanInformation::UNDERSCAN,
  ::com::rdk::hal::hdmioutput::ScanInformation::RESERVED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
