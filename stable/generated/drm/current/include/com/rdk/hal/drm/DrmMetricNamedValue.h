#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/DrmMetricValue.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class DrmMetricNamedValue : public ::android::Parcelable {
public:
  ::android::String16 name;
  ::com::rdk::hal::drm::DrmMetricValue value;
  inline bool operator!=(const DrmMetricNamedValue& rhs) const {
    return std::tie(name, value) != std::tie(rhs.name, rhs.value);
  }
  inline bool operator<(const DrmMetricNamedValue& rhs) const {
    return std::tie(name, value) < std::tie(rhs.name, rhs.value);
  }
  inline bool operator<=(const DrmMetricNamedValue& rhs) const {
    return std::tie(name, value) <= std::tie(rhs.name, rhs.value);
  }
  inline bool operator==(const DrmMetricNamedValue& rhs) const {
    return std::tie(name, value) == std::tie(rhs.name, rhs.value);
  }
  inline bool operator>(const DrmMetricNamedValue& rhs) const {
    return std::tie(name, value) > std::tie(rhs.name, rhs.value);
  }
  inline bool operator>=(const DrmMetricNamedValue& rhs) const {
    return std::tie(name, value) >= std::tie(rhs.name, rhs.value);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.DrmMetricNamedValue");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DrmMetricNamedValue{";
    os << "name: " << ::android::internal::ToString(name);
    os << ", value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class DrmMetricNamedValue
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
