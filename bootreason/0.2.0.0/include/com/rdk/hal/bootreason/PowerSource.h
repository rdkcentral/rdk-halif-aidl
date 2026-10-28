#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
// @aidl-doc
/**
 *  @brief     Power source types.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
enum class PowerSource : int32_t {
  // @aidl-doc
  /** The device power source cannot be determined. */
  UNKNOWN = 0,
  // @aidl-doc
  /**
   * The device power source is from an external PSU.
   *
   */
  PSU = 1,
  // @aidl-doc
  /** The device power source is from USB. */
  USB = 2,
  // @aidl-doc
  /** The device power source is from POE (Power over Ethernet). */
  POE = 3,
};
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
[[nodiscard]] static inline std::string toString(PowerSource val) {
  switch(val) {
  case PowerSource::UNKNOWN:
    return "UNKNOWN";
  case PowerSource::PSU:
    return "PSU";
  case PowerSource::USB:
    return "USB";
  case PowerSource::POE:
    return "POE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::bootreason::PowerSource, 4> enum_values<::com::rdk::hal::bootreason::PowerSource> = {
  ::com::rdk::hal::bootreason::PowerSource::UNKNOWN,
  ::com::rdk::hal::bootreason::PowerSource::PSU,
  ::com::rdk::hal::bootreason::PowerSource::USB,
  ::com::rdk::hal::bootreason::PowerSource::POE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
