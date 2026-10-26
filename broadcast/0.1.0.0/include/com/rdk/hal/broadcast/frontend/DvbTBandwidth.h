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
 * @brief Available DVB-T bandwidths.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbTBandwidth : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** The Tuner will automatically detect the bandwidth. */
  AUTO = 1,
  // @aidl-doc
  /** 1.712 MHz. */
  MHZ_1_712 = 2,
  // @aidl-doc
  /** 5 MHz. */
  MHZ_5 = 3,
  // @aidl-doc
  /** 6 MHz. */
  MHZ_6 = 4,
  // @aidl-doc
  /** 7 MHz. */
  MHZ_7 = 5,
  // @aidl-doc
  /** 8 MHz. */
  MHZ_8 = 6,
  // @aidl-doc
  /** 10 MHz. */
  MHZ_10 = 7,
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
[[nodiscard]] static inline std::string toString(DvbTBandwidth val) {
  switch(val) {
  case DvbTBandwidth::UNDEFINED:
    return "UNDEFINED";
  case DvbTBandwidth::AUTO:
    return "AUTO";
  case DvbTBandwidth::MHZ_1_712:
    return "MHZ_1_712";
  case DvbTBandwidth::MHZ_5:
    return "MHZ_5";
  case DvbTBandwidth::MHZ_6:
    return "MHZ_6";
  case DvbTBandwidth::MHZ_7:
    return "MHZ_7";
  case DvbTBandwidth::MHZ_8:
    return "MHZ_8";
  case DvbTBandwidth::MHZ_10:
    return "MHZ_10";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbTBandwidth, 8> enum_values<::com::rdk::hal::broadcast::frontend::DvbTBandwidth> = {
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::MHZ_1_712,
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::MHZ_5,
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::MHZ_6,
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::MHZ_7,
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::MHZ_8,
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth::MHZ_10,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
