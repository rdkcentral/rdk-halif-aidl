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
 * @brief Spectral inversion modes for broadcast frontend tuning.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class SpectralInversion : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Automatically detect spectral inversion. */
  AUTO = 1,
  // @aidl-doc
  /** Use normal spectral orientation. */
  NORMAL = 2,
  // @aidl-doc
  /** Use inverted spectral orientation. */
  INVERTED = 3,
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
[[nodiscard]] static inline std::string toString(SpectralInversion val) {
  switch(val) {
  case SpectralInversion::UNDEFINED:
    return "UNDEFINED";
  case SpectralInversion::AUTO:
    return "AUTO";
  case SpectralInversion::NORMAL:
    return "NORMAL";
  case SpectralInversion::INVERTED:
    return "INVERTED";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::SpectralInversion, 4> enum_values<::com::rdk::hal::broadcast::frontend::SpectralInversion> = {
  ::com::rdk::hal::broadcast::frontend::SpectralInversion::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::SpectralInversion::AUTO,
  ::com::rdk::hal::broadcast::frontend::SpectralInversion::NORMAL,
  ::com::rdk::hal::broadcast::frontend::SpectralInversion::INVERTED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
