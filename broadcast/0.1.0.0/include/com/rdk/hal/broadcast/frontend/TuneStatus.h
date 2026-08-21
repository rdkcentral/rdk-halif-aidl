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
enum class TuneStatus : int32_t {
  UNDEFINED = 0,
  IDLE = 1,
  TUNING = 2,
  NO_SIGNAL = 3,
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
