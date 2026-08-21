#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/ca/PowerControl.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace ca {
class CaCapabilities : public ::android::Parcelable {
public:
  ::com::rdk::hal::broadcast::ca::PowerControl powerControl = ::com::rdk::hal::broadcast::ca::PowerControl(0);
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const CaCapabilities& rhs) const {
    return std::tie(powerControl, extension) != std::tie(rhs.powerControl, rhs.extension);
  }
  inline bool operator<(const CaCapabilities& rhs) const {
    return std::tie(powerControl, extension) < std::tie(rhs.powerControl, rhs.extension);
  }
  inline bool operator<=(const CaCapabilities& rhs) const {
    return std::tie(powerControl, extension) <= std::tie(rhs.powerControl, rhs.extension);
  }
  inline bool operator==(const CaCapabilities& rhs) const {
    return std::tie(powerControl, extension) == std::tie(rhs.powerControl, rhs.extension);
  }
  inline bool operator>(const CaCapabilities& rhs) const {
    return std::tie(powerControl, extension) > std::tie(rhs.powerControl, rhs.extension);
  }
  inline bool operator>=(const CaCapabilities& rhs) const {
    return std::tie(powerControl, extension) >= std::tie(rhs.powerControl, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.ca.CaCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CaCapabilities{";
    os << "powerControl: " << ::android::internal::ToString(powerControl);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class CaCapabilities
}  // namespace ca
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
