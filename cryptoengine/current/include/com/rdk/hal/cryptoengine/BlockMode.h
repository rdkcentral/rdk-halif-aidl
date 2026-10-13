#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
enum class BlockMode : int32_t {
  UNSET = -1,
  CBC = 0,
  CTR = 1,
  GCM = 2,
  ECB = 3,
  KW = 4,
};
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
[[nodiscard]] static inline std::string toString(BlockMode val) {
  switch(val) {
  case BlockMode::UNSET:
    return "UNSET";
  case BlockMode::CBC:
    return "CBC";
  case BlockMode::CTR:
    return "CTR";
  case BlockMode::GCM:
    return "GCM";
  case BlockMode::ECB:
    return "ECB";
  case BlockMode::KW:
    return "KW";
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
constexpr inline std::array<::com::rdk::hal::cryptoengine::BlockMode, 6> enum_values<::com::rdk::hal::cryptoengine::BlockMode> = {
  ::com::rdk::hal::cryptoengine::BlockMode::UNSET,
  ::com::rdk::hal::cryptoengine::BlockMode::CBC,
  ::com::rdk::hal::cryptoengine::BlockMode::CTR,
  ::com::rdk::hal::cryptoengine::BlockMode::GCM,
  ::com::rdk::hal::cryptoengine::BlockMode::ECB,
  ::com::rdk::hal::cryptoengine::BlockMode::KW,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
