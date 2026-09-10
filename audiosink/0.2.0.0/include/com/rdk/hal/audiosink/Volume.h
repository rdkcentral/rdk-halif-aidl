#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class Volume : public ::android::Parcelable {
public:
  double volume = 0.000000;
  bool muted = false;
  inline bool operator!=(const Volume& rhs) const {
    return std::tie(volume, muted) != std::tie(rhs.volume, rhs.muted);
  }
  inline bool operator<(const Volume& rhs) const {
    return std::tie(volume, muted) < std::tie(rhs.volume, rhs.muted);
  }
  inline bool operator<=(const Volume& rhs) const {
    return std::tie(volume, muted) <= std::tie(rhs.volume, rhs.muted);
  }
  inline bool operator==(const Volume& rhs) const {
    return std::tie(volume, muted) == std::tie(rhs.volume, rhs.muted);
  }
  inline bool operator>(const Volume& rhs) const {
    return std::tie(volume, muted) > std::tie(rhs.volume, rhs.muted);
  }
  inline bool operator>=(const Volume& rhs) const {
    return std::tie(volume, muted) >= std::tie(rhs.volume, rhs.muted);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiosink.Volume");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Volume{";
    os << "volume: " << ::android::internal::ToString(volume);
    os << ", muted: " << ::android::internal::ToString(muted);
    os << "}";
    return os.str();
  }
};  // class Volume
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
