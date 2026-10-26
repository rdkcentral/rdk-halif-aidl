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
 * @brief Available DVB-T standards.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbTStandard : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-select the standard to use, i.e. try T first and then T2 if the former has failed */
  AUTO = 1,
  // @aidl-doc
  /** Use T only. */
  T = 2,
  // @aidl-doc
  /** Use T2 only. */
  T2 = 3,
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
[[nodiscard]] static inline std::string toString(DvbTStandard val) {
  switch(val) {
  case DvbTStandard::UNDEFINED:
    return "UNDEFINED";
  case DvbTStandard::AUTO:
    return "AUTO";
  case DvbTStandard::T:
    return "T";
  case DvbTStandard::T2:
    return "T2";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbTStandard, 4> enum_values<::com::rdk::hal::broadcast::frontend::DvbTStandard> = {
  ::com::rdk::hal::broadcast::frontend::DvbTStandard::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbTStandard::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbTStandard::T,
  ::com::rdk::hal::broadcast::frontend::DvbTStandard::T2,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
