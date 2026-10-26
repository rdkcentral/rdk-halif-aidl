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
 * @brief Available guard intervals.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbTGuardInterval : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-selected guard interval. */
  AUTO = 1,
  // @aidl-doc
  /** 1/4. */
  GI_1_4 = 2,
  // @aidl-doc
  /** 1/8. */
  GI_1_8 = 3,
  // @aidl-doc
  /** 1/16. */
  GI_1_16 = 4,
  // @aidl-doc
  /** 1/32. */
  GI_1_32 = 5,
  // @aidl-doc
  /** 1/128. */
  GI_1_128 = 6,
  // @aidl-doc
  /** 19/128. */
  GI_19_128 = 7,
  // @aidl-doc
  /** 19/256. */
  GI_19_256 = 8,
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
[[nodiscard]] static inline std::string toString(DvbTGuardInterval val) {
  switch(val) {
  case DvbTGuardInterval::UNDEFINED:
    return "UNDEFINED";
  case DvbTGuardInterval::AUTO:
    return "AUTO";
  case DvbTGuardInterval::GI_1_4:
    return "GI_1_4";
  case DvbTGuardInterval::GI_1_8:
    return "GI_1_8";
  case DvbTGuardInterval::GI_1_16:
    return "GI_1_16";
  case DvbTGuardInterval::GI_1_32:
    return "GI_1_32";
  case DvbTGuardInterval::GI_1_128:
    return "GI_1_128";
  case DvbTGuardInterval::GI_19_128:
    return "GI_19_128";
  case DvbTGuardInterval::GI_19_256:
    return "GI_19_256";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbTGuardInterval, 9> enum_values<::com::rdk::hal::broadcast::frontend::DvbTGuardInterval> = {
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::GI_1_4,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::GI_1_8,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::GI_1_16,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::GI_1_32,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::GI_1_128,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::GI_19_128,
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval::GI_19_256,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
