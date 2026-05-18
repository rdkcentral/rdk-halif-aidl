#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
enum class State : int32_t {
  CLOSED = 0,
  STARTED = 1,
};
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
[[nodiscard]] static inline std::string toString(State val) {
  switch(val) {
  case State::CLOSED:
    return "CLOSED";
  case State::STARTED:
    return "STARTED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmicec::State, 2> enum_values<::com::rdk::hal::hdmicec::State> = {
  ::com::rdk::hal::hdmicec::State::CLOSED,
  ::com::rdk::hal::hdmicec::State::STARTED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
