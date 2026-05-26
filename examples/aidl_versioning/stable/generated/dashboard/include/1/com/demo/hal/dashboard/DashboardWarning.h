#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/common/WarningLevel.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace dashboard {
class DashboardWarning : public ::android::Parcelable {
public:
  ::android::String16 warningType;
  ::android::String16 description;
  ::com::demo::hal::common::WarningLevel warningLevel = ::com::demo::hal::common::WarningLevel(0);
  inline bool operator!=(const DashboardWarning& rhs) const {
    return std::tie(warningType, description, warningLevel) != std::tie(rhs.warningType, rhs.description, rhs.warningLevel);
  }
  inline bool operator<(const DashboardWarning& rhs) const {
    return std::tie(warningType, description, warningLevel) < std::tie(rhs.warningType, rhs.description, rhs.warningLevel);
  }
  inline bool operator<=(const DashboardWarning& rhs) const {
    return std::tie(warningType, description, warningLevel) <= std::tie(rhs.warningType, rhs.description, rhs.warningLevel);
  }
  inline bool operator==(const DashboardWarning& rhs) const {
    return std::tie(warningType, description, warningLevel) == std::tie(rhs.warningType, rhs.description, rhs.warningLevel);
  }
  inline bool operator>(const DashboardWarning& rhs) const {
    return std::tie(warningType, description, warningLevel) > std::tie(rhs.warningType, rhs.description, rhs.warningLevel);
  }
  inline bool operator>=(const DashboardWarning& rhs) const {
    return std::tie(warningType, description, warningLevel) >= std::tie(rhs.warningType, rhs.description, rhs.warningLevel);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.dashboard.DashboardWarning");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DashboardWarning{";
    os << "warningType: " << ::android::internal::ToString(warningType);
    os << ", description: " << ::android::internal::ToString(description);
    os << ", warningLevel: " << ::android::internal::ToString(warningLevel);
    os << "}";
    return os.str();
  }
};  // class DashboardWarning
}  // namespace dashboard
}  // namespace hal
}  // namespace demo
}  // namespace com
