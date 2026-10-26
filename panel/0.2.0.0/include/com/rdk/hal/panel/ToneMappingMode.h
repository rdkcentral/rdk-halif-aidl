#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/** @brief HDR tone-mapping mode. */
enum class ToneMappingMode : int32_t {
  TONE_MAPPING_INVALID = -1,
  TONE_MAPPING_DYNAMIC = 0,
  TONE_MAPPING_CLIPPING = 1,
  TONE_MAPPING_STATIC = 2,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(ToneMappingMode val) {
  switch(val) {
  case ToneMappingMode::TONE_MAPPING_INVALID:
    return "TONE_MAPPING_INVALID";
  case ToneMappingMode::TONE_MAPPING_DYNAMIC:
    return "TONE_MAPPING_DYNAMIC";
  case ToneMappingMode::TONE_MAPPING_CLIPPING:
    return "TONE_MAPPING_CLIPPING";
  case ToneMappingMode::TONE_MAPPING_STATIC:
    return "TONE_MAPPING_STATIC";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::ToneMappingMode, 4> enum_values<::com::rdk::hal::panel::ToneMappingMode> = {
  ::com::rdk::hal::panel::ToneMappingMode::TONE_MAPPING_INVALID,
  ::com::rdk::hal::panel::ToneMappingMode::TONE_MAPPING_DYNAMIC,
  ::com::rdk::hal::panel::ToneMappingMode::TONE_MAPPING_CLIPPING,
  ::com::rdk::hal::panel::ToneMappingMode::TONE_MAPPING_STATIC,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
