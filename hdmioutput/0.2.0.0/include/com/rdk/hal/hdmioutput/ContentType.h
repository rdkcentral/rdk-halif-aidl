#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI content type enum.
 *
 *  Maps to the AVI InfoFrame fields ITC (InfoFrame Type Code) and CN (Content Type),
 *  allowing source devices to indicate the intended content profile for the video stream.
 *
 *  Reference: HDMI Specification – AVI InfoFrame ITC/CN fields.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class ContentType : int32_t {
  // @aidl-doc
  /** Content type not specified – AVI InfoFrame ITC=0 */
  UNSPECIFIED = -1,
  // @aidl-doc
  /** Graphics content – AVI InfoFrame ITC=1, CN=0 */
  GRAPHICS = 0,
  // @aidl-doc
  /** Photo content – AVI InfoFrame ITC=1, CN=1 */
  PHOTO = 1,
  // @aidl-doc
  /**
   * Cinema content – AVI InfoFrame ITC=1, CN=2
   *
   * Also used to declare FilmMaker Mode.
   */
  CINEMA = 2,
  // @aidl-doc
  /**
   * Game content – AVI InfoFrame ITC=1, CN=3
   *
   * Suggests the sink device enter low-latency mode or switch to a game-optimised picture mode.
   */
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
