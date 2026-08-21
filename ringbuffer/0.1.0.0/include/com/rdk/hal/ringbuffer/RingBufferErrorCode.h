#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
enum class RingBufferErrorCode : int32_t {
  UNDEFINED = 0,
  OVERFLOW = 1,
  PRODUCER_DISCONNECTED = 2,
  CONSUMER_DISCONNECTED = 3,
  IMPLEMENTATION_ERROR = 4,
};
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
[[nodiscard]] static inline std::string toString(RingBufferErrorCode val) {
  switch(val) {
  case RingBufferErrorCode::UNDEFINED:
    return "UNDEFINED";
  case RingBufferErrorCode::OVERFLOW:
    return "OVERFLOW";
  case RingBufferErrorCode::PRODUCER_DISCONNECTED:
    return "PRODUCER_DISCONNECTED";
  case RingBufferErrorCode::CONSUMER_DISCONNECTED:
    return "CONSUMER_DISCONNECTED";
  case RingBufferErrorCode::IMPLEMENTATION_ERROR:
    return "IMPLEMENTATION_ERROR";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::ringbuffer::RingBufferErrorCode, 5> enum_values<::com::rdk::hal::ringbuffer::RingBufferErrorCode> = {
  ::com::rdk::hal::ringbuffer::RingBufferErrorCode::UNDEFINED,
  ::com::rdk::hal::ringbuffer::RingBufferErrorCode::OVERFLOW,
  ::com::rdk::hal::ringbuffer::RingBufferErrorCode::PRODUCER_DISCONNECTED,
  ::com::rdk::hal::ringbuffer::RingBufferErrorCode::CONSUMER_DISCONNECTED,
  ::com::rdk::hal::ringbuffer::RingBufferErrorCode::IMPLEMENTATION_ERROR,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
