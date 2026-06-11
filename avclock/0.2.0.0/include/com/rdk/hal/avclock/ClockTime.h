#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class ClockTime : public ::android::Parcelable {
public:
  int64_t clockTimeNs = 0L;
  int64_t sampleTimestampNs = 0L;
  inline bool operator!=(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) != std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator<(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) < std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator<=(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) <= std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator==(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) == std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator>(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) > std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator>=(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) >= std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.avclock.ClockTime");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ClockTime{";
    os << "clockTimeNs: " << ::android::internal::ToString(clockTimeNs);
    os << ", sampleTimestampNs: " << ::android::internal::ToString(sampleTimestampNs);
    os << "}";
    return os.str();
  }
};  // class ClockTime
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
