#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief Enumerates supported content types for audio mixer inputs.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
enum class ContentType : int32_t {
  // @aidl-doc
  /** Undefined or unspecified type. */
  UNDEFINED = -1,
  // @aidl-doc
  /** System sounds or short samples. */
  CLIP = 0,
  // @aidl-doc
  /** Stream of undefined length (e.g. music, TV). */
  STREAM = 1,
  // @aidl-doc
  /** Text-to-speech or voice guidance. */
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
