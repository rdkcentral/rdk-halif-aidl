#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
// @aidl-doc
/** Specifies the underlying integer type for this enum. */
enum class ContentType : int32_t {
  // @aidl-doc
  /** Unknown or undefined audio content type. */
  UNKNOWN = 0,
  // @aidl-doc
  /** Audio content primarily consisting of speech. */
  SPEECH = 1,
  // @aidl-doc
  /** Audio content primarily consisting of music. */
  MUSIC = 2,
  // @aidl-doc
  /** Audio content associated with movies or video. */
  MOVIE = 3,
  // @aidl-doc
  /** Audio content used to represent data or information through sound (also known as audibilization). */
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
