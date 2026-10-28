#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief     Audio Quality Processor type.
 * Enumerates available audio quality processors supported by the platform,
 *            such as Dolby MS12, DTS, or vendor-specific implementations. Used for
 *            selection and capability discovery on audio output ports.
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 * @author   Gerald Weatherup
 */
enum class AQProcessor : int32_t {
  // @aidl-doc
  /** Undefined or no AQ processor. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Dolby MS12 2.6 audio processor (compatible with MS12 2.5). */
  DOLBY_MS12_2_6 = 1,
  // @aidl-doc
  /** DTS:X Ultra processor. */
  DTS_ULTRA = 2,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(AQProcessor val) {
  switch(val) {
  case AQProcessor::UNDEFINED:
    return "UNDEFINED";
  case AQProcessor::DOLBY_MS12_2_6:
    return "DOLBY_MS12_2_6";
  case AQProcessor::DTS_ULTRA:
    return "DTS_ULTRA";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::AQProcessor, 3> enum_values<::com::rdk::hal::audiomixer::AQProcessor> = {
  ::com::rdk::hal::audiomixer::AQProcessor::UNDEFINED,
  ::com::rdk::hal::audiomixer::AQProcessor::DOLBY_MS12_2_6,
  ::com::rdk::hal::audiomixer::AQProcessor::DTS_ULTRA,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
