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
enum class SignalDetectMode : int32_t {
  UNDEFINED = 0,
  NORMAL = 1,
  SWEEP_OPTIMIZED = 2,
  SEARCH_OPTIMIZED = 3,
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
[[nodiscard]] static inline std::string toString(SignalDetectMode val) {
  switch(val) {
  case SignalDetectMode::UNDEFINED:
    return "UNDEFINED";
  case SignalDetectMode::NORMAL:
    return "NORMAL";
  case SignalDetectMode::SWEEP_OPTIMIZED:
    return "SWEEP_OPTIMIZED";
  case SignalDetectMode::SEARCH_OPTIMIZED:
    return "SEARCH_OPTIMIZED";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::SignalDetectMode, 4> enum_values<::com::rdk::hal::broadcast::frontend::SignalDetectMode> = {
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode::NORMAL,
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode::SWEEP_OPTIMIZED,
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode::SEARCH_OPTIMIZED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
