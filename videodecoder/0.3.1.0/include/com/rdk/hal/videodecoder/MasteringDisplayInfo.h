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
// @aidl-doc
/**
 *  @brief     Mastering display colour volume metadata (SMPTE ST 2086).
 *
 *  Field layout and scaling factors match HEVC SEI message type 137
 *  (mastering_display_colour_volume) and CTA-861.3 Static Metadata
 *  Descriptor Type 1, ensuring direct compatibility with both standards.
 *
 *  @author    Gerald Weatherup
 */
class MasteringDisplayInfo : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the green display primary, x-axis.
   * Scaled by 50000. Range: 0-50000.
   * e.g. BT.2020 green x = 0.17 -> 8500
   */
  int32_t greenPrimaryX = 0;
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the green display primary, y-axis.
   * Scaled by 50000. Range: 0-50000.
   */
  int32_t greenPrimaryY = 0;
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the blue display primary, x-axis.
   * Scaled by 50000. Range: 0-50000.
   */
  int32_t bluePrimaryX = 0;
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the blue display primary, y-axis.
   * Scaled by 50000. Range: 0-50000.
   */
  int32_t bluePrimaryY = 0;
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the red display primary, x-axis.
   * Scaled by 50000. Range: 0-50000.
   */
  int32_t redPrimaryX = 0;
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the red display primary, y-axis.
   * Scaled by 50000. Range: 0-50000.
   */
  int32_t redPrimaryY = 0;
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the white point, x-axis.
   * Scaled by 50000. Range: 0-50000.
   * e.g. D65 white point x = 0.3127 -> 15635
   */
  int32_t whitePointX = 0;
  // @aidl-doc
  /**
   * CIE 1931 chromaticity coordinate for the white point, y-axis.
   * Scaled by 50000. Range: 0-50000.
   * e.g. D65 white point y = 0.3290 -> 16450
   */
  int32_t whitePointY = 0;
  // @aidl-doc
  /**
   * Maximum display mastering luminance in units of 0.0001 cd/m^2.
   * Range: 1-10,000,000 (0.0001-1000 cd/m^2).
   * e.g. 1000 nits peak -> 10,000,000
   * @see HEVC SEI type 137, max_display_mastering_luminance
   */
  int32_t maxLuminance = 0;
  // @aidl-doc
  /**
   * Minimum display mastering luminance in units of 0.0001 cd/m^2.
   * Range: 0-50,000 (0-5 cd/m^2).
   * e.g. 0.05 nits black level -> 500
   * @see HEVC SEI type 137, min_display_mastering_luminance
   */
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
