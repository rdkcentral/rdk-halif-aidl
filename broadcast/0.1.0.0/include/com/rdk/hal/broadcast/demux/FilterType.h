#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
// @aidl-doc
/**
 * @brief Demux filter types.
 *
 * This enum is semantically coupled to Filter: every concrete filter type listed here must have a corresponding member
 * in Filter.
 *
 * Note: These enum values are not used as the Filter union tag. The union discriminator is generated separately by
 * AIDL.
 *
 * @see Filter
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class FilterType : int32_t {
  // @aidl-doc
  /** Clean value when default initialized */
  UNDEFINED = 0,
  // @aidl-doc
  /** Mpeg2 transport stream data packets */
  MPEG2TS_DATA = 1,
  // @aidl-doc
  /** Mpeg2 transport stream clock packets */
  MPEG2TS_CLOCK = 2,
  // @aidl-doc
  /** Mpeg2 transport stream video packets */
  MPEG2TS_VIDEO = 3,
  // @aidl-doc
  /** Mpeg2 transport stream audio packets */
  MPEG2TS_AUDIO = 4,
  // @aidl-doc
  /** Mpeg2 transport stream supplementary audio packets */
  MPEG2TS_SUPPLEMENTARY_AUDIO = 5,
};
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
[[nodiscard]] static inline std::string toString(FilterType val) {
  switch(val) {
  case FilterType::UNDEFINED:
    return "UNDEFINED";
  case FilterType::MPEG2TS_DATA:
    return "MPEG2TS_DATA";
  case FilterType::MPEG2TS_CLOCK:
    return "MPEG2TS_CLOCK";
  case FilterType::MPEG2TS_VIDEO:
    return "MPEG2TS_VIDEO";
  case FilterType::MPEG2TS_AUDIO:
    return "MPEG2TS_AUDIO";
  case FilterType::MPEG2TS_SUPPLEMENTARY_AUDIO:
    return "MPEG2TS_SUPPLEMENTARY_AUDIO";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::demux::FilterType, 6> enum_values<::com::rdk::hal::broadcast::demux::FilterType> = {
  ::com::rdk::hal::broadcast::demux::FilterType::UNDEFINED,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_DATA,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_CLOCK,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_VIDEO,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_AUDIO,
  ::com::rdk::hal::broadcast::demux::FilterType::MPEG2TS_SUPPLEMENTARY_AUDIO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
