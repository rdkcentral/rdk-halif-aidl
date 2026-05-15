#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/DrmMetric.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class DrmMetricGroup : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::drm::DrmMetric> metrics;
  inline bool operator!=(const DrmMetricGroup& rhs) const {
    return std::tie(metrics) != std::tie(rhs.metrics);
  }
  inline bool operator<(const DrmMetricGroup& rhs) const {
    return std::tie(metrics) < std::tie(rhs.metrics);
  }
  inline bool operator<=(const DrmMetricGroup& rhs) const {
    return std::tie(metrics) <= std::tie(rhs.metrics);
  }
  inline bool operator==(const DrmMetricGroup& rhs) const {
    return std::tie(metrics) == std::tie(rhs.metrics);
  }
  inline bool operator>(const DrmMetricGroup& rhs) const {
    return std::tie(metrics) > std::tie(rhs.metrics);
  }
  inline bool operator>=(const DrmMetricGroup& rhs) const {
    return std::tie(metrics) >= std::tie(rhs.metrics);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.DrmMetricGroup");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DrmMetricGroup{";
    os << "metrics: " << ::android::internal::ToString(metrics);
    os << "}";
    return os.str();
  }
};  // class DrmMetricGroup
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
