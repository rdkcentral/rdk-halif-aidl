#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Dolby Vision dual-layer presence flags.
 *
 *  Indicates whether a Dolby Vision Base Layer (BL) and/or Enhancement
 *  Layer (EL) are present in the bitstream, as signalled in the container.
 *  This lets the decoder configure the correct dual-stream DV decode mode
 *  before decoding begins.
 *
 *  A BL-only stream is a standard HEVC/AVC-compatible stream with Dolby
 *  Vision RPU metadata. A BL+EL stream carries an additional enhancement
 *  layer for full Dolby Vision quality.
 *
 *  Only applicable when the stream DynamicRange is DOLBY_VISION.
 *
 *  @author    Gerald Weatherup
 */
class DolbyVisionLayerFlags : public ::android::Parcelable {
public:
  // @aidl-doc
  /** true if a Dolby Vision Base Layer is present. */
  bool blPresent = false;
  // @aidl-doc
  /** true if a Dolby Vision Enhancement Layer is present. */
  bool elPresent = false;
  inline bool operator!=(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) != std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator<(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) < std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator<=(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) <= std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator==(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) == std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator>(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) > std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator>=(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) >= std::tie(rhs.blPresent, rhs.elPresent);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.DolbyVisionLayerFlags");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DolbyVisionLayerFlags{";
    os << "blPresent: " << ::android::internal::ToString(blPresent);
    os << ", elPresent: " << ::android::internal::ToString(elPresent);
    os << "}";
    return os.str();
  }
};  // class DolbyVisionLayerFlags
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
