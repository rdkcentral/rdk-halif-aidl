#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
enum class MemoryType : int32_t {
  UNKNOWN = 0,
  DMABuf = 1,
  NativeHandle = 2,
};
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videosink {
[[nodiscard]] static inline std::string toString(MemoryType val) {
  switch(val) {
  case MemoryType::UNKNOWN:
    return "UNKNOWN";
  case MemoryType::DMABuf:
    return "DMABuf";
  case MemoryType::NativeHandle:
    return "NativeHandle";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videosink::MemoryType, 3> enum_values<::com::rdk::hal::videosink::MemoryType> = {
  ::com::rdk::hal::videosink::MemoryType::UNKNOWN,
  ::com::rdk::hal::videosink::MemoryType::DMABuf,
  ::com::rdk::hal::videosink::MemoryType::NativeHandle,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
