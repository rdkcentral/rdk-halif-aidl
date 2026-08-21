#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/Bandwidth.h>
#include <com/rdk/hal/broadcast/frontend/DvbTCodingRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbTStandard.h>
#include <com/rdk/hal/broadcast/frontend/GuardInterval.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <com/rdk/hal/broadcast/frontend/SignalDetectMode.h>
#include <com/rdk/hal/broadcast/frontend/TransmissionMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class DvbTTuneParameters : public ::android::Parcelable {
public:
  int64_t frequency = 0L;
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode signalDetectMode = ::com::rdk::hal::broadcast::frontend::SignalDetectMode(0);
  ::com::rdk::hal::broadcast::frontend::Bandwidth bandwidth = ::com::rdk::hal::broadcast::frontend::Bandwidth(0);
  ::com::rdk::hal::broadcast::frontend::DvbTStandard dvbTStandard = ::com::rdk::hal::broadcast::frontend::DvbTStandard(0);
  ::com::rdk::hal::broadcast::frontend::Modulation subCarrierModulation = ::com::rdk::hal::broadcast::frontend::Modulation(0);
  ::com::rdk::hal::broadcast::frontend::DvbTCodingRate codingRate;
  ::com::rdk::hal::broadcast::frontend::GuardInterval guardInterval = ::com::rdk::hal::broadcast::frontend::GuardInterval(0);
  ::com::rdk::hal::broadcast::frontend::TransmissionMode transmissionMode = ::com::rdk::hal::broadcast::frontend::TransmissionMode(0);
  int32_t plpId = 0;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, subCarrierModulation, codingRate, guardInterval, transmissionMode, plpId, extension) != std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.subCarrierModulation, rhs.codingRate, rhs.guardInterval, rhs.transmissionMode, rhs.plpId, rhs.extension);
  }
  inline bool operator<(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, subCarrierModulation, codingRate, guardInterval, transmissionMode, plpId, extension) < std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.subCarrierModulation, rhs.codingRate, rhs.guardInterval, rhs.transmissionMode, rhs.plpId, rhs.extension);
  }
  inline bool operator<=(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, subCarrierModulation, codingRate, guardInterval, transmissionMode, plpId, extension) <= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.subCarrierModulation, rhs.codingRate, rhs.guardInterval, rhs.transmissionMode, rhs.plpId, rhs.extension);
  }
  inline bool operator==(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, subCarrierModulation, codingRate, guardInterval, transmissionMode, plpId, extension) == std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.subCarrierModulation, rhs.codingRate, rhs.guardInterval, rhs.transmissionMode, rhs.plpId, rhs.extension);
  }
  inline bool operator>(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, subCarrierModulation, codingRate, guardInterval, transmissionMode, plpId, extension) > std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.subCarrierModulation, rhs.codingRate, rhs.guardInterval, rhs.transmissionMode, rhs.plpId, rhs.extension);
  }
  inline bool operator>=(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, subCarrierModulation, codingRate, guardInterval, transmissionMode, plpId, extension) >= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.subCarrierModulation, rhs.codingRate, rhs.guardInterval, rhs.transmissionMode, rhs.plpId, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbTTuneParameters");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbTTuneParameters{";
    os << "frequency: " << ::android::internal::ToString(frequency);
    os << ", signalDetectMode: " << ::android::internal::ToString(signalDetectMode);
    os << ", bandwidth: " << ::android::internal::ToString(bandwidth);
    os << ", dvbTStandard: " << ::android::internal::ToString(dvbTStandard);
    os << ", subCarrierModulation: " << ::android::internal::ToString(subCarrierModulation);
    os << ", codingRate: " << ::android::internal::ToString(codingRate);
    os << ", guardInterval: " << ::android::internal::ToString(guardInterval);
    os << ", transmissionMode: " << ::android::internal::ToString(transmissionMode);
    os << ", plpId: " << ::android::internal::ToString(plpId);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbTTuneParameters
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
