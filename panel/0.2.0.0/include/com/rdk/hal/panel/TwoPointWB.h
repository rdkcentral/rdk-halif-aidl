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
namespace panel {
// @aidl-doc
/**
 *  @brief     2-point white balance entry.
 *             Holds the RGB gain and offset values for one colour-temperature
 *             2-point white balance calibration entry.
 *             Used as the value type for PQParameter.TWO_POINT_WB in set/get/getDefault/getCapabilities operations.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
class TwoPointWB : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Colour temperature profile this white balance entry applies to. */
  ::android::String16 colourTemperature;
  // @aidl-doc
  /** Red-channel gain value. Valid range is 0 to 2047. */
  int32_t redGain = 0;
  // @aidl-doc
  /** Red-channel offset value. Valid range is -1024 to 1023. */
  int32_t redOffset = 0;
  // @aidl-doc
  /** Green-channel gain value. Valid range is 0 to 2047. */
  int32_t greenGain = 0;
  // @aidl-doc
  /** Green-channel offset value. Valid range is -1024 to 1023. */
  int32_t greenOffset = 0;
  // @aidl-doc
  /** Blue-channel gain value. Valid range is 0 to 2047. */
  int32_t blueGain = 0;
  // @aidl-doc
  /** Blue-channel offset value. Valid range is -1024 to 1023. */
  int32_t blueOffset = 0;
  inline bool operator!=(const TwoPointWB& rhs) const {
    return std::tie(colourTemperature, redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) != std::tie(rhs.colourTemperature, rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
  }
  inline bool operator<(const TwoPointWB& rhs) const {
    return std::tie(colourTemperature, redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) < std::tie(rhs.colourTemperature, rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
  }
  inline bool operator<=(const TwoPointWB& rhs) const {
    return std::tie(colourTemperature, redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) <= std::tie(rhs.colourTemperature, rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
  }
  inline bool operator==(const TwoPointWB& rhs) const {
    return std::tie(colourTemperature, redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) == std::tie(rhs.colourTemperature, rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
  }
  inline bool operator>(const TwoPointWB& rhs) const {
    return std::tie(colourTemperature, redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) > std::tie(rhs.colourTemperature, rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
  }
  inline bool operator>=(const TwoPointWB& rhs) const {
    return std::tie(colourTemperature, redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) >= std::tie(rhs.colourTemperature, rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.TwoPointWB");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "TwoPointWB{";
    os << "colourTemperature: " << ::android::internal::ToString(colourTemperature);
    os << ", redGain: " << ::android::internal::ToString(redGain);
    os << ", redOffset: " << ::android::internal::ToString(redOffset);
    os << ", greenGain: " << ::android::internal::ToString(greenGain);
    os << ", greenOffset: " << ::android::internal::ToString(greenOffset);
    os << ", blueGain: " << ::android::internal::ToString(blueGain);
    os << ", blueOffset: " << ::android::internal::ToString(blueOffset);
    os << "}";
    return os.str();
  }
};  // class TwoPointWB
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
