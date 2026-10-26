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
enum class DvbCModulation : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-selected modulation. */
  AUTO = 1,
  // @aidl-doc
  /** QAM_16. */
  QAM_16 = 2,
  // @aidl-doc
  /** QAM_32. */
  QAM_32 = 3,
  // @aidl-doc
  /** QAM_64. */
  QAM_64 = 4,
  // @aidl-doc
  /** QAM_128. */
  QAM_128 = 5,
  // @aidl-doc
  /** QAM_256. */
  QAM_256 = 6,
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
[[nodiscard]] static inline std::string toString(DvbCModulation val) {
  switch(val) {
  case DvbCModulation::UNDEFINED:
    return "UNDEFINED";
  case DvbCModulation::AUTO:
    return "AUTO";
  case DvbCModulation::QAM_16:
    return "QAM_16";
  case DvbCModulation::QAM_32:
    return "QAM_32";
  case DvbCModulation::QAM_64:
    return "QAM_64";
  case DvbCModulation::QAM_128:
    return "QAM_128";
  case DvbCModulation::QAM_256:
    return "QAM_256";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbCModulation, 7> enum_values<::com::rdk::hal::broadcast::frontend::DvbCModulation> = {
  ::com::rdk::hal::broadcast::frontend::DvbCModulation::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbCModulation::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbCModulation::QAM_16,
  ::com::rdk::hal::broadcast::frontend::DvbCModulation::QAM_32,
  ::com::rdk::hal::broadcast::frontend::DvbCModulation::QAM_64,
  ::com::rdk::hal::broadcast::frontend::DvbCModulation::QAM_128,
  ::com::rdk::hal::broadcast::frontend::DvbCModulation::QAM_256,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
