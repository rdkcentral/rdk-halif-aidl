#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
enum class VaultState : int32_t {
  READY = 0,
  ERROR = 1,
};
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
[[nodiscard]] static inline std::string toString(VaultState val) {
  switch(val) {
  case VaultState::READY:
    return "READY";
  case VaultState::ERROR:
    return "ERROR";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::keyvault::VaultState, 2> enum_values<::com::rdk::hal::keyvault::VaultState> = {
  ::com::rdk::hal::keyvault::VaultState::READY,
  ::com::rdk::hal::keyvault::VaultState::ERROR,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
