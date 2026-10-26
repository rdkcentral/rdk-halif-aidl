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
 * @brief Hierarchical transmission modes defined for DVB-T tuning.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbTHierarchy : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Automatically detect the hierarchy. */
  AUTO = 1,
  // @aidl-doc
  /** Non-hierarchical transmission. */
  NONE = 2,
  // @aidl-doc
  /** Hierarchical transmission with alpha 1. */
  ALPHA_1 = 3,
  // @aidl-doc
  /** Hierarchical transmission with alpha 2. */
  ALPHA_2 = 4,
  // @aidl-doc
  /** Hierarchical transmission with alpha 4. */
  ALPHA_4 = 5,
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
[[nodiscard]] static inline std::string toString(DvbTHierarchy val) {
  switch(val) {
  case DvbTHierarchy::UNDEFINED:
    return "UNDEFINED";
  case DvbTHierarchy::AUTO:
    return "AUTO";
  case DvbTHierarchy::NONE:
    return "NONE";
  case DvbTHierarchy::ALPHA_1:
    return "ALPHA_1";
  case DvbTHierarchy::ALPHA_2:
    return "ALPHA_2";
  case DvbTHierarchy::ALPHA_4:
    return "ALPHA_4";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbTHierarchy, 6> enum_values<::com::rdk::hal::broadcast::frontend::DvbTHierarchy> = {
  ::com::rdk::hal::broadcast::frontend::DvbTHierarchy::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbTHierarchy::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbTHierarchy::NONE,
  ::com::rdk::hal::broadcast::frontend::DvbTHierarchy::ALPHA_1,
  ::com::rdk::hal::broadcast::frontend::DvbTHierarchy::ALPHA_2,
  ::com::rdk::hal::broadcast::frontend::DvbTHierarchy::ALPHA_4,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
