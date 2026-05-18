#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
enum class ContentType : int32_t {
  UNKNOWN = 0,
  SPEECH = 1,
  MUSIC = 2,
  MOVIE = 3,
  SONIFICATION = 4,
};
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
[[nodiscard]] static inline std::string toString(ContentType val) {
  switch(val) {
  case ContentType::UNKNOWN:
    return "UNKNOWN";
  case ContentType::SPEECH:
    return "SPEECH";
  case ContentType::MUSIC:
    return "MUSIC";
  case ContentType::MOVIE:
    return "MOVIE";
  case ContentType::SONIFICATION:
    return "SONIFICATION";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiosink::ContentType, 5> enum_values<::com::rdk::hal::audiosink::ContentType> = {
  ::com::rdk::hal::audiosink::ContentType::UNKNOWN,
  ::com::rdk::hal::audiosink::ContentType::SPEECH,
  ::com::rdk::hal::audiosink::ContentType::MUSIC,
  ::com::rdk::hal::audiosink::ContentType::MOVIE,
  ::com::rdk::hal::audiosink::ContentType::SONIFICATION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
