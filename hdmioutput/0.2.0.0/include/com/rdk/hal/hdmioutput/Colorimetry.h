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
 *  @brief     HDMI Colorimetry enum.
 *
 *  Represents the base colorimetry values encoded in the AVI InfoFrame field C.
 *  These values define the default colour matrix used by the HDMI sink device,
 *  unless overridden by extended colorimetry settings.
 *
 *  Reference: HDMI Specification – AVI InfoFrame (Colorimetry Field).
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class Colorimetry : int32_t {
  // @aidl-doc
  /** No colorimetry data – AVI InfoFrame C=0 */
  NO_DATA = 0,
  // @aidl-doc
  /** SMPTE 170M / ITU-R BT.601 – AVI InfoFrame C=1 */
  SMPTE_170M = 1,
  // @aidl-doc
  /** ITU-R BT.709 – AVI InfoFrame C=2 */
  ITU_R_BT709 = 2,
  // @aidl-doc
  /**
   * Extended colorimetry – AVI InfoFrame C=3.
   * Requires use of the EC (Extended Colorimetry) field.
   *
   * @see ExtendedColorimetry
   */
  EXTENDED_COLORIMETRY = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(Colorimetry val) {
  switch(val) {
  case Colorimetry::NO_DATA:
    return "NO_DATA";
  case Colorimetry::SMPTE_170M:
    return "SMPTE_170M";
  case Colorimetry::ITU_R_BT709:
    return "ITU_R_BT709";
  case Colorimetry::EXTENDED_COLORIMETRY:
    return "EXTENDED_COLORIMETRY";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::Colorimetry, 4> enum_values<::com::rdk::hal::hdmioutput::Colorimetry> = {
  ::com::rdk::hal::hdmioutput::Colorimetry::NO_DATA,
  ::com::rdk::hal::hdmioutput::Colorimetry::SMPTE_170M,
  ::com::rdk::hal::hdmioutput::Colorimetry::ITU_R_BT709,
  ::com::rdk::hal::hdmioutput::Colorimetry::EXTENDED_COLORIMETRY,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
