#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class EcCurve : int32_t {
  UNSET = -1,
  P_256 = 0,
  P_384 = 1,
  P_521 = 2,
  ED25519 = 3,
  X25519 = 4,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(EcCurve val) {
  switch(val) {
  case EcCurve::UNSET:
    return "UNSET";
  case EcCurve::P_256:
    return "P_256";
  case EcCurve::P_384:
    return "P_384";
  case EcCurve::P_521:
    return "P_521";
  case EcCurve::ED25519:
    return "ED25519";
  case EcCurve::X25519:
    return "X25519";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::cryptoengine::EcCurve, 6> enum_values<::com::rdk::hal::cryptoengine::EcCurve> = {
  ::com::rdk::hal::cryptoengine::EcCurve::UNSET,
  ::com::rdk::hal::cryptoengine::EcCurve::P_256,
  ::com::rdk::hal::cryptoengine::EcCurve::P_384,
  ::com::rdk::hal::cryptoengine::EcCurve::P_521,
  ::com::rdk::hal::cryptoengine::EcCurve::ED25519,
  ::com::rdk::hal::cryptoengine::EcCurve::X25519,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
