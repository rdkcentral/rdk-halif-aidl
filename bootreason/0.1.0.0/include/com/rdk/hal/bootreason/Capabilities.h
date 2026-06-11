#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/bootreason/BootCause.h>
#include <com/rdk/hal/bootreason/ResetType.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
class Capabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::bootreason::BootCause> supportedBootCauses;
  ::std::vector<::com::rdk::hal::bootreason::ResetType> supportedResetTypes;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedBootCauses, supportedResetTypes) != std::tie(rhs.supportedBootCauses, rhs.supportedResetTypes);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedBootCauses, supportedResetTypes) < std::tie(rhs.supportedBootCauses, rhs.supportedResetTypes);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedBootCauses, supportedResetTypes) <= std::tie(rhs.supportedBootCauses, rhs.supportedResetTypes);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedBootCauses, supportedResetTypes) == std::tie(rhs.supportedBootCauses, rhs.supportedResetTypes);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedBootCauses, supportedResetTypes) > std::tie(rhs.supportedBootCauses, rhs.supportedResetTypes);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedBootCauses, supportedResetTypes) >= std::tie(rhs.supportedBootCauses, rhs.supportedResetTypes);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.bootreason.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedBootCauses: " << ::android::internal::ToString(supportedBootCauses);
    os << ", supportedResetTypes: " << ::android::internal::ToString(supportedResetTypes);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
