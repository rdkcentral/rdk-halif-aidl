#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace dashboard {
class DashboardInfo : public ::android::Parcelable {
public:
  ::android::String16 displayMessage;
  bool warningActive = false;
  inline bool operator!=(const DashboardInfo& rhs) const {
    return std::tie(displayMessage, warningActive) != std::tie(rhs.displayMessage, rhs.warningActive);
  }
  inline bool operator<(const DashboardInfo& rhs) const {
    return std::tie(displayMessage, warningActive) < std::tie(rhs.displayMessage, rhs.warningActive);
  }
  inline bool operator<=(const DashboardInfo& rhs) const {
    return std::tie(displayMessage, warningActive) <= std::tie(rhs.displayMessage, rhs.warningActive);
  }
  inline bool operator==(const DashboardInfo& rhs) const {
    return std::tie(displayMessage, warningActive) == std::tie(rhs.displayMessage, rhs.warningActive);
  }
  inline bool operator>(const DashboardInfo& rhs) const {
    return std::tie(displayMessage, warningActive) > std::tie(rhs.displayMessage, rhs.warningActive);
  }
  inline bool operator>=(const DashboardInfo& rhs) const {
    return std::tie(displayMessage, warningActive) >= std::tie(rhs.displayMessage, rhs.warningActive);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.dashboard.DashboardInfo");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DashboardInfo{";
    os << "displayMessage: " << ::android::internal::ToString(displayMessage);
    os << ", warningActive: " << ::android::internal::ToString(warningActive);
    os << "}";
    return os.str();
  }
};  // class DashboardInfo
}  // namespace dashboard
}  // namespace hal
}  // namespace demo
}  // namespace com
