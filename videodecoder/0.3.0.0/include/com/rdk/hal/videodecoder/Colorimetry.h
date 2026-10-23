#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/ColorMatrix.h>
#include <com/rdk/hal/videodecoder/ColorPrimaries.h>
#include <com/rdk/hal/videodecoder/ColorRange.h>
#include <com/rdk/hal/videodecoder/TransferCharacteristics.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Full colorimetry signalling for a video stream — the four
 *             independent axes carried by the bitstream VUI / container
 *             metadata.
 *
 *  Replaces the prior single-enum `Colorimetry` (which conflated all four
 *  axes into a single "BT709 / BT2020 / ..." label and could not, e.g.,
 *  distinguish PQ from HLG when primaries are the same). Field shape
 *  matches:
 *
 *  - ITU-T H.273 / ISO/IEC 23091-2 CICP (the H.264/HEVC VUI carries these
 *    four values as `video_full_range_flag`, `matrix_coefficients`,
 *    `transfer_characteristics`, `colour_primaries`).
 *  - GStreamer `GstVideoColorimetry` — middleware extracts the same four
 *    values from caps' `colorimetry` field. See issue #367 for the
 *    extraction pattern (`vci.range`, `vci.matrix`, `vci.transfer`,
 *    `vci.primaries`).
 *
 *  <h3>Default values</h3>
 *  All four fields default to their `UNKNOWN` sentinel so an unset
 *  parcelable equals "no colorimetry signalled". Carriers using this
 *  parcelable as an `@nullable` field can additionally distinguish
 *  "no override" (null) from "explicitly all UNKNOWN" (non-null with
 *  every field = UNKNOWN).
 *
 *  <h3>Common configurations</h3>
 *  - SDR BT.709 :  range=LIMITED, matrix=BT709,      transfer=BT709,            primaries=BT709
 *  - SDR BT.601 :  range=LIMITED, matrix=BT601_525,  transfer=SMPTE170M,        primaries=BT601_525  (NTSC)
 *  - HDR10 (PQ) :  range=LIMITED, matrix=BT2020_NCL, transfer=SMPTE2084_PQ,     primaries=BT2020
 *  - HLG        :  range=LIMITED, matrix=BT2020_NCL, transfer=ARIB_STD_B67_HLG, primaries=BT2020
 *  - sRGB       :  range=FULL,    matrix=IDENTITY,   transfer=SRGB,             primaries=BT709
 *
 *  @author    Gerald Weatherup
 */
class Colorimetry : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Sample quantisation range (limited / studio vs full / computer).
   * GStreamer mapping: `GstVideoColorimetry.range` → `hdrColorimetry[0]`.
   */
  ::com::rdk::hal::videodecoder::ColorRange range = ::com::rdk::hal::videodecoder::ColorRange::UNKNOWN;
  // @aidl-doc
  /**
   * YCbCr → RGB conversion matrix coefficients.
   * GStreamer mapping: `GstVideoColorimetry.matrix` → `hdrColorimetry[1]`.
   */
  ::com::rdk::hal::videodecoder::ColorMatrix matrix = ::com::rdk::hal::videodecoder::ColorMatrix::UNKNOWN;
  // @aidl-doc
  /**
   * Opto-electrical transfer function (gamma / HDR curve).
   * GStreamer mapping: `GstVideoColorimetry.transfer` → `hdrColorimetry[2]`.
   * This is the field that distinguishes HDR systems (PQ vs HLG) when
   * primaries are the same.
   */
  ::com::rdk::hal::videodecoder::TransferCharacteristics transfer = ::com::rdk::hal::videodecoder::TransferCharacteristics::UNKNOWN;
  // @aidl-doc
  /**
   * Colour primaries (the gamut chromaticities).
   * GStreamer mapping: `GstVideoColorimetry.primaries` → `hdrColorimetry[3]`.
   */
  ::com::rdk::hal::videodecoder::ColorPrimaries primaries = ::com::rdk::hal::videodecoder::ColorPrimaries::UNKNOWN;
  inline bool operator!=(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) != std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator<(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) < std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator<=(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) <= std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator==(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) == std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator>(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) > std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator>=(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) >= std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.Colorimetry");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Colorimetry{";
    os << "range: " << ::android::internal::ToString(range);
    os << ", matrix: " << ::android::internal::ToString(matrix);
    os << ", transfer: " << ::android::internal::ToString(transfer);
    os << ", primaries: " << ::android::internal::ToString(primaries);
    os << "}";
    return os.str();
  }
};  // class Colorimetry
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
