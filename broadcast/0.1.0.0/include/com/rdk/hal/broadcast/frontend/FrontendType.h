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
enum class FrontendType : int32_t {
  UNDEFINED = 0,
  ATSC = 1,
  DVB_C = 2,
  DVB_S = 3,
  DVB_T = 4,
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
[[nodiscard]] static inline std::string toString(FrontendType val) {
  switch(val) {
  case FrontendType::UNDEFINED:
    return "UNDEFINED";
  case FrontendType::ATSC:
    return "ATSC";
  case FrontendType::DVB_C:
    return "DVB_C";
  case FrontendType::DVB_S:
    return "DVB_S";
  case FrontendType::DVB_T:
    return "DVB_T";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::FrontendType, 5> enum_values<::com::rdk::hal::broadcast::frontend::FrontendType> = {
  ::com::rdk::hal::broadcast::frontend::FrontendType::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::FrontendType::ATSC,
  ::com::rdk::hal::broadcast::frontend::FrontendType::DVB_C,
  ::com::rdk::hal::broadcast::frontend::FrontendType::DVB_S,
  ::com::rdk::hal::broadcast::frontend::FrontendType::DVB_T,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
