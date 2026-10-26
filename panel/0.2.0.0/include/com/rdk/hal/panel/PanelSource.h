#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 * @brief Panel AV source identifier.
 *
 * `type` identifies the source family, for example HDMI, COMPOSITE, DTV, IP,
 * AUTO, or UNKNOWN. `instance` optionally identifies a concrete source within
 * that family, for example 1 or 2 for HDMI inputs.
 */
class PanelSource : public ::android::Parcelable {
public:
  ::android::String16 type;
  ::std::optional<::android::String16> instance;
  inline bool operator!=(const PanelSource& rhs) const {
    return std::tie(type, instance) != std::tie(rhs.type, rhs.instance);
  }
  inline bool operator<(const PanelSource& rhs) const {
    return std::tie(type, instance) < std::tie(rhs.type, rhs.instance);
  }
  inline bool operator<=(const PanelSource& rhs) const {
    return std::tie(type, instance) <= std::tie(rhs.type, rhs.instance);
  }
  inline bool operator==(const PanelSource& rhs) const {
    return std::tie(type, instance) == std::tie(rhs.type, rhs.instance);
  }
  inline bool operator>(const PanelSource& rhs) const {
    return std::tie(type, instance) > std::tie(rhs.type, rhs.instance);
  }
  inline bool operator>=(const PanelSource& rhs) const {
    return std::tie(type, instance) >= std::tie(rhs.type, rhs.instance);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PanelSource");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PanelSource{";
    os << "type: " << ::android::internal::ToString(type);
    os << ", instance: " << ::android::internal::ToString(instance);
    os << "}";
    return os.str();
  }
};  // class PanelSource
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
