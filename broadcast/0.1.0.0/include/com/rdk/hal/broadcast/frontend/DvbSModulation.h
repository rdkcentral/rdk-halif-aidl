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
 * @brief Available modulations.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbSModulation : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-selected modulation. */
  AUTO = 1,
  // @aidl-doc
  /** QPSK. */
  QPSK = 2,
  // @aidl-doc
  /** PSK_8. */
  PSK_8 = 3,
  // @aidl-doc
  /** PSK_16. */
  PSK_16 = 4,
  // @aidl-doc
  /** PSK_32. */
  PSK_32 = 5,
  // @aidl-doc
  /** APSK_8. */
  APSK_8 = 6,
  // @aidl-doc
  /** APSK_16. */
  APSK_16 = 7,
  // @aidl-doc
  /** APSK_32. */
  APSK_32 = 8,
  // @aidl-doc
  /** APSK_64. */
  APSK_64 = 9,
  // @aidl-doc
  /** APSK_128. */
  APSK_128 = 10,
  // @aidl-doc
  /** APSK_256. */
  APSK_256 = 11,
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
[[nodiscard]] static inline std::string toString(DvbSModulation val) {
  switch(val) {
  case DvbSModulation::UNDEFINED:
    return "UNDEFINED";
  case DvbSModulation::AUTO:
    return "AUTO";
  case DvbSModulation::QPSK:
    return "QPSK";
  case DvbSModulation::PSK_8:
    return "PSK_8";
  case DvbSModulation::PSK_16:
    return "PSK_16";
  case DvbSModulation::PSK_32:
    return "PSK_32";
  case DvbSModulation::APSK_8:
    return "APSK_8";
  case DvbSModulation::APSK_16:
    return "APSK_16";
  case DvbSModulation::APSK_32:
    return "APSK_32";
  case DvbSModulation::APSK_64:
    return "APSK_64";
  case DvbSModulation::APSK_128:
    return "APSK_128";
  case DvbSModulation::APSK_256:
    return "APSK_256";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbSModulation, 12> enum_values<::com::rdk::hal::broadcast::frontend::DvbSModulation> = {
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::QPSK,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::PSK_8,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::PSK_16,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::PSK_32,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::APSK_8,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::APSK_16,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::APSK_32,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::APSK_64,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::APSK_128,
  ::com::rdk::hal::broadcast::frontend::DvbSModulation::APSK_256,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
