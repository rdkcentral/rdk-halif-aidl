#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
// @aidl-doc
/**
 * @brief Error codes for IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class RingBufferErrorCode : int32_t {
  // @aidl-doc
  /** Clean value when default initialized */
  UNDEFINED = 0,
  // @aidl-doc
  /**
   * Overflow.
   *
   * Only relevant for ring buffers set to OverflowBehaviour.OVERFLOWING. Will be issued when the producer acquires a
   * buffer which will include the current reading position, i.e. the offset of the "oldest" acquire result not yet
   * released by the consumer or the offset that would be given to the next acquire call if the consumer currently
   * holds no buffer.
   *
   * Delivered asynchronously through the oneway onError callback. Delivery may be triggered by the implementation
   * while it is handling an acquire call, so the callback can run on another thread while the producer's own acquire
   * call is still in progress. The producer must therefore not take a lock in the callback that it also holds across
   * acquire.
   */
  OVERFLOW = 1,
  // @aidl-doc
  /**
   * The producer side has vanished unexpectedly, e.g. due to a crash or being killed by the system.
   *
   * Detected by the implementation through a death recipient on the producer's listener. Any acquire result the
   * producer still held is discarded, since it was never released and so was never committed, and the producer slot
   * returns to its unregistered state so that a replacement can register.
   */
  PRODUCER_DISCONNECTED = 2,
  // @aidl-doc
  /**
   * The consumer side has vanished unexpectedly, e.g. due to a crash or being killed by the system.
   *
   * Detected by the implementation through a death recipient on the consumer's listener. Any acquire results the
   * consumer still held are released, returning that space to the producer, and the consumer slot returns to its
   * unregistered state so that a replacement can register.
   */
  CONSUMER_DISCONNECTED = 3,
  // @aidl-doc
  /** Implementation-specific error (the message parameter of the callback should contain more details) */
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
