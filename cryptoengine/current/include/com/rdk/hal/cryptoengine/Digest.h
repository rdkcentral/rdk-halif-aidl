#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class Digest : int32_t {
  UNSET = -1,
  NONE = 0,
  SHA_2_224 = 2,
  SHA_2_256 = 3,
  SHA_2_384 = 4,
  SHA_2_512 = 5,
  SHA_3_256 = 6,
  SHA_3_384 = 7,
  SHA_3_512 = 8,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(Digest val) {
  switch(val) {
  case Digest::UNSET:
    return "UNSET";
  case Digest::NONE:
    return "NONE";
  case Digest::SHA_2_224:
    return "SHA_2_224";
  case Digest::SHA_2_256:
    return "SHA_2_256";
  case Digest::SHA_2_384:
    return "SHA_2_384";
  case Digest::SHA_2_512:
    return "SHA_2_512";
  case Digest::SHA_3_256:
    return "SHA_3_256";
  case Digest::SHA_3_384:
    return "SHA_3_384";
  case Digest::SHA_3_512:
    return "SHA_3_512";
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
constexpr inline std::array<::com::rdk::hal::cryptoengine::Digest, 9> enum_values<::com::rdk::hal::cryptoengine::Digest> = {
  ::com::rdk::hal::cryptoengine::Digest::UNSET,
  ::com::rdk::hal::cryptoengine::Digest::NONE,
  ::com::rdk::hal::cryptoengine::Digest::SHA_2_224,
  ::com::rdk::hal::cryptoengine::Digest::SHA_2_256,
  ::com::rdk::hal::cryptoengine::Digest::SHA_2_384,
  ::com::rdk::hal::cryptoengine::Digest::SHA_2_512,
  ::com::rdk::hal::cryptoengine::Digest::SHA_3_256,
  ::com::rdk::hal::cryptoengine::Digest::SHA_3_384,
  ::com::rdk::hal::cryptoengine::Digest::SHA_3_512,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
