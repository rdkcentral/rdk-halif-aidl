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
namespace drm {
class NumberOfSessions : public ::android::Parcelable {
public:
  int32_t currentSessions = 0;
  int32_t maxSessions = 0;
  inline bool operator!=(const NumberOfSessions& rhs) const {
    return std::tie(currentSessions, maxSessions) != std::tie(rhs.currentSessions, rhs.maxSessions);
  }
  inline bool operator<(const NumberOfSessions& rhs) const {
    return std::tie(currentSessions, maxSessions) < std::tie(rhs.currentSessions, rhs.maxSessions);
  }
  inline bool operator<=(const NumberOfSessions& rhs) const {
    return std::tie(currentSessions, maxSessions) <= std::tie(rhs.currentSessions, rhs.maxSessions);
  }
  inline bool operator==(const NumberOfSessions& rhs) const {
    return std::tie(currentSessions, maxSessions) == std::tie(rhs.currentSessions, rhs.maxSessions);
  }
  inline bool operator>(const NumberOfSessions& rhs) const {
    return std::tie(currentSessions, maxSessions) > std::tie(rhs.currentSessions, rhs.maxSessions);
  }
  inline bool operator>=(const NumberOfSessions& rhs) const {
    return std::tie(currentSessions, maxSessions) >= std::tie(rhs.currentSessions, rhs.maxSessions);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.NumberOfSessions");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "NumberOfSessions{";
    os << "currentSessions: " << ::android::internal::ToString(currentSessions);
    os << ", maxSessions: " << ::android::internal::ToString(maxSessions);
    os << "}";
    return os.str();
  }
};  // class NumberOfSessions
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
