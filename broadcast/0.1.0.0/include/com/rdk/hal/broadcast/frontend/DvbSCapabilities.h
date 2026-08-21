#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/CodingRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbSStandard.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <com/rdk/hal/broadcast/frontend/RollOff.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class DvbSCapabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::broadcast::frontend::Modulation> modulations;
  ::std::vector<::com::rdk::hal::broadcast::frontend::CodingRate> codingRates;
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbSStandard> dvbSStandards;
  ::std::vector<::com::rdk::hal::broadcast::frontend::RollOff> rollOffs;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbSCapabilities& rhs) const {
    return std::tie(modulations, codingRates, dvbSStandards, rollOffs, extension) != std::tie(rhs.modulations, rhs.codingRates, rhs.dvbSStandards, rhs.rollOffs, rhs.extension);
  }
  inline bool operator<(const DvbSCapabilities& rhs) const {
    return std::tie(modulations, codingRates, dvbSStandards, rollOffs, extension) < std::tie(rhs.modulations, rhs.codingRates, rhs.dvbSStandards, rhs.rollOffs, rhs.extension);
  }
  inline bool operator<=(const DvbSCapabilities& rhs) const {
    return std::tie(modulations, codingRates, dvbSStandards, rollOffs, extension) <= std::tie(rhs.modulations, rhs.codingRates, rhs.dvbSStandards, rhs.rollOffs, rhs.extension);
  }
  inline bool operator==(const DvbSCapabilities& rhs) const {
    return std::tie(modulations, codingRates, dvbSStandards, rollOffs, extension) == std::tie(rhs.modulations, rhs.codingRates, rhs.dvbSStandards, rhs.rollOffs, rhs.extension);
  }
  inline bool operator>(const DvbSCapabilities& rhs) const {
    return std::tie(modulations, codingRates, dvbSStandards, rollOffs, extension) > std::tie(rhs.modulations, rhs.codingRates, rhs.dvbSStandards, rhs.rollOffs, rhs.extension);
  }
  inline bool operator>=(const DvbSCapabilities& rhs) const {
    return std::tie(modulations, codingRates, dvbSStandards, rollOffs, extension) >= std::tie(rhs.modulations, rhs.codingRates, rhs.dvbSStandards, rhs.rollOffs, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbSCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbSCapabilities{";
    os << "modulations: " << ::android::internal::ToString(modulations);
    os << ", codingRates: " << ::android::internal::ToString(codingRates);
    os << ", dvbSStandards: " << ::android::internal::ToString(dvbSStandards);
    os << ", rollOffs: " << ::android::internal::ToString(rollOffs);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbSCapabilities
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
