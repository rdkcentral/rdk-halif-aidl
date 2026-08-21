#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/Bandwidth.h>
#include <com/rdk/hal/broadcast/frontend/CodingRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbTStandard.h>
#include <com/rdk/hal/broadcast/frontend/GuardInterval.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <com/rdk/hal/broadcast/frontend/TransmissionMode.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class DvbTCapabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::broadcast::frontend::Bandwidth> bandwidths;
  ::std::vector<::com::rdk::hal::broadcast::frontend::Modulation> subCarrierModulations;
  ::std::vector<::com::rdk::hal::broadcast::frontend::CodingRate> codingRates;
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTStandard> dvbTStandards;
  ::std::vector<::com::rdk::hal::broadcast::frontend::GuardInterval> guardIntervals;
  ::std::vector<::com::rdk::hal::broadcast::frontend::TransmissionMode> transmissionModes;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, subCarrierModulations, codingRates, dvbTStandards, guardIntervals, transmissionModes, extension) != std::tie(rhs.bandwidths, rhs.subCarrierModulations, rhs.codingRates, rhs.dvbTStandards, rhs.guardIntervals, rhs.transmissionModes, rhs.extension);
  }
  inline bool operator<(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, subCarrierModulations, codingRates, dvbTStandards, guardIntervals, transmissionModes, extension) < std::tie(rhs.bandwidths, rhs.subCarrierModulations, rhs.codingRates, rhs.dvbTStandards, rhs.guardIntervals, rhs.transmissionModes, rhs.extension);
  }
  inline bool operator<=(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, subCarrierModulations, codingRates, dvbTStandards, guardIntervals, transmissionModes, extension) <= std::tie(rhs.bandwidths, rhs.subCarrierModulations, rhs.codingRates, rhs.dvbTStandards, rhs.guardIntervals, rhs.transmissionModes, rhs.extension);
  }
  inline bool operator==(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, subCarrierModulations, codingRates, dvbTStandards, guardIntervals, transmissionModes, extension) == std::tie(rhs.bandwidths, rhs.subCarrierModulations, rhs.codingRates, rhs.dvbTStandards, rhs.guardIntervals, rhs.transmissionModes, rhs.extension);
  }
  inline bool operator>(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, subCarrierModulations, codingRates, dvbTStandards, guardIntervals, transmissionModes, extension) > std::tie(rhs.bandwidths, rhs.subCarrierModulations, rhs.codingRates, rhs.dvbTStandards, rhs.guardIntervals, rhs.transmissionModes, rhs.extension);
  }
  inline bool operator>=(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, subCarrierModulations, codingRates, dvbTStandards, guardIntervals, transmissionModes, extension) >= std::tie(rhs.bandwidths, rhs.subCarrierModulations, rhs.codingRates, rhs.dvbTStandards, rhs.guardIntervals, rhs.transmissionModes, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbTCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbTCapabilities{";
    os << "bandwidths: " << ::android::internal::ToString(bandwidths);
    os << ", subCarrierModulations: " << ::android::internal::ToString(subCarrierModulations);
    os << ", codingRates: " << ::android::internal::ToString(codingRates);
    os << ", dvbTStandards: " << ::android::internal::ToString(dvbTStandards);
    os << ", guardIntervals: " << ::android::internal::ToString(guardIntervals);
    os << ", transmissionModes: " << ::android::internal::ToString(transmissionModes);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbTCapabilities
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
