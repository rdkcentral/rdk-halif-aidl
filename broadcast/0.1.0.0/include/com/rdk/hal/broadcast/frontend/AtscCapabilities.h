#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class AtscCapabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::broadcast::frontend::Modulation> modulations;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const AtscCapabilities& rhs) const {
    return std::tie(modulations, extension) != std::tie(rhs.modulations, rhs.extension);
  }
  inline bool operator<(const AtscCapabilities& rhs) const {
    return std::tie(modulations, extension) < std::tie(rhs.modulations, rhs.extension);
  }
  inline bool operator<=(const AtscCapabilities& rhs) const {
    return std::tie(modulations, extension) <= std::tie(rhs.modulations, rhs.extension);
  }
  inline bool operator==(const AtscCapabilities& rhs) const {
    return std::tie(modulations, extension) == std::tie(rhs.modulations, rhs.extension);
  }
  inline bool operator>(const AtscCapabilities& rhs) const {
    return std::tie(modulations, extension) > std::tie(rhs.modulations, rhs.extension);
  }
  inline bool operator>=(const AtscCapabilities& rhs) const {
    return std::tie(modulations, extension) >= std::tie(rhs.modulations, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.AtscCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "AtscCapabilities{";
    os << "modulations: " << ::android::internal::ToString(modulations);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class AtscCapabilities
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
