#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class ContentType : int32_t {
  UNSPECIFIED = -1,
  GRAPHICS = 0,
  PHOTO = 1,
  CINEMA = 2,
  GAME = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(ContentType val) {
  switch(val) {
  case ContentType::UNSPECIFIED:
    return "UNSPECIFIED";
  case ContentType::GRAPHICS:
    return "GRAPHICS";
  case ContentType::PHOTO:
    return "PHOTO";
  case ContentType::CINEMA:
    return "CINEMA";
  case ContentType::GAME:
    return "GAME";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::ContentType, 5> enum_values<::com::rdk::hal::hdmioutput::ContentType> = {
  ::com::rdk::hal::hdmioutput::ContentType::UNSPECIFIED,
  ::com::rdk::hal::hdmioutput::ContentType::GRAPHICS,
  ::com::rdk::hal::hdmioutput::ContentType::PHOTO,
  ::com::rdk::hal::hdmioutput::ContentType::CINEMA,
  ::com::rdk::hal::hdmioutput::ContentType::GAME,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
