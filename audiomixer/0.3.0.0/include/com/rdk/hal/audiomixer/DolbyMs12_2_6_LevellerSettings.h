#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_LevellerMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class DolbyMs12_2_6_LevellerSettings : public ::android::Parcelable {
public:
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode mode = ::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode(0);
  int32_t level = 0;
  inline bool operator!=(const DolbyMs12_2_6_LevellerSettings& rhs) const {
    return std::tie(mode, level) != std::tie(rhs.mode, rhs.level);
  }
  inline bool operator<(const DolbyMs12_2_6_LevellerSettings& rhs) const {
    return std::tie(mode, level) < std::tie(rhs.mode, rhs.level);
  }
  inline bool operator<=(const DolbyMs12_2_6_LevellerSettings& rhs) const {
    return std::tie(mode, level) <= std::tie(rhs.mode, rhs.level);
  }
  inline bool operator==(const DolbyMs12_2_6_LevellerSettings& rhs) const {
    return std::tie(mode, level) == std::tie(rhs.mode, rhs.level);
  }
  inline bool operator>(const DolbyMs12_2_6_LevellerSettings& rhs) const {
    return std::tie(mode, level) > std::tie(rhs.mode, rhs.level);
  }
  inline bool operator>=(const DolbyMs12_2_6_LevellerSettings& rhs) const {
    return std::tie(mode, level) >= std::tie(rhs.mode, rhs.level);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.DolbyMs12_2_6_LevellerSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DolbyMs12_2_6_LevellerSettings{";
    os << "mode: " << ::android::internal::ToString(mode);
    os << ", level: " << ::android::internal::ToString(level);
    os << "}";
    return os.str();
  }
};  // class DolbyMs12_2_6_LevellerSettings
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
