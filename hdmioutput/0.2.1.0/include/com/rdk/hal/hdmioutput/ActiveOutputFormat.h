#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/AdditionalColorimetryExtension.h>
#include <com/rdk/hal/hdmioutput/Colorimetry.h>
#include <com/rdk/hal/hdmioutput/ExtendedColorimetry.h>
#include <com/rdk/hal/hdmioutput/HDROutputMode.h>
#include <com/rdk/hal/hdmioutput/PixelFormat.h>
#include <com/rdk/hal/hdmioutput/QuantizationRange.h>
#include <com/rdk/hal/hdmioutput/VIC.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     The video signal the HDMI output is sending now.
 *
 *  Read with IHDMIOutput.getActiveOutputFormat() and delivered whole by
 *  IHDMIOutputEventListener.onActiveOutputFormatChanged(). Every field
 *  describes the same instant: one negotiated change (e.g. a switch into
 *  HDR, which changes EOTF, colorimetry and colour depth together) is one
 *  event, so a client never sees a mix of old and new values.
 *
 *  Configured values stay in Property (e.g. HDR_OUTPUT_MODE may be AUTO);
 *  this parcelable is what they resolved to against the content and sink.
 *
 *  @author    Gerald Weatherup
 */
class ActiveOutputFormat : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Video mode on the wire. Never VIC0_UNAVAILABLE. */
  ::com::rdk::hal::hdmioutput::VIC vic = ::com::rdk::hal::hdmioutput::VIC(0);
  // @aidl-doc
  /** Base colorimetry. AVI InfoFrame C. */
  ::com::rdk::hal::hdmioutput::Colorimetry colorimetry = ::com::rdk::hal::hdmioutput::Colorimetry(0);
  // @aidl-doc
  /**
   * Extended colorimetry. AVI InfoFrame EC.
   * Meaningful only when colorimetry is EXTENDED_COLORIMETRY.
   */
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry extendedColorimetry = ::com::rdk::hal::hdmioutput::ExtendedColorimetry(0);
  // @aidl-doc
  /**
   * Additional colorimetry extension. AVI InfoFrame ACE.
   * Meaningful only when extendedColorimetry is
   * ADDITIONAL_COLORIMETRY_EXTENSION.
   */
  ::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension additionalColorimetryExtension = ::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension(0);
  // @aidl-doc
  /** Bits per colour component (8, 10, 12 or 16). */
  int32_t colorDepth = 0;
  // @aidl-doc
  /** Chroma format. AVI InfoFrame Y. */
  ::com::rdk::hal::hdmioutput::PixelFormat pixelFormat = ::com::rdk::hal::hdmioutput::PixelFormat(0);
  // @aidl-doc
  /** Quantization range. AVI InfoFrame Q / YQ. */
  ::com::rdk::hal::hdmioutput::QuantizationRange quantizationRange = ::com::rdk::hal::hdmioutput::QuantizationRange(0);
  // @aidl-doc
  /** Dynamic range being signalled. Never AUTO. */
  ::com::rdk::hal::hdmioutput::HDROutputMode hdrOutputMode = ::com::rdk::hal::hdmioutput::HDROutputMode(0);
  inline bool operator!=(const ActiveOutputFormat& rhs) const {
    return std::tie(vic, colorimetry, extendedColorimetry, additionalColorimetryExtension, colorDepth, pixelFormat, quantizationRange, hdrOutputMode) != std::tie(rhs.vic, rhs.colorimetry, rhs.extendedColorimetry, rhs.additionalColorimetryExtension, rhs.colorDepth, rhs.pixelFormat, rhs.quantizationRange, rhs.hdrOutputMode);
  }
  inline bool operator<(const ActiveOutputFormat& rhs) const {
    return std::tie(vic, colorimetry, extendedColorimetry, additionalColorimetryExtension, colorDepth, pixelFormat, quantizationRange, hdrOutputMode) < std::tie(rhs.vic, rhs.colorimetry, rhs.extendedColorimetry, rhs.additionalColorimetryExtension, rhs.colorDepth, rhs.pixelFormat, rhs.quantizationRange, rhs.hdrOutputMode);
  }
  inline bool operator<=(const ActiveOutputFormat& rhs) const {
    return std::tie(vic, colorimetry, extendedColorimetry, additionalColorimetryExtension, colorDepth, pixelFormat, quantizationRange, hdrOutputMode) <= std::tie(rhs.vic, rhs.colorimetry, rhs.extendedColorimetry, rhs.additionalColorimetryExtension, rhs.colorDepth, rhs.pixelFormat, rhs.quantizationRange, rhs.hdrOutputMode);
  }
  inline bool operator==(const ActiveOutputFormat& rhs) const {
    return std::tie(vic, colorimetry, extendedColorimetry, additionalColorimetryExtension, colorDepth, pixelFormat, quantizationRange, hdrOutputMode) == std::tie(rhs.vic, rhs.colorimetry, rhs.extendedColorimetry, rhs.additionalColorimetryExtension, rhs.colorDepth, rhs.pixelFormat, rhs.quantizationRange, rhs.hdrOutputMode);
  }
  inline bool operator>(const ActiveOutputFormat& rhs) const {
    return std::tie(vic, colorimetry, extendedColorimetry, additionalColorimetryExtension, colorDepth, pixelFormat, quantizationRange, hdrOutputMode) > std::tie(rhs.vic, rhs.colorimetry, rhs.extendedColorimetry, rhs.additionalColorimetryExtension, rhs.colorDepth, rhs.pixelFormat, rhs.quantizationRange, rhs.hdrOutputMode);
  }
  inline bool operator>=(const ActiveOutputFormat& rhs) const {
    return std::tie(vic, colorimetry, extendedColorimetry, additionalColorimetryExtension, colorDepth, pixelFormat, quantizationRange, hdrOutputMode) >= std::tie(rhs.vic, rhs.colorimetry, rhs.extendedColorimetry, rhs.additionalColorimetryExtension, rhs.colorDepth, rhs.pixelFormat, rhs.quantizationRange, rhs.hdrOutputMode);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmioutput.ActiveOutputFormat");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ActiveOutputFormat{";
    os << "vic: " << ::android::internal::ToString(vic);
    os << ", colorimetry: " << ::android::internal::ToString(colorimetry);
    os << ", extendedColorimetry: " << ::android::internal::ToString(extendedColorimetry);
    os << ", additionalColorimetryExtension: " << ::android::internal::ToString(additionalColorimetryExtension);
    os << ", colorDepth: " << ::android::internal::ToString(colorDepth);
    os << ", pixelFormat: " << ::android::internal::ToString(pixelFormat);
    os << ", quantizationRange: " << ::android::internal::ToString(quantizationRange);
    os << ", hdrOutputMode: " << ::android::internal::ToString(hdrOutputMode);
    os << "}";
    return os.str();
  }
};  // class ActiveOutputFormat
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
