#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
// @aidl-doc
/**
 *  @brief     Lifecycle state of an audiosink resource instance.
 *
 *  Per-module State enum (sub-task B of #24) — replaces the shared
 *  `common.State` so this module's generation no longer pins itself to
 *  common's evolution.
 *
 *  The shape mirrors the prior `common.State` 9-value union as the
 *  initial migration; trimming the per-module enum to only the
 *  transitions audiosink actually has is a follow-up the module's owners
 *  may pursue independently without forcing a generation bump on every
 *  other consumer.
 *
 *  @author    Gerald Weatherup
 */
enum class State : int32_t {
  // @aidl-doc
  /** Initial / unknown state. */
  UNKNOWN = 0,
  // @aidl-doc
  /** Resource is closed; no open() call has succeeded yet. */
  CLOSED = 1,
  // @aidl-doc
  /** Resource is in the process of opening. */
  OPENING = 2,
  // @aidl-doc
  /** Resource is open and ready to be configured / started. */
  READY = 3,
  // @aidl-doc
  /** Resource is transitioning from READY to STARTED. */
  STARTING = 4,
  // @aidl-doc
  /** Resource is actively running. */
  STARTED = 5,
  // @aidl-doc
  /** Resource is flushing buffered data. */
  FLUSHING = 6,
  // @aidl-doc
  /** Resource is transitioning from STARTED back to READY. */
  STOPPING = 7,
  // @aidl-doc
  /** Resource is transitioning to CLOSED. */
  CLOSING = 8,
};
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
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
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiosink::State, 9> enum_values<::com::rdk::hal::audiosink::State> = {
  ::com::rdk::hal::audiosink::State::UNKNOWN,
  ::com::rdk::hal::audiosink::State::CLOSED,
  ::com::rdk::hal::audiosink::State::OPENING,
  ::com::rdk::hal::audiosink::State::READY,
  ::com::rdk::hal::audiosink::State::STARTING,
  ::com::rdk::hal::audiosink::State::STARTED,
  ::com::rdk::hal::audiosink::State::FLUSHING,
  ::com::rdk::hal::audiosink::State::STOPPING,
  ::com::rdk::hal::audiosink::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
