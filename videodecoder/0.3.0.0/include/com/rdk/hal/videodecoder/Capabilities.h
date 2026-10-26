#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/CodecCapabilities.h>
#include <com/rdk/hal/videodecoder/Colorimetry.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Video decoder capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Array of CodecCapability parcelables supported by this video decoder instance. */
  ::std::vector<::com::rdk::hal::videodecoder::CodecCapabilities> supportedCodecs;
  // @aidl-doc
  /** Array of DynamicRange values supported by this video decoder instance. */
  ::std::vector<::com::rdk::hal::videodecoder::DynamicRange> supportedDynamicRanges;
  // @aidl-doc
  /**
   * Array of Colorimetry values that this decoder instance can detect and report
   * in FrameMetadata.colorimetry. An empty array indicates colorimetry detection
   * is not supported.
   */
  ::std::vector<::com::rdk::hal::videodecoder::Colorimetry> supportedColorimetries;
  // @aidl-doc
  /**
   * Indicates if this decoder instance can work in secure video path (SVP) mode.
   * @see Property.SECURE_VIDEO
   */
  bool supportsSecure = false;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportedColorimetries, supportsSecure) != std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportedColorimetries, rhs.supportsSecure);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportedColorimetries, supportsSecure) < std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportedColorimetries, rhs.supportsSecure);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportedColorimetries, supportsSecure) <= std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportedColorimetries, rhs.supportsSecure);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportedColorimetries, supportsSecure) == std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportedColorimetries, rhs.supportsSecure);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportedColorimetries, supportsSecure) > std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportedColorimetries, rhs.supportsSecure);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportedColorimetries, supportsSecure) >= std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportedColorimetries, rhs.supportsSecure);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedCodecs: " << ::android::internal::ToString(supportedCodecs);
    os << ", supportedDynamicRanges: " << ::android::internal::ToString(supportedDynamicRanges);
    os << ", supportedColorimetries: " << ::android::internal::ToString(supportedColorimetries);
    os << ", supportsSecure: " << ::android::internal::ToString(supportsSecure);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
