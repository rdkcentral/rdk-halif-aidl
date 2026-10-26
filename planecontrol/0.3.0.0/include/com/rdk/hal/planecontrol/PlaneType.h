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
 *  @brief     Plane type definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class PlaneType : int32_t {
  // @aidl-doc
  /** Video plane. */
  VIDEO = 0,
  // @aidl-doc
  /** Graphics plane. */
  GRAPHICS = 1,
};
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
[[nodiscard]] static inline std::string toString(PlaneType val) {
  switch(val) {
  case PlaneType::VIDEO:
    return "VIDEO";
  case PlaneType::GRAPHICS:
    return "GRAPHICS";
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
constexpr inline std::array<::com::rdk::hal::planecontrol::PlaneType, 2> enum_values<::com::rdk::hal::planecontrol::PlaneType> = {
  ::com::rdk::hal::planecontrol::PlaneType::VIDEO,
  ::com::rdk::hal::planecontrol::PlaneType::GRAPHICS,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
