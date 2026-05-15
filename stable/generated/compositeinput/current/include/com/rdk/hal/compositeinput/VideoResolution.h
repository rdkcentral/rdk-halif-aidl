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
namespace compositeinput {
class VideoResolution : public ::android::Parcelable {
public:
  int32_t pixelWidth = 0;
  int32_t pixelHeight = 0;
  bool interlaced = false;
  float frameRateInHz = 0.000000f;
  inline bool operator!=(const VideoResolution& rhs) const {
    return std::tie(pixelWidth, pixelHeight, interlaced, frameRateInHz) != std::tie(rhs.pixelWidth, rhs.pixelHeight, rhs.interlaced, rhs.frameRateInHz);
  }
  inline bool operator<(const VideoResolution& rhs) const {
    return std::tie(pixelWidth, pixelHeight, interlaced, frameRateInHz) < std::tie(rhs.pixelWidth, rhs.pixelHeight, rhs.interlaced, rhs.frameRateInHz);
  }
  inline bool operator<=(const VideoResolution& rhs) const {
    return std::tie(pixelWidth, pixelHeight, interlaced, frameRateInHz) <= std::tie(rhs.pixelWidth, rhs.pixelHeight, rhs.interlaced, rhs.frameRateInHz);
  }
  inline bool operator==(const VideoResolution& rhs) const {
    return std::tie(pixelWidth, pixelHeight, interlaced, frameRateInHz) == std::tie(rhs.pixelWidth, rhs.pixelHeight, rhs.interlaced, rhs.frameRateInHz);
  }
  inline bool operator>(const VideoResolution& rhs) const {
    return std::tie(pixelWidth, pixelHeight, interlaced, frameRateInHz) > std::tie(rhs.pixelWidth, rhs.pixelHeight, rhs.interlaced, rhs.frameRateInHz);
  }
  inline bool operator>=(const VideoResolution& rhs) const {
    return std::tie(pixelWidth, pixelHeight, interlaced, frameRateInHz) >= std::tie(rhs.pixelWidth, rhs.pixelHeight, rhs.interlaced, rhs.frameRateInHz);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.VideoResolution");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "VideoResolution{";
    os << "pixelWidth: " << ::android::internal::ToString(pixelWidth);
    os << ", pixelHeight: " << ::android::internal::ToString(pixelHeight);
    os << ", interlaced: " << ::android::internal::ToString(interlaced);
    os << ", frameRateInHz: " << ::android::internal::ToString(frameRateInHz);
    os << "}";
    return os.str();
  }
};  // class VideoResolution
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
