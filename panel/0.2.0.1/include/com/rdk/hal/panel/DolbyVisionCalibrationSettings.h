#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     Dolby Vision calibration settings.
 *             Legacy field names are retained for wire compatibility.
 *             Holds peak and minimum luminance, gamma correction, and the CIE 1931 xy
 *             chromaticity coordinates for Red, Green, Blue and White primaries.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
class DolbyVisionCalibrationSettings : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Peak white luminance in nits (legacy field name `Tmax`).
   * Used by the tone-mapping engine to map HDR content to the panel's
   * maximum brightness capability.
   * Valid range is 0 to 10000.
   */
  double Tmax = 0.000000;
  // @aidl-doc
  /**
   * Minimum black luminance in nits (legacy field name `Tmin`).
   * Used by the tone-mapping engine when mapping HDR content to the
   * panel's black-level capability.
   * Valid range is 0 to 10000.
   */
  double Tmin = 0.000000;
  // @aidl-doc
  /**
   * Display EOTF gamma exponent (legacy field name `Tgamma`).
   * Valid range is 1.80 to 2.60.
   */
  double Tgamma = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity x-coordinate of the Red primary.
   * Valid range is 0.0 to 1.0.
   */
  double Rx = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity y-coordinate of the Red primary.
   * Valid range is 0.0 to 1.0.
   */
  double Ry = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity x-coordinate of the Green primary.
   * Valid range is 0.0 to 1.0.
   */
  double Gx = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity y-coordinate of the Green primary.
   * Valid range is 0.0 to 1.0.
   */
  double Gy = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity x-coordinate of the Blue primary.
   * Valid range is 0.0 to 1.0.
   */
  double Bx = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity y-coordinate of the Blue primary.
   * Valid range is 0.0 to 1.0.
   */
  double By = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity x-coordinate of the White point.
   * Valid range is 0.0 to 1.0.
   */
  double Wx = 0.000000;
  // @aidl-doc
  /**
   * CIE 1931 xy chromaticity y-coordinate of the White point.
   * Valid range is 0.0 to 1.0.
   */
  double Wy = 0.000000;
  inline bool operator!=(const DolbyVisionCalibrationSettings& rhs) const {
    return std::tie(Tmax, Tmin, Tgamma, Rx, Ry, Gx, Gy, Bx, By, Wx, Wy) != std::tie(rhs.Tmax, rhs.Tmin, rhs.Tgamma, rhs.Rx, rhs.Ry, rhs.Gx, rhs.Gy, rhs.Bx, rhs.By, rhs.Wx, rhs.Wy);
  }
  inline bool operator<(const DolbyVisionCalibrationSettings& rhs) const {
    return std::tie(Tmax, Tmin, Tgamma, Rx, Ry, Gx, Gy, Bx, By, Wx, Wy) < std::tie(rhs.Tmax, rhs.Tmin, rhs.Tgamma, rhs.Rx, rhs.Ry, rhs.Gx, rhs.Gy, rhs.Bx, rhs.By, rhs.Wx, rhs.Wy);
  }
  inline bool operator<=(const DolbyVisionCalibrationSettings& rhs) const {
    return std::tie(Tmax, Tmin, Tgamma, Rx, Ry, Gx, Gy, Bx, By, Wx, Wy) <= std::tie(rhs.Tmax, rhs.Tmin, rhs.Tgamma, rhs.Rx, rhs.Ry, rhs.Gx, rhs.Gy, rhs.Bx, rhs.By, rhs.Wx, rhs.Wy);
  }
  inline bool operator==(const DolbyVisionCalibrationSettings& rhs) const {
    return std::tie(Tmax, Tmin, Tgamma, Rx, Ry, Gx, Gy, Bx, By, Wx, Wy) == std::tie(rhs.Tmax, rhs.Tmin, rhs.Tgamma, rhs.Rx, rhs.Ry, rhs.Gx, rhs.Gy, rhs.Bx, rhs.By, rhs.Wx, rhs.Wy);
  }
  inline bool operator>(const DolbyVisionCalibrationSettings& rhs) const {
    return std::tie(Tmax, Tmin, Tgamma, Rx, Ry, Gx, Gy, Bx, By, Wx, Wy) > std::tie(rhs.Tmax, rhs.Tmin, rhs.Tgamma, rhs.Rx, rhs.Ry, rhs.Gx, rhs.Gy, rhs.Bx, rhs.By, rhs.Wx, rhs.Wy);
  }
  inline bool operator>=(const DolbyVisionCalibrationSettings& rhs) const {
    return std::tie(Tmax, Tmin, Tgamma, Rx, Ry, Gx, Gy, Bx, By, Wx, Wy) >= std::tie(rhs.Tmax, rhs.Tmin, rhs.Tgamma, rhs.Rx, rhs.Ry, rhs.Gx, rhs.Gy, rhs.Bx, rhs.By, rhs.Wx, rhs.Wy);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.DolbyVisionCalibrationSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DolbyVisionCalibrationSettings{";
    os << "Tmax: " << ::android::internal::ToString(Tmax);
    os << ", Tmin: " << ::android::internal::ToString(Tmin);
    os << ", Tgamma: " << ::android::internal::ToString(Tgamma);
    os << ", Rx: " << ::android::internal::ToString(Rx);
    os << ", Ry: " << ::android::internal::ToString(Ry);
    os << ", Gx: " << ::android::internal::ToString(Gx);
    os << ", Gy: " << ::android::internal::ToString(Gy);
    os << ", Bx: " << ::android::internal::ToString(Bx);
    os << ", By: " << ::android::internal::ToString(By);
    os << ", Wx: " << ::android::internal::ToString(Wx);
    os << ", Wy: " << ::android::internal::ToString(Wy);
    os << "}";
    return os.str();
  }
};  // class DolbyVisionCalibrationSettings
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
