#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
// @aidl-doc
/** Enumerate the supported crypto modes */
enum class Mode : int32_t {
  // @aidl-doc
  /** The data is not encrypted. */
  UNENCRYPTED = 0,
  // @aidl-doc
  /** AES counter mode (CTR). */
  AES_CTR = 1,
  // @aidl-doc
  /** AES cipher block chaining with ciphertext stealing (CBC-CTS). */
  AES_CBC_CTS = 2,
  // @aidl-doc
  /** AES cipher block chaining (CBC). */
  AES_CBC = 3,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(Mode val) {
  switch(val) {
  case Mode::UNENCRYPTED:
    return "UNENCRYPTED";
  case Mode::AES_CTR:
    return "AES_CTR";
  case Mode::AES_CBC_CTS:
    return "AES_CBC_CTS";
  case Mode::AES_CBC:
    return "AES_CBC";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::drm::Mode, 4> enum_values<::com::rdk::hal::drm::Mode> = {
  ::com::rdk::hal::drm::Mode::UNENCRYPTED,
  ::com::rdk::hal::drm::Mode::AES_CTR,
  ::com::rdk::hal::drm::Mode::AES_CBC_CTS,
  ::com::rdk::hal::drm::Mode::AES_CBC,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
