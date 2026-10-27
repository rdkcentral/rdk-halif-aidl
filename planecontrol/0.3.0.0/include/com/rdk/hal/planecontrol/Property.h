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
 *  @brief     Plane properties definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Unique 0 based index per plane resource instance.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  RESOURCE_ID = 0,
  // @aidl-doc
  /**
   * Left coordinate of the plane inside its frame coordinates.
   *
   * Type: Integer
   * Default is 0.
   * Access: Read-write.
   */
  X = 1,
  // @aidl-doc
  /**
   * Top coordinate of the plane inside its frame coordinates.
   *
   * Type: Integer
   * Default is 0.
   * Access: Read-write.
   */
  Y = 2,
  // @aidl-doc
  /**
   * Width of the plane inside its reference frame coordinates.
   *
   * Type: Integer
   * Default is Capabilities.maxWidth.
   * Access: Read-write.
   */
  WIDTH = 3,
  // @aidl-doc
  /**
   * Height of the plane inside its reference frame coordinates.
   *
   * Type: Integer
   * Default is Capabilities.maxHeight.
   * Access: Read-write.
   */
  HEIGHT = 4,
  // @aidl-doc
  /**
   * Alpha blending value for the whole plane. 0=transparent, 255=opaque.
   *
   * Type: Integer
   * Default is 255.
   * Access: Read-write.
   * @pre Capabilities.supportsAlpha must be true to support this property.
   */
  ALPHA = 5,
  // @aidl-doc
  /**
   * Z-order position of the plane. Higher z-order planes are composited above lower z-order planes.
   *
   * Type: Integer
   * Default is RESOURCE_ID property index.
   * Access: Read-write.
   */
  ZORDER = 6,
  // @aidl-doc
  /**
   * Visibility of the plane.
   *
   * Type: Integer
   *  0 - invisible (default)
   *  1 - visible
   * Access: Read-write.
   */
  VISIBLE = 7,
  // @aidl-doc
  /**
   * Overscan applied to a video frames presented on the video plane.
   * Overscan is specified in percentage and applied equally to all edges.
   * Overscan only applied to `VIDEO` planes.
   *
   * Type: Integer
   *  0 - full image (no overscan).
   * Access: Read-write.
   */
  OVERSCAN = 8,
  // @aidl-doc
  /**
   * Aspect ratio applied to a video plane.
   * Values are enumerated in AspectRatio.
   *
   * Type: Integer - enum AspectRatio
   *  0 - AspectRatio::FULL_WITH_ASPECT
   * Access: Read-write.
   */
  ASPECT_RATIO = 9,
};
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::X:
    return "X";
  case Property::Y:
    return "Y";
  case Property::WIDTH:
    return "WIDTH";
  case Property::HEIGHT:
    return "HEIGHT";
  case Property::ALPHA:
    return "ALPHA";
  case Property::ZORDER:
    return "ZORDER";
  case Property::VISIBLE:
    return "VISIBLE";
  case Property::OVERSCAN:
    return "OVERSCAN";
  case Property::ASPECT_RATIO:
    return "ASPECT_RATIO";
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
constexpr inline std::array<::com::rdk::hal::planecontrol::Property, 10> enum_values<::com::rdk::hal::planecontrol::Property> = {
  ::com::rdk::hal::planecontrol::Property::RESOURCE_ID,
  ::com::rdk::hal::planecontrol::Property::X,
  ::com::rdk::hal::planecontrol::Property::Y,
  ::com::rdk::hal::planecontrol::Property::WIDTH,
  ::com::rdk::hal::planecontrol::Property::HEIGHT,
  ::com::rdk::hal::planecontrol::Property::ALPHA,
  ::com::rdk::hal::planecontrol::Property::ZORDER,
  ::com::rdk::hal::planecontrol::Property::VISIBLE,
  ::com::rdk::hal::planecontrol::Property::OVERSCAN,
  ::com::rdk::hal::planecontrol::Property::ASPECT_RATIO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
