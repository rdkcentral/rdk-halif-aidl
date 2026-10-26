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
 *  @brief     HDMI extended colorimetry enum.
 *
 *  Defines the extended colorimetry values used in the HDMI AVI InfoFrame when
 *  Colorimetry (C) is set to 3. These settings refine how the HDMI sink interprets
 *  colour space beyond standard ITU-R BT.709 or SMPTE 170M.
 *
 *  Reference: HDMI Specification – AVI InfoFrame EC (Extended Colorimetry) Field.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class ExtendedColorimetry : int32_t {
  // @aidl-doc
  /** xvYCC601 – AVI InfoFrame C=3, EC=0 */
  XV_YCC_601 = 0,
  // @aidl-doc
  /** xvYCC709 – AVI InfoFrame C=3, EC=1 */
  XV_YCC_709 = 1,
  // @aidl-doc
  /** sYCC601 – AVI InfoFrame C=3, EC=2 */
  S_YCC_601 = 2,
  // @aidl-doc
  /** opYCC601 – AVI InfoFrame C=3, EC=3 */
  OP_YCC_601 = 3,
  // @aidl-doc
  /** opRGB – AVI InfoFrame C=3, EC=4 */
  OP_RGB = 4,
  // @aidl-doc
  /** ITU-R BT.2020 YCC (constant luminance) – AVI InfoFrame C=3, EC=5 */
  BT2020_C_YCC = 5,
  // @aidl-doc
  /**
   * ITU-R BT.2020 RGB or YCC – AVI InfoFrame C=3, EC=6
   *
   * RGB interpretation when Y=0,
   * YCC interpretation when Y=1, 2, or 3.
   */
  BT2020_RGB_YCC = 6,
  // @aidl-doc
  /**
   * Additional Colorimetry Extension – AVI InfoFrame C=3, EC=7
   *
   * @see AdditionalColorimetryExtension for ACE field values.
   */
  ADDITIONAL_COLORIMETRY_EXTENSION = 7,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(ExtendedColorimetry val) {
  switch(val) {
  case ExtendedColorimetry::XV_YCC_601:
    return "XV_YCC_601";
  case ExtendedColorimetry::XV_YCC_709:
    return "XV_YCC_709";
  case ExtendedColorimetry::S_YCC_601:
    return "S_YCC_601";
  case ExtendedColorimetry::OP_YCC_601:
    return "OP_YCC_601";
  case ExtendedColorimetry::OP_RGB:
    return "OP_RGB";
  case ExtendedColorimetry::BT2020_C_YCC:
    return "BT2020_C_YCC";
  case ExtendedColorimetry::BT2020_RGB_YCC:
    return "BT2020_RGB_YCC";
  case ExtendedColorimetry::ADDITIONAL_COLORIMETRY_EXTENSION:
    return "ADDITIONAL_COLORIMETRY_EXTENSION";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::ExtendedColorimetry, 8> enum_values<::com::rdk::hal::hdmioutput::ExtendedColorimetry> = {
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::XV_YCC_601,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::XV_YCC_709,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::S_YCC_601,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::OP_YCC_601,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::OP_RGB,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::BT2020_C_YCC,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::BT2020_RGB_YCC,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::ADDITIONAL_COLORIMETRY_EXTENSION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
