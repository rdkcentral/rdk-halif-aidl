#pragma once

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
class MotionEvent : public ::android::Parcelable {
public:
  ::com::rdk::hal::sensor::motion::OperationalMode mode = ::com::rdk::hal::sensor::motion::OperationalMode(0);
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
