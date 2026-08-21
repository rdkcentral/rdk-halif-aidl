#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/CodingRate.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class DvbTCodingRate : public ::android::Parcelable {
public:
  ::com::rdk::hal::broadcast::frontend::CodingRate lp = ::com::rdk::hal::broadcast::frontend::CodingRate(0);
  ::com::rdk::hal::broadcast::frontend::CodingRate hp = ::com::rdk::hal::broadcast::frontend::CodingRate(0);
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbTCodingRate& rhs) const {
    return std::tie(lp, hp, extension) != std::tie(rhs.lp, rhs.hp, rhs.extension);
  }
  inline bool operator<(const DvbTCodingRate& rhs) const {
    return std::tie(lp, hp, extension) < std::tie(rhs.lp, rhs.hp, rhs.extension);
  }
  inline bool operator<=(const DvbTCodingRate& rhs) const {
    return std::tie(lp, hp, extension) <= std::tie(rhs.lp, rhs.hp, rhs.extension);
  }
  inline bool operator==(const DvbTCodingRate& rhs) const {
    return std::tie(lp, hp, extension) == std::tie(rhs.lp, rhs.hp, rhs.extension);
  }
  inline bool operator>(const DvbTCodingRate& rhs) const {
    return std::tie(lp, hp, extension) > std::tie(rhs.lp, rhs.hp, rhs.extension);
  }
  inline bool operator>=(const DvbTCodingRate& rhs) const {
    return std::tie(lp, hp, extension) >= std::tie(rhs.lp, rhs.hp, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbTCodingRate");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbTCodingRate{";
    os << "lp: " << ::android::internal::ToString(lp);
    os << ", hp: " << ::android::internal::ToString(hp);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbTCodingRate
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
