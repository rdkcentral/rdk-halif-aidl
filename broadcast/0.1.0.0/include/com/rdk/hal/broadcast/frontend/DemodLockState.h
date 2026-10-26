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
 * @brief Demodulator lock state.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DemodLockState : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** The demodulator has not locked onto the carrier. */
  UNLOCKED = 1,
  // @aidl-doc
  /** The demodulator has locked onto the carrier. */
  LOCKED = 2,
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
[[nodiscard]] static inline std::string toString(DemodLockState val) {
  switch(val) {
  case DemodLockState::UNDEFINED:
    return "UNDEFINED";
  case DemodLockState::UNLOCKED:
    return "UNLOCKED";
  case DemodLockState::LOCKED:
    return "LOCKED";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DemodLockState, 3> enum_values<::com::rdk::hal::broadcast::frontend::DemodLockState> = {
  ::com::rdk::hal::broadcast::frontend::DemodLockState::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DemodLockState::UNLOCKED,
  ::com::rdk::hal::broadcast::frontend::DemodLockState::LOCKED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
