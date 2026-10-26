#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/PanelSource.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     Picture mode configuration.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
class PictureModeConfiguration : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The picture mode. */
  ::std::string pictureMode;
  // @aidl-doc
  /** The dynamic range. */
  ::com::rdk::hal::videodecoder::DynamicRange dynamicRange = ::com::rdk::hal::videodecoder::DynamicRange(0);
  // @aidl-doc
  /** The AV source. */
  ::com::rdk::hal::panel::PanelSource source;
  inline bool operator!=(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, dynamicRange, source) != std::tie(rhs.pictureMode, rhs.dynamicRange, rhs.source);
  }
  inline bool operator<(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, dynamicRange, source) < std::tie(rhs.pictureMode, rhs.dynamicRange, rhs.source);
  }
  inline bool operator<=(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, dynamicRange, source) <= std::tie(rhs.pictureMode, rhs.dynamicRange, rhs.source);
  }
  inline bool operator==(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, dynamicRange, source) == std::tie(rhs.pictureMode, rhs.dynamicRange, rhs.source);
  }
  inline bool operator>(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, dynamicRange, source) > std::tie(rhs.pictureMode, rhs.dynamicRange, rhs.source);
  }
  inline bool operator>=(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, dynamicRange, source) >= std::tie(rhs.pictureMode, rhs.dynamicRange, rhs.source);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PictureModeConfiguration");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PictureModeConfiguration{";
    os << "pictureMode: " << ::android::internal::ToString(pictureMode);
    os << ", dynamicRange: " << ::android::internal::ToString(dynamicRange);
    os << ", source: " << ::android::internal::ToString(source);
    os << "}";
    return os.str();
  }
};  // class PictureModeConfiguration
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
