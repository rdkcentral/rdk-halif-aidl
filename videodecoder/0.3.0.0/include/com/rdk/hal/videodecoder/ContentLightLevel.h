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
 *  @brief     Content light level metadata (SMPTE ST 2094-10 / CTA-861.3).
 *
 *  Carried in HEVC SEI message type 144 (content_light_level_info).
 *  Both fields are integer cd/m^2 (nits) in the range 0-65535.
 *  A value of 0 indicates the field is not present or unknown.
 *
 *  @author    Gerald Weatherup
 */
class ContentLightLevel : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Maximum Content Light Level (MaxCLL).
   * The peak luminance of any single pixel across the entire content,
   * in integer cd/m^2 (nits). Range: 0-65535. 0 = not present.
   * @see HEVC SEI type 144, max_content_light_level
   */
  int32_t maxCLL = 0;
  // @aidl-doc
  /**
   * Maximum Frame-Average Light Level (MaxFALL).
   * The maximum average luminance of any single frame across the entire
   * content, in integer cd/m^2 (nits). Range: 0-65535. 0 = not present.
   * @see HEVC SEI type 144, max_pic_average_light_level
   */
  int32_t maxFALL = 0;
  inline bool operator!=(const ContentLightLevel& rhs) const {
    return std::tie(maxCLL, maxFALL) != std::tie(rhs.maxCLL, rhs.maxFALL);
  }
  inline bool operator<(const ContentLightLevel& rhs) const {
    return std::tie(maxCLL, maxFALL) < std::tie(rhs.maxCLL, rhs.maxFALL);
  }
  inline bool operator<=(const ContentLightLevel& rhs) const {
    return std::tie(maxCLL, maxFALL) <= std::tie(rhs.maxCLL, rhs.maxFALL);
  }
  inline bool operator==(const ContentLightLevel& rhs) const {
    return std::tie(maxCLL, maxFALL) == std::tie(rhs.maxCLL, rhs.maxFALL);
  }
  inline bool operator>(const ContentLightLevel& rhs) const {
    return std::tie(maxCLL, maxFALL) > std::tie(rhs.maxCLL, rhs.maxFALL);
  }
  inline bool operator>=(const ContentLightLevel& rhs) const {
    return std::tie(maxCLL, maxFALL) >= std::tie(rhs.maxCLL, rhs.maxFALL);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.ContentLightLevel");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ContentLightLevel{";
    os << "maxCLL: " << ::android::internal::ToString(maxCLL);
    os << ", maxFALL: " << ::android::internal::ToString(maxFALL);
    os << "}";
    return os.str();
  }
};  // class ContentLightLevel
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
