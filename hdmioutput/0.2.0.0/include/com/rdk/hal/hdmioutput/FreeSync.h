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
 *  @brief     HDMI AMD FreeSync enum.
 *
 *  Describes the level of AMD FreeSync support provided by the HDMI output.
 *  This is used in conjunction with `Capabilities.supportsFreeSync` to specify
 *  the actual feature tier supported.
 *
 *  Reference: AMD FreeSync specification.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class FreeSync : int32_t {
  // @aidl-doc
  /** No FreeSync support. */
  UNSUPPORTED = 0,
  // @aidl-doc
  /** AMD FreeSync basic tier. */
  FREESYNC = 1,
  // @aidl-doc
  /** AMD FreeSync Premium tier. */
  FREESYNC_PREMIUM = 2,
  // @aidl-doc
  /** AMD FreeSync Premium Pro tier. */
  FREESYNC_PREMIUM_PRO = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(FreeSync val) {
  switch(val) {
  case FreeSync::UNSUPPORTED:
    return "UNSUPPORTED";
  case FreeSync::FREESYNC:
    return "FREESYNC";
  case FreeSync::FREESYNC_PREMIUM:
    return "FREESYNC_PREMIUM";
  case FreeSync::FREESYNC_PREMIUM_PRO:
    return "FREESYNC_PREMIUM_PRO";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::FreeSync, 4> enum_values<::com::rdk::hal::hdmioutput::FreeSync> = {
  ::com::rdk::hal::hdmioutput::FreeSync::UNSUPPORTED,
  ::com::rdk::hal::hdmioutput::FreeSync::FREESYNC,
  ::com::rdk::hal::hdmioutput::FreeSync::FREESYNC_PREMIUM,
  ::com::rdk::hal::hdmioutput::FreeSync::FREESYNC_PREMIUM_PRO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
