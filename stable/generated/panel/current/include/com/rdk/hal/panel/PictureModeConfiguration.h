#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class PictureModeConfiguration : public ::android::Parcelable {
public:
  ::android::String16 pictureMode;
  ::com::rdk::hal::videodecoder::DynamicRange format = ::com::rdk::hal::videodecoder::DynamicRange(0);
  ::com::rdk::hal::AVSource source = ::com::rdk::hal::AVSource(0);
  inline bool operator!=(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, format, source) != std::tie(rhs.pictureMode, rhs.format, rhs.source);
  }
  inline bool operator<(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, format, source) < std::tie(rhs.pictureMode, rhs.format, rhs.source);
  }
  inline bool operator<=(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, format, source) <= std::tie(rhs.pictureMode, rhs.format, rhs.source);
  }
  inline bool operator==(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, format, source) == std::tie(rhs.pictureMode, rhs.format, rhs.source);
  }
  inline bool operator>(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, format, source) > std::tie(rhs.pictureMode, rhs.format, rhs.source);
  }
  inline bool operator>=(const PictureModeConfiguration& rhs) const {
    return std::tie(pictureMode, format, source) >= std::tie(rhs.pictureMode, rhs.format, rhs.source);
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
    os << ", format: " << ::android::internal::ToString(format);
    os << ", source: " << ::android::internal::ToString(source);
    os << "}";
    return os.str();
  }
};  // class PictureModeConfiguration
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
