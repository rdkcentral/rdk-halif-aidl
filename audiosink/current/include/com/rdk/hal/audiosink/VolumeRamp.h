#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
enum class VolumeRamp : int32_t {
  LINEAR = 0,
  IN_CUBIC = 1,
  OUT_CUBIC = 2,
};
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
[[nodiscard]] static inline std::string toString(VolumeRamp val) {
  switch(val) {
  case VolumeRamp::LINEAR:
    return "LINEAR";
  case VolumeRamp::IN_CUBIC:
    return "IN_CUBIC";
  case VolumeRamp::OUT_CUBIC:
    return "OUT_CUBIC";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiosink::VolumeRamp, 3> enum_values<::com::rdk::hal::audiosink::VolumeRamp> = {
  ::com::rdk::hal::audiosink::VolumeRamp::LINEAR,
  ::com::rdk::hal::audiosink::VolumeRamp::IN_CUBIC,
  ::com::rdk::hal::audiosink::VolumeRamp::OUT_CUBIC,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
