#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class Capabilities : public ::android::Parcelable {
public:
  inline bool operator!=(const Capabilities&) const {
    return std::tie() != std::tie();
  }
  inline bool operator<(const Capabilities&) const {
    return std::tie() < std::tie();
  }
  inline bool operator<=(const Capabilities&) const {
    return std::tie() <= std::tie();
  }
  inline bool operator==(const Capabilities&) const {
    return std::tie() == std::tie();
  }
  inline bool operator>(const Capabilities&) const {
    return std::tie() > std::tie();
  }
  inline bool operator>=(const Capabilities&) const {
    return std::tie() >= std::tie();
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.avclock.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
