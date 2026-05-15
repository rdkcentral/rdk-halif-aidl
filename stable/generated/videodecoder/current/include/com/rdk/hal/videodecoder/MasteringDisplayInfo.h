#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class MasteringDisplayInfo : public ::android::Parcelable {
public:
  int32_t greenPrimaryX = 0;
  int32_t greenPrimaryY = 0;
  int32_t bluePrimaryX = 0;
  int32_t bluePrimaryY = 0;
  int32_t redPrimaryX = 0;
  int32_t redPrimaryY = 0;
  int32_t whitePointX = 0;
  int32_t whitePointY = 0;
  int32_t maxLuminance = 0;
  int32_t minLuminance = 0;
  inline bool operator!=(const MasteringDisplayInfo& rhs) const {
    return std::tie(greenPrimaryX, greenPrimaryY, bluePrimaryX, bluePrimaryY, redPrimaryX, redPrimaryY, whitePointX, whitePointY, maxLuminance, minLuminance) != std::tie(rhs.greenPrimaryX, rhs.greenPrimaryY, rhs.bluePrimaryX, rhs.bluePrimaryY, rhs.redPrimaryX, rhs.redPrimaryY, rhs.whitePointX, rhs.whitePointY, rhs.maxLuminance, rhs.minLuminance);
  }
  inline bool operator<(const MasteringDisplayInfo& rhs) const {
    return std::tie(greenPrimaryX, greenPrimaryY, bluePrimaryX, bluePrimaryY, redPrimaryX, redPrimaryY, whitePointX, whitePointY, maxLuminance, minLuminance) < std::tie(rhs.greenPrimaryX, rhs.greenPrimaryY, rhs.bluePrimaryX, rhs.bluePrimaryY, rhs.redPrimaryX, rhs.redPrimaryY, rhs.whitePointX, rhs.whitePointY, rhs.maxLuminance, rhs.minLuminance);
  }
  inline bool operator<=(const MasteringDisplayInfo& rhs) const {
    return std::tie(greenPrimaryX, greenPrimaryY, bluePrimaryX, bluePrimaryY, redPrimaryX, redPrimaryY, whitePointX, whitePointY, maxLuminance, minLuminance) <= std::tie(rhs.greenPrimaryX, rhs.greenPrimaryY, rhs.bluePrimaryX, rhs.bluePrimaryY, rhs.redPrimaryX, rhs.redPrimaryY, rhs.whitePointX, rhs.whitePointY, rhs.maxLuminance, rhs.minLuminance);
  }
  inline bool operator==(const MasteringDisplayInfo& rhs) const {
    return std::tie(greenPrimaryX, greenPrimaryY, bluePrimaryX, bluePrimaryY, redPrimaryX, redPrimaryY, whitePointX, whitePointY, maxLuminance, minLuminance) == std::tie(rhs.greenPrimaryX, rhs.greenPrimaryY, rhs.bluePrimaryX, rhs.bluePrimaryY, rhs.redPrimaryX, rhs.redPrimaryY, rhs.whitePointX, rhs.whitePointY, rhs.maxLuminance, rhs.minLuminance);
  }
  inline bool operator>(const MasteringDisplayInfo& rhs) const {
    return std::tie(greenPrimaryX, greenPrimaryY, bluePrimaryX, bluePrimaryY, redPrimaryX, redPrimaryY, whitePointX, whitePointY, maxLuminance, minLuminance) > std::tie(rhs.greenPrimaryX, rhs.greenPrimaryY, rhs.bluePrimaryX, rhs.bluePrimaryY, rhs.redPrimaryX, rhs.redPrimaryY, rhs.whitePointX, rhs.whitePointY, rhs.maxLuminance, rhs.minLuminance);
  }
  inline bool operator>=(const MasteringDisplayInfo& rhs) const {
    return std::tie(greenPrimaryX, greenPrimaryY, bluePrimaryX, bluePrimaryY, redPrimaryX, redPrimaryY, whitePointX, whitePointY, maxLuminance, minLuminance) >= std::tie(rhs.greenPrimaryX, rhs.greenPrimaryY, rhs.bluePrimaryX, rhs.bluePrimaryY, rhs.redPrimaryX, rhs.redPrimaryY, rhs.whitePointX, rhs.whitePointY, rhs.maxLuminance, rhs.minLuminance);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.MasteringDisplayInfo");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "MasteringDisplayInfo{";
    os << "greenPrimaryX: " << ::android::internal::ToString(greenPrimaryX);
    os << ", greenPrimaryY: " << ::android::internal::ToString(greenPrimaryY);
    os << ", bluePrimaryX: " << ::android::internal::ToString(bluePrimaryX);
    os << ", bluePrimaryY: " << ::android::internal::ToString(bluePrimaryY);
    os << ", redPrimaryX: " << ::android::internal::ToString(redPrimaryX);
    os << ", redPrimaryY: " << ::android::internal::ToString(redPrimaryY);
    os << ", whitePointX: " << ::android::internal::ToString(whitePointX);
    os << ", whitePointY: " << ::android::internal::ToString(whitePointY);
    os << ", maxLuminance: " << ::android::internal::ToString(maxLuminance);
    os << ", minLuminance: " << ::android::internal::ToString(minLuminance);
    os << "}";
    return os.str();
  }
};  // class MasteringDisplayInfo
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
