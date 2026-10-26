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
 *  @brief     Plane aspect ratio definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class AspectRatio : int32_t {
  // @aidl-doc
  /**
   * The full video frame is displayed centered in the plane maintaining aspect ratio
   * with letterbox or pillarbox bars as needed.
   */
  FULL_WITH_ASPECT = 0,
  // @aidl-doc
  /**
   * The full frame is displayed in the plane and stretched as needed.
   * Aspect ratio may be distorted.
   */
  FULL_STRETCH = 1,
  // @aidl-doc
  /**
   * The frame is zoomed to fill the plane maintaining aspect ratio
   * where the zoom may crop some of the video frame.
   */
  ZOOM_WITH_ASPECT = 2,
};
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
[[nodiscard]] static inline std::string toString(AspectRatio val) {
  switch(val) {
  case AspectRatio::FULL_WITH_ASPECT:
    return "FULL_WITH_ASPECT";
  case AspectRatio::FULL_STRETCH:
    return "FULL_STRETCH";
  case AspectRatio::ZOOM_WITH_ASPECT:
    return "ZOOM_WITH_ASPECT";
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
constexpr inline std::array<::com::rdk::hal::planecontrol::AspectRatio, 3> enum_values<::com::rdk::hal::planecontrol::AspectRatio> = {
  ::com::rdk::hal::planecontrol::AspectRatio::FULL_WITH_ASPECT,
  ::com::rdk::hal::planecontrol::AspectRatio::FULL_STRETCH,
  ::com::rdk::hal::planecontrol::AspectRatio::ZOOM_WITH_ASPECT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
