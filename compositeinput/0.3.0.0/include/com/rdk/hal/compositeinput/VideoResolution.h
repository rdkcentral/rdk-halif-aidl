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
// @aidl-doc
/**
 * @brief Video resolution and format information.
 *
 * Describes the digitized video output format from the composite input.
 * The SOC vendor handles analog video standard detection (NTSC/PAL/SECAM)
 * and color decoding internally, providing standardized digital output.
 */
class VideoResolution : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Horizontal resolution in pixels (e.g., 720). */
  int32_t pixelWidth = 0;
  // @aidl-doc
  /** Vertical resolution in pixels (e.g., 480 or 576). */
  int32_t pixelHeight = 0;
  // @aidl-doc
  /** True if interlaced, false if progressive. */
  bool interlaced = false;
  // @aidl-doc
  /** Frame rate in Hz (e.g., 25.0, 29.97, 50.0, 59.94). */
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
