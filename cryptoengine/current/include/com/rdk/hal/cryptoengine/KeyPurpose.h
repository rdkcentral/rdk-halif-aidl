#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class KeyPurpose : int32_t {
  ENCRYPT = 1,
  DECRYPT = 2,
  SIGN = 4,
  VERIFY = 8,
  AGREE_KEY = 16,
  WRAP_KEY = 32,
  UNWRAP_KEY = 64,
  DERIVE_KEY = 128,
  DERIVE_BITS = 256,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(KeyPurpose val) {
  switch(val) {
  case KeyPurpose::ENCRYPT:
    return "ENCRYPT";
  case KeyPurpose::DECRYPT:
    return "DECRYPT";
  case KeyPurpose::SIGN:
    return "SIGN";
  case KeyPurpose::VERIFY:
    return "VERIFY";
  case KeyPurpose::AGREE_KEY:
    return "AGREE_KEY";
  case KeyPurpose::WRAP_KEY:
    return "WRAP_KEY";
  case KeyPurpose::UNWRAP_KEY:
    return "UNWRAP_KEY";
  case KeyPurpose::DERIVE_KEY:
    return "DERIVE_KEY";
  case KeyPurpose::DERIVE_BITS:
    return "DERIVE_BITS";
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
constexpr inline std::array<::com::rdk::hal::cryptoengine::KeyPurpose, 9> enum_values<::com::rdk::hal::cryptoengine::KeyPurpose> = {
  ::com::rdk::hal::cryptoengine::KeyPurpose::ENCRYPT,
  ::com::rdk::hal::cryptoengine::KeyPurpose::DECRYPT,
  ::com::rdk::hal::cryptoengine::KeyPurpose::SIGN,
  ::com::rdk::hal::cryptoengine::KeyPurpose::VERIFY,
  ::com::rdk::hal::cryptoengine::KeyPurpose::AGREE_KEY,
  ::com::rdk::hal::cryptoengine::KeyPurpose::WRAP_KEY,
  ::com::rdk::hal::cryptoengine::KeyPurpose::UNWRAP_KEY,
  ::com::rdk::hal::cryptoengine::KeyPurpose::DERIVE_KEY,
  ::com::rdk::hal::cryptoengine::KeyPurpose::DERIVE_BITS,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
