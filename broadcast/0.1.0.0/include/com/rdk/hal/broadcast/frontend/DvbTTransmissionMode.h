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
 * @brief DVB-T Transmission modes.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbTTransmissionMode : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-selected transmission mode. */
  AUTO = 1,
  // @aidl-doc
  /** Transmission mode of 2k used in DVB-T. */
  MODE_2K = 2,
  // @aidl-doc
  /** Transmission mode of 4k used in DVB-T. */
  MODE_4K = 3,
  // @aidl-doc
  /** Transmission mode of 8k used in DVB-T. */
  MODE_8K = 4,
  // @aidl-doc
  /** Transmission mode of 1k used in DVB-T2. */
  MODE_1K = 5,
  // @aidl-doc
  /** Transmission mode of 16k used in DVB-T2. */
  MODE_16K = 6,
  // @aidl-doc
  /** Transmission mode of 32k used in DVB-T2. */
  MODE_32K = 7,
  // @aidl-doc
  /** Transmission mode of 8k extended used in DVB-T2. */
  MODE_8K_E = 8,
  // @aidl-doc
  /** Transmission mode of 16k extended used in DVB-T2. */
  MODE_16K_E = 9,
  // @aidl-doc
  /** Transmission mode of 32k extended used in DVB-T2. */
  MODE_32K_E = 10,
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
[[nodiscard]] static inline std::string toString(DvbTTransmissionMode val) {
  switch(val) {
  case DvbTTransmissionMode::UNDEFINED:
    return "UNDEFINED";
  case DvbTTransmissionMode::AUTO:
    return "AUTO";
  case DvbTTransmissionMode::MODE_2K:
    return "MODE_2K";
  case DvbTTransmissionMode::MODE_4K:
    return "MODE_4K";
  case DvbTTransmissionMode::MODE_8K:
    return "MODE_8K";
  case DvbTTransmissionMode::MODE_1K:
    return "MODE_1K";
  case DvbTTransmissionMode::MODE_16K:
    return "MODE_16K";
  case DvbTTransmissionMode::MODE_32K:
    return "MODE_32K";
  case DvbTTransmissionMode::MODE_8K_E:
    return "MODE_8K_E";
  case DvbTTransmissionMode::MODE_16K_E:
    return "MODE_16K_E";
  case DvbTTransmissionMode::MODE_32K_E:
    return "MODE_32K_E";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode, 11> enum_values<::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode> = {
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_2K,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_4K,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_8K,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_1K,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_16K,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_32K,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_8K_E,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_16K_E,
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode::MODE_32K_E,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
