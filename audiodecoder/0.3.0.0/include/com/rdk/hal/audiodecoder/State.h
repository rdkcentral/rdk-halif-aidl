#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 * @brief     Audio Decoder States
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 */
enum class State : int32_t {
  // @aidl-doc
  /** The audio decoder HAL is in an unknown or uninitialized state. */
  UNKNOWN = 0,
  // @aidl-doc
  /** The service connection is established but decoder not yet configured. */
  CLOSED = 1,
  // @aidl-doc
  /** Decoder is loading resources and initializing internal structures. */
  OPENING = 2,
  // @aidl-doc
  /** Decoder is configured and ready to start decoding but idle. */
  READY = 3,
  // @aidl-doc
  /** Decoder is transitioning from READY to DECODING; priming buffers. */
  STARTING = 4,
  // @aidl-doc
  /** Decoder is actively decoding audio frames. */
  STARTED = 5,
  // @aidl-doc
  /** Decoder is flushing pending input/output buffers; after flushing, returns to DECODING or READY. */
  FLUSHING = 6,
  // @aidl-doc
  /** Decoder is stopping and flushing; will revert to READY after complete. */
  STOPPING = 7,
  // @aidl-doc
  /** Decoder is releasing resources and transitioning to CLOSED. */
  CLOSING = 8,
};
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(State val) {
  switch(val) {
  case State::UNKNOWN:
    return "UNKNOWN";
  case State::CLOSED:
    return "CLOSED";
  case State::OPENING:
    return "OPENING";
  case State::READY:
    return "READY";
  case State::STARTING:
    return "STARTING";
  case State::STARTED:
    return "STARTED";
  case State::FLUSHING:
    return "FLUSHING";
  case State::STOPPING:
    return "STOPPING";
  case State::CLOSING:
    return "CLOSING";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiodecoder::State, 9> enum_values<::com::rdk::hal::audiodecoder::State> = {
  ::com::rdk::hal::audiodecoder::State::UNKNOWN,
  ::com::rdk::hal::audiodecoder::State::CLOSED,
  ::com::rdk::hal::audiodecoder::State::OPENING,
  ::com::rdk::hal::audiodecoder::State::READY,
  ::com::rdk::hal::audiodecoder::State::STARTING,
  ::com::rdk::hal::audiodecoder::State::STARTED,
  ::com::rdk::hal::audiodecoder::State::FLUSHING,
  ::com::rdk::hal::audiodecoder::State::STOPPING,
  ::com::rdk::hal::audiodecoder::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
