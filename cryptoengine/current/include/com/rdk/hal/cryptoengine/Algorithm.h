#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class Algorithm : int32_t {
  UNSET = -1,
  AES = 0,
  EC = 1,
  HMAC = 2,
  RSA = 3,
  CHACHA20_POLY1305 = 4,
  CMAC = 5,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(Algorithm val) {
  switch(val) {
  case Algorithm::UNSET:
    return "UNSET";
  case Algorithm::AES:
    return "AES";
  case Algorithm::EC:
    return "EC";
  case Algorithm::HMAC:
    return "HMAC";
  case Algorithm::RSA:
    return "RSA";
  case Algorithm::CHACHA20_POLY1305:
    return "CHACHA20_POLY1305";
  case Algorithm::CMAC:
    return "CMAC";
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
constexpr inline std::array<::com::rdk::hal::cryptoengine::Algorithm, 7> enum_values<::com::rdk::hal::cryptoengine::Algorithm> = {
  ::com::rdk::hal::cryptoengine::Algorithm::UNSET,
  ::com::rdk::hal::cryptoengine::Algorithm::AES,
  ::com::rdk::hal::cryptoengine::Algorithm::EC,
  ::com::rdk::hal::cryptoengine::Algorithm::HMAC,
  ::com::rdk::hal::cryptoengine::Algorithm::RSA,
  ::com::rdk::hal::cryptoengine::Algorithm::CHACHA20_POLY1305,
  ::com::rdk::hal::cryptoengine::Algorithm::CMAC,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
