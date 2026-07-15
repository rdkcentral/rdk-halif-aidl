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
class ContentLightLevel : public ::android::Parcelable {
public:
  int32_t maxCLL = 0;
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
