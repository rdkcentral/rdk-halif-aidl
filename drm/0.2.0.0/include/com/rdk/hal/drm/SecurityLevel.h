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
/** The security level of a drm plugin or session. */
enum class SecurityLevel : int32_t {
  // @aidl-doc
  /** Unable to determine the security level */
  UNKNOWN = 0,
  // @aidl-doc
  /** Software-based whitebox crypto */
  SW_SECURE_CRYPTO = 1,
  // @aidl-doc
  /** Software-based whitebox crypto and an obfuscated decoder */
  SW_SECURE_DECODE = 2,
  // @aidl-doc
  /**
   * DRM key management and crypto operations are performed within a
   * hardware backed trusted execution environment
   */
  HW_SECURE_CRYPTO = 3,
  // @aidl-doc
  /**
   * DRM key management, crypto operations and decoding of content
   * are performed within a hardware backed trusted execution environment
   */
  HW_SECURE_DECODE = 4,
  // @aidl-doc
  /**
   * DRM key management, crypto operations, decoding of content and all
   * handling of the media (compressed and uncompressed) is handled within
   * a hardware backed trusted execution environment.
   */
  HW_SECURE_ALL = 5,
  // @aidl-doc
  /**
   * The default security level is defined as the highest security level
   * supported on the device.
   */
  DEFAULT = 6,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(SecurityLevel val) {
  switch(val) {
  case SecurityLevel::UNKNOWN:
    return "UNKNOWN";
  case SecurityLevel::SW_SECURE_CRYPTO:
    return "SW_SECURE_CRYPTO";
  case SecurityLevel::SW_SECURE_DECODE:
    return "SW_SECURE_DECODE";
  case SecurityLevel::HW_SECURE_CRYPTO:
    return "HW_SECURE_CRYPTO";
  case SecurityLevel::HW_SECURE_DECODE:
    return "HW_SECURE_DECODE";
  case SecurityLevel::HW_SECURE_ALL:
    return "HW_SECURE_ALL";
  case SecurityLevel::DEFAULT:
    return "DEFAULT";
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
constexpr inline std::array<::com::rdk::hal::drm::SecurityLevel, 7> enum_values<::com::rdk::hal::drm::SecurityLevel> = {
  ::com::rdk::hal::drm::SecurityLevel::UNKNOWN,
  ::com::rdk::hal::drm::SecurityLevel::SW_SECURE_CRYPTO,
  ::com::rdk::hal::drm::SecurityLevel::SW_SECURE_DECODE,
  ::com::rdk::hal::drm::SecurityLevel::HW_SECURE_CRYPTO,
  ::com::rdk::hal::drm::SecurityLevel::HW_SECURE_DECODE,
  ::com::rdk::hal::drm::SecurityLevel::HW_SECURE_ALL,
  ::com::rdk::hal::drm::SecurityLevel::DEFAULT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
