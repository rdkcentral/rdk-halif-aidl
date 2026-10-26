#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/ToneMappingLevel.h>
#include <com/rdk/hal/panel/ToneMappingMode.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/** @brief Grouped HDR tone-mapping settings. */
class ToneMappingSettings : public ::android::Parcelable {
public:
  ::com::rdk::hal::panel::ToneMappingMode mode = ::com::rdk::hal::panel::ToneMappingMode(0);
  ::com::rdk::hal::panel::ToneMappingLevel level = ::com::rdk::hal::panel::ToneMappingLevel(0);
  inline bool operator!=(const ToneMappingSettings& rhs) const {
    return std::tie(mode, level) != std::tie(rhs.mode, rhs.level);
  }
  inline bool operator<(const ToneMappingSettings& rhs) const {
    return std::tie(mode, level) < std::tie(rhs.mode, rhs.level);
  }
  inline bool operator<=(const ToneMappingSettings& rhs) const {
    return std::tie(mode, level) <= std::tie(rhs.mode, rhs.level);
  }
  inline bool operator==(const ToneMappingSettings& rhs) const {
    return std::tie(mode, level) == std::tie(rhs.mode, rhs.level);
  }
  inline bool operator>(const ToneMappingSettings& rhs) const {
    return std::tie(mode, level) > std::tie(rhs.mode, rhs.level);
  }
  inline bool operator>=(const ToneMappingSettings& rhs) const {
    return std::tie(mode, level) >= std::tie(rhs.mode, rhs.level);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.ToneMappingSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ToneMappingSettings{";
    os << "mode: " << ::android::internal::ToString(mode);
    os << ", level: " << ::android::internal::ToString(level);
    os << "}";
    return os.str();
  }
};  // class ToneMappingSettings
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
