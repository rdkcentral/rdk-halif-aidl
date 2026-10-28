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
// @aidl-doc
/**
 * This message contains plugin-specific metrics made available to the client.
 * The message is used for making vendor-specific metrics available to an
 * application. The framework is not consuming any of the information.
 *
 * Metrics are grouped in instances of DrmMetricGroup. Each group contains
 * multiple instances of Metric.
 *
 * Example:
 *
 * Capture the timing information of a buffer copy event, "buf_copy", broken
 * out by the "size" of the buffer.
 *
 * DrmMetricGroup {
 *   metrics[0] {
 *     name: "buf_copy"
 *     attributes[0] {
 *       name: "size"
 *       type: INT64_TYPE
 *       int64Value: 1024
 *     }
 *     values[0] {
 *       componentName: "operation_count"
 *       type: INT64_TYPE
 *       int64Value: 75
 *     }
 *     values[1] {
 *       component_name: "average_time_seconds"
 *       type: DOUBLE_TYPE
 *       doubleValue: 0.00000042
 *     }
 *   }
 * }
 */
class DrmMetricGroup : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The list of metrics to be captured. */
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
