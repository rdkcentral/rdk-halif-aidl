#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Video decoder error code definitions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class ErrorCode : int32_t {
  // @aidl-doc
  /** Placeholder. No video decoder error codes are defined yet. */
  xxxx = 1,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ErrorCode val) {
  switch(val) {
  case ErrorCode::xxxx:
    return "xxxx";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videodecoder::ErrorCode, 1> enum_values<::com::rdk::hal::videodecoder::ErrorCode> = {
  ::com::rdk::hal::videodecoder::ErrorCode::xxxx,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
