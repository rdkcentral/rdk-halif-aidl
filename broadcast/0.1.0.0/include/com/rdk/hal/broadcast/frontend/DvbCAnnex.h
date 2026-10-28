#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief Available DVB-C standards.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbCAnnex : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-select the annex to use. */
  AUTO = 1,
  // @aidl-doc
  /** DVB-C Annex A. */
  A = 2,
  // @aidl-doc
  /** DVB-C Annex B. */
  B = 3,
  // @aidl-doc
  /** DVB-C Annex C. */
  C = 4,
};
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
[[nodiscard]] static inline std::string toString(DvbCAnnex val) {
  switch(val) {
  case DvbCAnnex::UNDEFINED:
    return "UNDEFINED";
  case DvbCAnnex::AUTO:
    return "AUTO";
  case DvbCAnnex::A:
    return "A";
  case DvbCAnnex::B:
    return "B";
  case DvbCAnnex::C:
    return "C";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbCAnnex, 5> enum_values<::com::rdk::hal::broadcast::frontend::DvbCAnnex> = {
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::A,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::B,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::C,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
