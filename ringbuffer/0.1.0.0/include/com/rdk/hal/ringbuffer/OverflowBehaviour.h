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
 * @brief What a ring buffer does when the producer outruns the consumer.
 *
 * There is no interface-wide default. Which behaviours a ring buffer offers, and whether the behaviour can be changed
 * at all, is a capability of the particular implementation, so the owning component selects the one it requires
 * through IRingBuffer::setOverflowBehaviour() and reads the value in effect through getInfo().
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class OverflowBehaviour : int32_t {
  // @aidl-doc
  /** Clean value when default initialized */
  UNDEFINED = 0,
  // @aidl-doc
  /**
   * The producer is able to write even when the ring buffer is full.
   *
   * This will result in data loss on the consumer side, but will not block the producer. Overflows are reported to
   * the producer through RingBufferErrorCode.OVERFLOW.
   */
  OVERFLOWING = 1,
  // @aidl-doc
  /**
   * The producer receives null from acquire() when the ring buffer is full, avoiding data loss.
   *
   * The producer can retry after IRingBufferSinkListener::onSpaceAvailable() or drop data at source.
   */
  NON_OVERFLOWING = 2,
};
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
[[nodiscard]] static inline std::string toString(OverflowBehaviour val) {
  switch(val) {
  case OverflowBehaviour::UNDEFINED:
    return "UNDEFINED";
  case OverflowBehaviour::OVERFLOWING:
    return "OVERFLOWING";
  case OverflowBehaviour::NON_OVERFLOWING:
    return "NON_OVERFLOWING";
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
constexpr inline std::array<::com::rdk::hal::ringbuffer::OverflowBehaviour, 3> enum_values<::com::rdk::hal::ringbuffer::OverflowBehaviour> = {
  ::com::rdk::hal::ringbuffer::OverflowBehaviour::UNDEFINED,
  ::com::rdk::hal::ringbuffer::OverflowBehaviour::OVERFLOWING,
  ::com::rdk::hal::ringbuffer::OverflowBehaviour::NON_OVERFLOWING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
