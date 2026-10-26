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
 *  @brief     HDMI AFD (Active Format Description) enum.
 *
 *  Represents the AFD values as specified in the HDMI AVI InfoFrame.
 *  These values indicate how the video content should be displayed
 *  with respect to aspect ratio and centring.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class AFD : int32_t {
  // @aidl-doc
  /** Unspecified AFD - AVI InfoFrame A0=0 */
  UNSPECIFIED = -1,
  // @aidl-doc
  /** Same as picture - AVI InfoFrame A0=1, R=1000b */
  SAME_AS_PICTURE = 8,
  // @aidl-doc
  /** Center 4:3 - AVI InfoFrame A0=1, R=1001b */
  CENTER_4_3 = 9,
  // @aidl-doc
  /** Center 16:9 - AVI InfoFrame A0=1, R=1010b */
  CENTER_16_9 = 10,
  // @aidl-doc
  /** Center 14:9 - AVI InfoFrame A0=1, R=1011b */
  CENTER_14_9 = 11,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(AFD val) {
  switch(val) {
  case AFD::UNSPECIFIED:
    return "UNSPECIFIED";
  case AFD::SAME_AS_PICTURE:
    return "SAME_AS_PICTURE";
  case AFD::CENTER_4_3:
    return "CENTER_4_3";
  case AFD::CENTER_16_9:
    return "CENTER_16_9";
  case AFD::CENTER_14_9:
    return "CENTER_14_9";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::AFD, 5> enum_values<::com::rdk::hal::hdmioutput::AFD> = {
  ::com::rdk::hal::hdmioutput::AFD::UNSPECIFIED,
  ::com::rdk::hal::hdmioutput::AFD::SAME_AS_PICTURE,
  ::com::rdk::hal::hdmioutput::AFD::CENTER_4_3,
  ::com::rdk::hal::hdmioutput::AFD::CENTER_16_9,
  ::com::rdk::hal::hdmioutput::AFD::CENTER_14_9,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
