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
enum class TransmissionMode : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  MODE_2K = 2,
  MODE_4K = 3,
  MODE_8K = 4,
  MODE_1K = 5,
  MODE_16K = 6,
  MODE_32K = 7,
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
[[nodiscard]] static inline std::string toString(TransmissionMode val) {
  switch(val) {
  case TransmissionMode::UNDEFINED:
    return "UNDEFINED";
  case TransmissionMode::AUTO:
    return "AUTO";
  case TransmissionMode::MODE_2K:
    return "MODE_2K";
  case TransmissionMode::MODE_4K:
    return "MODE_4K";
  case TransmissionMode::MODE_8K:
    return "MODE_8K";
  case TransmissionMode::MODE_1K:
    return "MODE_1K";
  case TransmissionMode::MODE_16K:
    return "MODE_16K";
  case TransmissionMode::MODE_32K:
    return "MODE_32K";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::TransmissionMode, 8> enum_values<::com::rdk::hal::broadcast::frontend::TransmissionMode> = {
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::AUTO,
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::MODE_2K,
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::MODE_4K,
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::MODE_8K,
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::MODE_1K,
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::MODE_16K,
  ::com::rdk::hal::broadcast::frontend::TransmissionMode::MODE_32K,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
