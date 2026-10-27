#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/DimmingLevel.h>
#include <com/rdk/hal/panel/DimmingMode.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/** @brief Grouped dimming settings. */
class DimmingSettings : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The dimming mode. */
  ::com::rdk::hal::panel::DimmingMode mode = ::com::rdk::hal::panel::DimmingMode(0);
  // @aidl-doc
  /** The dimming level, one of the levels supported for the mode. */
  ::com::rdk::hal::panel::DimmingLevel level = ::com::rdk::hal::panel::DimmingLevel(0);
  inline bool operator!=(const DimmingSettings& rhs) const {
    return std::tie(mode, level) != std::tie(rhs.mode, rhs.level);
  }
  inline bool operator<(const DimmingSettings& rhs) const {
    return std::tie(mode, level) < std::tie(rhs.mode, rhs.level);
  }
  inline bool operator<=(const DimmingSettings& rhs) const {
    return std::tie(mode, level) <= std::tie(rhs.mode, rhs.level);
  }
  inline bool operator==(const DimmingSettings& rhs) const {
    return std::tie(mode, level) == std::tie(rhs.mode, rhs.level);
  }
  inline bool operator>(const DimmingSettings& rhs) const {
    return std::tie(mode, level) > std::tie(rhs.mode, rhs.level);
  }
  inline bool operator>=(const DimmingSettings& rhs) const {
    return std::tie(mode, level) >= std::tie(rhs.mode, rhs.level);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.DimmingSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DimmingSettings{";
    os << "mode: " << ::android::internal::ToString(mode);
    os << ", level: " << ::android::internal::ToString(level);
    os << "}";
    return os.str();
  }
};  // class DimmingSettings
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
