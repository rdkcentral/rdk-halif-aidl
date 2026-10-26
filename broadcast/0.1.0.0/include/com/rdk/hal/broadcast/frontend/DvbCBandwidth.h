#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief Available DVB-C bandwidths.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbCBandwidth : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** The Tuner will automatically detect the bandwidth. */
  AUTO = 1,
  // @aidl-doc
  /** 5 MHz. */
  MHZ_5 = 2,
  // @aidl-doc
  /** 6 MHz. */
  MHZ_6 = 3,
  // @aidl-doc
  /** 7 MHz. */
  MHZ_7 = 4,
  // @aidl-doc
  /** 8 MHz. */
  MHZ_8 = 5,
};
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
[[nodiscard]] static inline std::string toString(DvbCBandwidth val) {
  switch(val) {
  case DvbCBandwidth::UNDEFINED:
    return "UNDEFINED";
  case DvbCBandwidth::AUTO:
    return "AUTO";
  case DvbCBandwidth::MHZ_5:
    return "MHZ_5";
  case DvbCBandwidth::MHZ_6:
    return "MHZ_6";
  case DvbCBandwidth::MHZ_7:
    return "MHZ_7";
  case DvbCBandwidth::MHZ_8:
    return "MHZ_8";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbCBandwidth, 6> enum_values<::com::rdk::hal::broadcast::frontend::DvbCBandwidth> = {
  ::com::rdk::hal::broadcast::frontend::DvbCBandwidth::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbCBandwidth::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbCBandwidth::MHZ_5,
  ::com::rdk::hal::broadcast::frontend::DvbCBandwidth::MHZ_6,
  ::com::rdk::hal::broadcast::frontend::DvbCBandwidth::MHZ_7,
  ::com::rdk::hal::broadcast::frontend::DvbCBandwidth::MHZ_8,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
