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
 * @brief Multiple Input Single Output (MISO) modes defined for DVB-T frontend tuning.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbTMiso : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Let the receiver determine the mode. */
  AUTO = 1,
  // @aidl-doc
  /** Single Input Single Output. */
  SISO = 2,
  // @aidl-doc
  /** Multiple Input Single Output. */
  MISO = 3,
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
[[nodiscard]] static inline std::string toString(DvbTMiso val) {
  switch(val) {
  case DvbTMiso::UNDEFINED:
    return "UNDEFINED";
  case DvbTMiso::AUTO:
    return "AUTO";
  case DvbTMiso::SISO:
    return "SISO";
  case DvbTMiso::MISO:
    return "MISO";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbTMiso, 4> enum_values<::com::rdk::hal::broadcast::frontend::DvbTMiso> = {
  ::com::rdk::hal::broadcast::frontend::DvbTMiso::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbTMiso::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbTMiso::SISO,
  ::com::rdk::hal::broadcast::frontend::DvbTMiso::MISO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
