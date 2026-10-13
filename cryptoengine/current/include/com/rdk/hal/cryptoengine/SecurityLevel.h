#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class SecurityLevel : int32_t {
  SOFTWARE = 0,
  TEE = 1,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(SecurityLevel val) {
  switch(val) {
  case SecurityLevel::SOFTWARE:
    return "SOFTWARE";
  case SecurityLevel::TEE:
    return "TEE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::cryptoengine::SecurityLevel, 2> enum_values<::com::rdk::hal::cryptoengine::SecurityLevel> = {
  ::com::rdk::hal::cryptoengine::SecurityLevel::SOFTWARE,
  ::com::rdk::hal::cryptoengine::SecurityLevel::TEE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
