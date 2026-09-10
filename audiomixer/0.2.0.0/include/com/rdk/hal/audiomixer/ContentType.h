#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class ContentType : int32_t {
  UNDEFINED = -1,
  CLIP = 0,
  STREAM = 1,
  TTS = 2,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(ContentType val) {
  switch(val) {
  case ContentType::UNDEFINED:
    return "UNDEFINED";
  case ContentType::CLIP:
    return "CLIP";
  case ContentType::STREAM:
    return "STREAM";
  case ContentType::TTS:
    return "TTS";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::ContentType, 4> enum_values<::com::rdk::hal::audiomixer::ContentType> = {
  ::com::rdk::hal::audiomixer::ContentType::UNDEFINED,
  ::com::rdk::hal::audiomixer::ContentType::CLIP,
  ::com::rdk::hal::audiomixer::ContentType::STREAM,
  ::com::rdk::hal::audiomixer::ContentType::TTS,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
