#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class PaddingMode : int32_t {
  UNSET = -1,
  NONE = 0,
  PKCS7 = 1,
  RSA_OAEP = 2,
  RSA_PSS = 3,
  RSA_PKCS1_V1_5 = 4,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(PaddingMode val) {
  switch(val) {
  case PaddingMode::UNSET:
    return "UNSET";
  case PaddingMode::NONE:
    return "NONE";
  case PaddingMode::PKCS7:
    return "PKCS7";
  case PaddingMode::RSA_OAEP:
    return "RSA_OAEP";
  case PaddingMode::RSA_PSS:
    return "RSA_PSS";
  case PaddingMode::RSA_PKCS1_V1_5:
    return "RSA_PKCS1_V1_5";
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
constexpr inline std::array<::com::rdk::hal::cryptoengine::PaddingMode, 6> enum_values<::com::rdk::hal::cryptoengine::PaddingMode> = {
  ::com::rdk::hal::cryptoengine::PaddingMode::UNSET,
  ::com::rdk::hal::cryptoengine::PaddingMode::NONE,
  ::com::rdk::hal::cryptoengine::PaddingMode::PKCS7,
  ::com::rdk::hal::cryptoengine::PaddingMode::RSA_OAEP,
  ::com::rdk::hal::cryptoengine::PaddingMode::RSA_PSS,
  ::com::rdk::hal::cryptoengine::PaddingMode::RSA_PKCS1_V1_5,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
