#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class KeyDerivation : int32_t {
  UNSET = -1,
  HKDF = 0,
  PBKDF2 = 1,
  NFLX_DH = 2,
  DH = 3,
  CONCAT_KDF = 4,
  CMAC_KDF = 5,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(KeyDerivation val) {
  switch(val) {
  case KeyDerivation::UNSET:
    return "UNSET";
  case KeyDerivation::HKDF:
    return "HKDF";
  case KeyDerivation::PBKDF2:
    return "PBKDF2";
  case KeyDerivation::NFLX_DH:
    return "NFLX_DH";
  case KeyDerivation::DH:
    return "DH";
  case KeyDerivation::CONCAT_KDF:
    return "CONCAT_KDF";
  case KeyDerivation::CMAC_KDF:
    return "CMAC_KDF";
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
constexpr inline std::array<::com::rdk::hal::cryptoengine::KeyDerivation, 7> enum_values<::com::rdk::hal::cryptoengine::KeyDerivation> = {
  ::com::rdk::hal::cryptoengine::KeyDerivation::UNSET,
  ::com::rdk::hal::cryptoengine::KeyDerivation::HKDF,
  ::com::rdk::hal::cryptoengine::KeyDerivation::PBKDF2,
  ::com::rdk::hal::cryptoengine::KeyDerivation::NFLX_DH,
  ::com::rdk::hal::cryptoengine::KeyDerivation::DH,
  ::com::rdk::hal::cryptoengine::KeyDerivation::CONCAT_KDF,
  ::com::rdk::hal::cryptoengine::KeyDerivation::CMAC_KDF,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
