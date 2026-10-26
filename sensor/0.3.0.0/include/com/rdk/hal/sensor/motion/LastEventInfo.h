#pragma once
// @aidl-doc
/**
 * @file LastEventInfo.h
 * @brief Diagnostic snapshot of the most recent motion sensor event.
 *
 * Returned by {@link IMotionSensorController#getLastEventInfo()}.
 * Allows debug tools to determine what happened last and when, without
 * replaying the event stream.
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
class LastEventInfo : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief The event type (MOTION or NO_MOTION). */
  ::com::rdk::hal::sensor::motion::OperationalMode mode = ::com::rdk::hal::sensor::motion::OperationalMode(0);
  // @aidl-doc
  /**
   * @brief Monotonic timestamp in nanoseconds when the event occurred.
   *
   * Uses the same time base as CLOCK_MONOTONIC / System.nanoTime().
   * Elapsed time since the event is computed as (System.nanoTime() - timestampNs).
   */
  int64_t timestampNs = 0L;
  inline bool operator!=(const LastEventInfo& rhs) const {
    return std::tie(mode, timestampNs) != std::tie(rhs.mode, rhs.timestampNs);
  }
  inline bool operator<(const LastEventInfo& rhs) const {
    return std::tie(mode, timestampNs) < std::tie(rhs.mode, rhs.timestampNs);
  }
  inline bool operator<=(const LastEventInfo& rhs) const {
    return std::tie(mode, timestampNs) <= std::tie(rhs.mode, rhs.timestampNs);
  }
  inline bool operator==(const LastEventInfo& rhs) const {
    return std::tie(mode, timestampNs) == std::tie(rhs.mode, rhs.timestampNs);
  }
  inline bool operator>(const LastEventInfo& rhs) const {
    return std::tie(mode, timestampNs) > std::tie(rhs.mode, rhs.timestampNs);
  }
  inline bool operator>=(const LastEventInfo& rhs) const {
    return std::tie(mode, timestampNs) >= std::tie(rhs.mode, rhs.timestampNs);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.LastEventInfo");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "LastEventInfo{";
    os << "mode: " << ::android::internal::ToString(mode);
    os << ", timestampNs: " << ::android::internal::ToString(timestampNs);
    os << "}";
    return os.str();
  }
};  // class LastEventInfo
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
