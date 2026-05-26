#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/DrmMetricNamedValue.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class DrmMetric : public ::android::Parcelable {
public:
  ::android::String16 name;
  ::std::vector<::com::rdk::hal::drm::DrmMetricNamedValue> attributes;
  ::std::vector<::com::rdk::hal::drm::DrmMetricNamedValue> values;
  inline bool operator!=(const DrmMetric& rhs) const {
    return std::tie(name, attributes, values) != std::tie(rhs.name, rhs.attributes, rhs.values);
  }
  inline bool operator<(const DrmMetric& rhs) const {
    return std::tie(name, attributes, values) < std::tie(rhs.name, rhs.attributes, rhs.values);
  }
  inline bool operator<=(const DrmMetric& rhs) const {
    return std::tie(name, attributes, values) <= std::tie(rhs.name, rhs.attributes, rhs.values);
  }
  inline bool operator==(const DrmMetric& rhs) const {
    return std::tie(name, attributes, values) == std::tie(rhs.name, rhs.attributes, rhs.values);
  }
  inline bool operator>(const DrmMetric& rhs) const {
    return std::tie(name, attributes, values) > std::tie(rhs.name, rhs.attributes, rhs.values);
  }
  inline bool operator>=(const DrmMetric& rhs) const {
    return std::tie(name, attributes, values) >= std::tie(rhs.name, rhs.attributes, rhs.values);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.DrmMetric");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DrmMetric{";
    os << "name: " << ::android::internal::ToString(name);
    os << ", attributes: " << ::android::internal::ToString(attributes);
    os << ", values: " << ::android::internal::ToString(values);
    os << "}";
    return os.str();
  }
};  // class DrmMetric
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
