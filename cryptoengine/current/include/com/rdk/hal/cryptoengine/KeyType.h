#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class KeyType : int32_t {
  SECRET = 0,
  PUBLIC = 1,
  PRIVATE = 2,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(KeyType val) {
  switch(val) {
  case KeyType::SECRET:
    return "SECRET";
  case KeyType::PUBLIC:
    return "PUBLIC";
  case KeyType::PRIVATE:
    return "PRIVATE";
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
constexpr inline std::array<::com::rdk::hal::cryptoengine::KeyType, 3> enum_values<::com::rdk::hal::cryptoengine::KeyType> = {
  ::com::rdk::hal::cryptoengine::KeyType::SECRET,
  ::com::rdk::hal::cryptoengine::KeyType::PUBLIC,
  ::com::rdk::hal::cryptoengine::KeyType::PRIVATE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
