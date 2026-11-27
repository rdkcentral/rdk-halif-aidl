#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/** @brief SDR gamma options. */
enum class SDRGamma : int32_t {
  // @aidl-doc
  /** SDR gamma is invalid. */
  SDR_GAMMA_INVALID = -1,
  // @aidl-doc
  /** SDR gamma is 1.8. */
  SDR_GAMMA_1_8 = 0,
  // @aidl-doc
  /** SDR gamma is 1.9. */
  SDR_GAMMA_1_9 = 1,
  // @aidl-doc
  /** SDR gamma is 2.0. */
  SDR_GAMMA_2_0 = 2,
  // @aidl-doc
  /** SDR gamma is 2.1. */
  SDR_GAMMA_2_1 = 3,
  // @aidl-doc
  /** SDR gamma is 2.2. */
  SDR_GAMMA_2_2 = 4,
  // @aidl-doc
  /** SDR gamma is 2.3. */
  SDR_GAMMA_2_3 = 5,
  // @aidl-doc
  /** SDR gamma is 2.4. */
  SDR_GAMMA_2_4 = 6,
  // @aidl-doc
  /** SDR gamma is ITU-R BT.1886. */
  SDR_GAMMA_BT_1886 = 7,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(SDRGamma val) {
  switch(val) {
  case SDRGamma::SDR_GAMMA_INVALID:
    return "SDR_GAMMA_INVALID";
  case SDRGamma::SDR_GAMMA_1_8:
    return "SDR_GAMMA_1_8";
  case SDRGamma::SDR_GAMMA_1_9:
    return "SDR_GAMMA_1_9";
  case SDRGamma::SDR_GAMMA_2_0:
    return "SDR_GAMMA_2_0";
  case SDRGamma::SDR_GAMMA_2_1:
    return "SDR_GAMMA_2_1";
  case SDRGamma::SDR_GAMMA_2_2:
    return "SDR_GAMMA_2_2";
  case SDRGamma::SDR_GAMMA_2_3:
    return "SDR_GAMMA_2_3";
  case SDRGamma::SDR_GAMMA_2_4:
    return "SDR_GAMMA_2_4";
  case SDRGamma::SDR_GAMMA_BT_1886:
    return "SDR_GAMMA_BT_1886";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::SDRGamma, 9> enum_values<::com::rdk::hal::panel::SDRGamma> = {
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_INVALID,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_1_8,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_1_9,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_2_0,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_2_1,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_2_2,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_2_3,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_2_4,
  ::com::rdk::hal::panel::SDRGamma::SDR_GAMMA_BT_1886,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
