#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace common {
class TireStatus : public ::android::Parcelable {
public:
  float pressure = 0.000000f;
  bool isPunctured = false;
  inline bool operator!=(const TireStatus& rhs) const {
    return std::tie(pressure, isPunctured) != std::tie(rhs.pressure, rhs.isPunctured);
  }
  inline bool operator<(const TireStatus& rhs) const {
    return std::tie(pressure, isPunctured) < std::tie(rhs.pressure, rhs.isPunctured);
  }
  inline bool operator<=(const TireStatus& rhs) const {
    return std::tie(pressure, isPunctured) <= std::tie(rhs.pressure, rhs.isPunctured);
  }
  inline bool operator==(const TireStatus& rhs) const {
    return std::tie(pressure, isPunctured) == std::tie(rhs.pressure, rhs.isPunctured);
  }
  inline bool operator>(const TireStatus& rhs) const {
    return std::tie(pressure, isPunctured) > std::tie(rhs.pressure, rhs.isPunctured);
  }
  inline bool operator>=(const TireStatus& rhs) const {
    return std::tie(pressure, isPunctured) >= std::tie(rhs.pressure, rhs.isPunctured);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.common.TireStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "TireStatus{";
    os << "pressure: " << ::android::internal::ToString(pressure);
    os << ", isPunctured: " << ::android::internal::ToString(isPunctured);
    os << "}";
    return os.str();
  }
};  // class TireStatus
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
