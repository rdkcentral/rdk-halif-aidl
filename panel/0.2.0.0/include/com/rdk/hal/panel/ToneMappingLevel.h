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
/** @brief HDR tone-mapping level. */
enum class ToneMappingLevel : int32_t {
  // @aidl-doc
  /** Invalid or unset level. */
  TONE_MAPPING_LEVEL_INVALID = -1,
  // @aidl-doc
  /** The tone-mapping mode has no selectable levels. */
  TONE_MAPPING_LEVEL_NOT_APPLICABLE = 0,
  // @aidl-doc
  /** Low tone-mapping level. */
  TONE_MAPPING_LEVEL_LOW = 1,
  // @aidl-doc
  /** Medium tone-mapping level. */
  TONE_MAPPING_LEVEL_MEDIUM = 2,
  // @aidl-doc
  /** High tone-mapping level. */
  TONE_MAPPING_LEVEL_HIGH = 3,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(ToneMappingLevel val) {
  switch(val) {
  case ToneMappingLevel::TONE_MAPPING_LEVEL_INVALID:
    return "TONE_MAPPING_LEVEL_INVALID";
  case ToneMappingLevel::TONE_MAPPING_LEVEL_NOT_APPLICABLE:
    return "TONE_MAPPING_LEVEL_NOT_APPLICABLE";
  case ToneMappingLevel::TONE_MAPPING_LEVEL_LOW:
    return "TONE_MAPPING_LEVEL_LOW";
  case ToneMappingLevel::TONE_MAPPING_LEVEL_MEDIUM:
    return "TONE_MAPPING_LEVEL_MEDIUM";
  case ToneMappingLevel::TONE_MAPPING_LEVEL_HIGH:
    return "TONE_MAPPING_LEVEL_HIGH";
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
constexpr inline std::array<::com::rdk::hal::panel::ToneMappingLevel, 5> enum_values<::com::rdk::hal::panel::ToneMappingLevel> = {
  ::com::rdk::hal::panel::ToneMappingLevel::TONE_MAPPING_LEVEL_INVALID,
  ::com::rdk::hal::panel::ToneMappingLevel::TONE_MAPPING_LEVEL_NOT_APPLICABLE,
  ::com::rdk::hal::panel::ToneMappingLevel::TONE_MAPPING_LEVEL_LOW,
  ::com::rdk::hal::panel::ToneMappingLevel::TONE_MAPPING_LEVEL_MEDIUM,
  ::com::rdk::hal::panel::ToneMappingLevel::TONE_MAPPING_LEVEL_HIGH,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
