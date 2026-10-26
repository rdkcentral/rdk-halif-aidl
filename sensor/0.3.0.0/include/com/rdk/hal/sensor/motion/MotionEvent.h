#pragma once
// @aidl-doc
/**
 * @file MotionEvent.h
 * @brief Event payload delivered to motion sensor event listeners.
 */

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/OperationalMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
// @aidl-doc
/**
 * @brief Event payload delivered to motion sensor event listeners.
 *
 * @details
 * Provides context for a motion-state change event:
 *  - The active operational mode whose condition was met
 *  - A monotonic timestamp for event ordering and correlation with
 *    other system events (thermal, deep sleep, etc.)
 *
 * Mirrors the shape of `ActionEvent` on the thermal sensor side so
 * downstream listeners that consume both sensors get a consistent
 * payload contract.
 */
class MotionEvent : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief The active mode whose condition was met (MOTION or NO_MOTION). */
  ::com::rdk::hal::sensor::motion::OperationalMode mode = ::com::rdk::hal::sensor::motion::OperationalMode(0);
  // @aidl-doc
  /**
   * @brief Monotonic timestamp (ms) when the event occurred.
   * @details Use monotonic time for event ordering; not wall-clock time.
   *          Sourced from `CLOCK_MONOTONIC` (or equivalent) at the
   *          point the vendor layer detects the state change.
   */
  int64_t timestampMonotonicMs = 0L;
  inline bool operator!=(const MotionEvent& rhs) const {
    return std::tie(mode, timestampMonotonicMs) != std::tie(rhs.mode, rhs.timestampMonotonicMs);
  }
  inline bool operator<(const MotionEvent& rhs) const {
    return std::tie(mode, timestampMonotonicMs) < std::tie(rhs.mode, rhs.timestampMonotonicMs);
  }
  inline bool operator<=(const MotionEvent& rhs) const {
    return std::tie(mode, timestampMonotonicMs) <= std::tie(rhs.mode, rhs.timestampMonotonicMs);
  }
  inline bool operator==(const MotionEvent& rhs) const {
    return std::tie(mode, timestampMonotonicMs) == std::tie(rhs.mode, rhs.timestampMonotonicMs);
  }
  inline bool operator>(const MotionEvent& rhs) const {
    return std::tie(mode, timestampMonotonicMs) > std::tie(rhs.mode, rhs.timestampMonotonicMs);
  }
  inline bool operator>=(const MotionEvent& rhs) const {
    return std::tie(mode, timestampMonotonicMs) >= std::tie(rhs.mode, rhs.timestampMonotonicMs);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.MotionEvent");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "MotionEvent{";
    os << "mode: " << ::android::internal::ToString(mode);
    os << ", timestampMonotonicMs: " << ::android::internal::ToString(timestampMonotonicMs);
    os << "}";
    return os.str();
  }
};  // class MotionEvent
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
