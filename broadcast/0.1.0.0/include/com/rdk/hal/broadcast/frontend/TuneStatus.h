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
 * @brief TuneStatus enum.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class TuneStatus : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** The frontend is currently idle. */
  IDLE = 1,
  // @aidl-doc
  /** The frontend is trying to obtain lock. */
  TUNING = 2,
  // @aidl-doc
  /** The frontend was not able to lock to the requested tune parameters. */
  NO_SIGNAL = 3,
  // @aidl-doc
  /** The frontend is locked to a signal. */
  LOCKED = 4,
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
[[nodiscard]] static inline std::string toString(TuneStatus val) {
  switch(val) {
  case TuneStatus::UNDEFINED:
    return "UNDEFINED";
  case TuneStatus::IDLE:
    return "IDLE";
  case TuneStatus::TUNING:
    return "TUNING";
  case TuneStatus::NO_SIGNAL:
    return "NO_SIGNAL";
  case TuneStatus::LOCKED:
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::TuneStatus, 5> enum_values<::com::rdk::hal::broadcast::frontend::TuneStatus> = {
  ::com::rdk::hal::broadcast::frontend::TuneStatus::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::TuneStatus::IDLE,
  ::com::rdk::hal::broadcast::frontend::TuneStatus::TUNING,
  ::com::rdk::hal::broadcast::frontend::TuneStatus::NO_SIGNAL,
  ::com::rdk::hal::broadcast::frontend::TuneStatus::LOCKED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
