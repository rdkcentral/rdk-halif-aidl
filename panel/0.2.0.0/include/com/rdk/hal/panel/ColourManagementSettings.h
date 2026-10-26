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
 * @brief Grouped colour-management settings.
 *
 * This structure allows clients to update the complete CMS state with a single
 * read-modify-apply cycle instead of issuing separate writes for each colour
 * component. It carries one integer value for each hue, saturation, and
 * luminance slot across the six CMS colours: red, green, blue, yellow, cyan,
 * and magenta.
 */
class ColourManagementSettings : public ::android::Parcelable {
public:
  int32_t redHue = 0;
  int32_t redSaturation = 0;
  int32_t redLuminance = 0;
  int32_t greenHue = 0;
  int32_t greenSaturation = 0;
  int32_t greenLuminance = 0;
  int32_t blueHue = 0;
  int32_t blueSaturation = 0;
  int32_t blueLuminance = 0;
  int32_t yellowHue = 0;
  int32_t yellowSaturation = 0;
  int32_t yellowLuminance = 0;
  int32_t cyanHue = 0;
  int32_t cyanSaturation = 0;
  int32_t cyanLuminance = 0;
  int32_t magentaHue = 0;
  int32_t magentaSaturation = 0;
  int32_t magentaLuminance = 0;
  inline bool operator!=(const ColourManagementSettings& rhs) const {
    return std::tie(redHue, redSaturation, redLuminance, greenHue, greenSaturation, greenLuminance, blueHue, blueSaturation, blueLuminance, yellowHue, yellowSaturation, yellowLuminance, cyanHue, cyanSaturation, cyanLuminance, magentaHue, magentaSaturation, magentaLuminance) != std::tie(rhs.redHue, rhs.redSaturation, rhs.redLuminance, rhs.greenHue, rhs.greenSaturation, rhs.greenLuminance, rhs.blueHue, rhs.blueSaturation, rhs.blueLuminance, rhs.yellowHue, rhs.yellowSaturation, rhs.yellowLuminance, rhs.cyanHue, rhs.cyanSaturation, rhs.cyanLuminance, rhs.magentaHue, rhs.magentaSaturation, rhs.magentaLuminance);
  }
  inline bool operator<(const ColourManagementSettings& rhs) const {
    return std::tie(redHue, redSaturation, redLuminance, greenHue, greenSaturation, greenLuminance, blueHue, blueSaturation, blueLuminance, yellowHue, yellowSaturation, yellowLuminance, cyanHue, cyanSaturation, cyanLuminance, magentaHue, magentaSaturation, magentaLuminance) < std::tie(rhs.redHue, rhs.redSaturation, rhs.redLuminance, rhs.greenHue, rhs.greenSaturation, rhs.greenLuminance, rhs.blueHue, rhs.blueSaturation, rhs.blueLuminance, rhs.yellowHue, rhs.yellowSaturation, rhs.yellowLuminance, rhs.cyanHue, rhs.cyanSaturation, rhs.cyanLuminance, rhs.magentaHue, rhs.magentaSaturation, rhs.magentaLuminance);
  }
  inline bool operator<=(const ColourManagementSettings& rhs) const {
    return std::tie(redHue, redSaturation, redLuminance, greenHue, greenSaturation, greenLuminance, blueHue, blueSaturation, blueLuminance, yellowHue, yellowSaturation, yellowLuminance, cyanHue, cyanSaturation, cyanLuminance, magentaHue, magentaSaturation, magentaLuminance) <= std::tie(rhs.redHue, rhs.redSaturation, rhs.redLuminance, rhs.greenHue, rhs.greenSaturation, rhs.greenLuminance, rhs.blueHue, rhs.blueSaturation, rhs.blueLuminance, rhs.yellowHue, rhs.yellowSaturation, rhs.yellowLuminance, rhs.cyanHue, rhs.cyanSaturation, rhs.cyanLuminance, rhs.magentaHue, rhs.magentaSaturation, rhs.magentaLuminance);
  }
  inline bool operator==(const ColourManagementSettings& rhs) const {
    return std::tie(redHue, redSaturation, redLuminance, greenHue, greenSaturation, greenLuminance, blueHue, blueSaturation, blueLuminance, yellowHue, yellowSaturation, yellowLuminance, cyanHue, cyanSaturation, cyanLuminance, magentaHue, magentaSaturation, magentaLuminance) == std::tie(rhs.redHue, rhs.redSaturation, rhs.redLuminance, rhs.greenHue, rhs.greenSaturation, rhs.greenLuminance, rhs.blueHue, rhs.blueSaturation, rhs.blueLuminance, rhs.yellowHue, rhs.yellowSaturation, rhs.yellowLuminance, rhs.cyanHue, rhs.cyanSaturation, rhs.cyanLuminance, rhs.magentaHue, rhs.magentaSaturation, rhs.magentaLuminance);
  }
  inline bool operator>(const ColourManagementSettings& rhs) const {
    return std::tie(redHue, redSaturation, redLuminance, greenHue, greenSaturation, greenLuminance, blueHue, blueSaturation, blueLuminance, yellowHue, yellowSaturation, yellowLuminance, cyanHue, cyanSaturation, cyanLuminance, magentaHue, magentaSaturation, magentaLuminance) > std::tie(rhs.redHue, rhs.redSaturation, rhs.redLuminance, rhs.greenHue, rhs.greenSaturation, rhs.greenLuminance, rhs.blueHue, rhs.blueSaturation, rhs.blueLuminance, rhs.yellowHue, rhs.yellowSaturation, rhs.yellowLuminance, rhs.cyanHue, rhs.cyanSaturation, rhs.cyanLuminance, rhs.magentaHue, rhs.magentaSaturation, rhs.magentaLuminance);
  }
  inline bool operator>=(const ColourManagementSettings& rhs) const {
    return std::tie(redHue, redSaturation, redLuminance, greenHue, greenSaturation, greenLuminance, blueHue, blueSaturation, blueLuminance, yellowHue, yellowSaturation, yellowLuminance, cyanHue, cyanSaturation, cyanLuminance, magentaHue, magentaSaturation, magentaLuminance) >= std::tie(rhs.redHue, rhs.redSaturation, rhs.redLuminance, rhs.greenHue, rhs.greenSaturation, rhs.greenLuminance, rhs.blueHue, rhs.blueSaturation, rhs.blueLuminance, rhs.yellowHue, rhs.yellowSaturation, rhs.yellowLuminance, rhs.cyanHue, rhs.cyanSaturation, rhs.cyanLuminance, rhs.magentaHue, rhs.magentaSaturation, rhs.magentaLuminance);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.ColourManagementSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ColourManagementSettings{";
    os << "redHue: " << ::android::internal::ToString(redHue);
    os << ", redSaturation: " << ::android::internal::ToString(redSaturation);
    os << ", redLuminance: " << ::android::internal::ToString(redLuminance);
    os << ", greenHue: " << ::android::internal::ToString(greenHue);
    os << ", greenSaturation: " << ::android::internal::ToString(greenSaturation);
    os << ", greenLuminance: " << ::android::internal::ToString(greenLuminance);
    os << ", blueHue: " << ::android::internal::ToString(blueHue);
    os << ", blueSaturation: " << ::android::internal::ToString(blueSaturation);
    os << ", blueLuminance: " << ::android::internal::ToString(blueLuminance);
    os << ", yellowHue: " << ::android::internal::ToString(yellowHue);
    os << ", yellowSaturation: " << ::android::internal::ToString(yellowSaturation);
    os << ", yellowLuminance: " << ::android::internal::ToString(yellowLuminance);
    os << ", cyanHue: " << ::android::internal::ToString(cyanHue);
    os << ", cyanSaturation: " << ::android::internal::ToString(cyanSaturation);
    os << ", cyanLuminance: " << ::android::internal::ToString(cyanLuminance);
    os << ", magentaHue: " << ::android::internal::ToString(magentaHue);
    os << ", magentaSaturation: " << ::android::internal::ToString(magentaSaturation);
    os << ", magentaLuminance: " << ::android::internal::ToString(magentaLuminance);
    os << "}";
    return os.str();
  }
};  // class ColourManagementSettings
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
