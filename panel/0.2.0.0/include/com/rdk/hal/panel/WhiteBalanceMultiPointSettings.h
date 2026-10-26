#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     Display panel multi-point white balance entry.
 *             Holds the per-channel arrays for one colour-temperature multi-point
 *             white balance calibration entry.
 *             Used as the value type for PQParameter.MULTI_POINT_WB in set/get/getDefault/getCapabilities operations.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
class WhiteBalanceMultiPointSettings : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Colour temperature profile this white balance setting applies to. */
  ::std::string colourTemperature;
  // @aidl-doc
  /** Red-channel white point values for this colour temperature. */
  ::std::vector<int32_t> r;
  // @aidl-doc
  /** Green-channel white point values for this colour temperature. */
  ::std::vector<int32_t> g;
  // @aidl-doc
  /** Blue-channel white point values for this colour temperature. */
  ::std::vector<int32_t> b;
  inline bool operator!=(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(colourTemperature, r, g, b) != std::tie(rhs.colourTemperature, rhs.r, rhs.g, rhs.b);
  }
  inline bool operator<(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(colourTemperature, r, g, b) < std::tie(rhs.colourTemperature, rhs.r, rhs.g, rhs.b);
  }
  inline bool operator<=(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(colourTemperature, r, g, b) <= std::tie(rhs.colourTemperature, rhs.r, rhs.g, rhs.b);
  }
  inline bool operator==(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(colourTemperature, r, g, b) == std::tie(rhs.colourTemperature, rhs.r, rhs.g, rhs.b);
  }
  inline bool operator>(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(colourTemperature, r, g, b) > std::tie(rhs.colourTemperature, rhs.r, rhs.g, rhs.b);
  }
  inline bool operator>=(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(colourTemperature, r, g, b) >= std::tie(rhs.colourTemperature, rhs.r, rhs.g, rhs.b);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.WhiteBalanceMultiPointSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "WhiteBalanceMultiPointSettings{";
    os << "colourTemperature: " << ::android::internal::ToString(colourTemperature);
    os << ", r: " << ::android::internal::ToString(r);
    os << ", g: " << ::android::internal::ToString(g);
    os << ", b: " << ::android::internal::ToString(b);
    os << "}";
    return os.str();
  }
};  // class WhiteBalanceMultiPointSettings
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
