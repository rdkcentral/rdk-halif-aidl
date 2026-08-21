#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/CodingRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbSStandard.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <com/rdk/hal/broadcast/frontend/RollOff.h>
#include <com/rdk/hal/broadcast/frontend/SignalDetectMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class DvbSTuneParameters : public ::android::Parcelable {
public:
  int64_t frequency = 0L;
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode signalDetectMode = ::com::rdk::hal::broadcast::frontend::SignalDetectMode(0);
  int32_t symbolRate = 0;
  ::com::rdk::hal::broadcast::frontend::DvbSStandard dvbSStandard = ::com::rdk::hal::broadcast::frontend::DvbSStandard(0);
  ::com::rdk::hal::broadcast::frontend::Modulation modulation = ::com::rdk::hal::broadcast::frontend::Modulation(0);
  ::com::rdk::hal::broadcast::frontend::CodingRate innerFec = ::com::rdk::hal::broadcast::frontend::CodingRate(0);
  ::com::rdk::hal::broadcast::frontend::RollOff rollOff = ::com::rdk::hal::broadcast::frontend::RollOff(0);
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, extension) != std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.extension);
  }
  inline bool operator<(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, extension) < std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.extension);
  }
  inline bool operator<=(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, extension) <= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.extension);
  }
  inline bool operator==(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, extension) == std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.extension);
  }
  inline bool operator>(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, extension) > std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.extension);
  }
  inline bool operator>=(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, extension) >= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbSTuneParameters");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbSTuneParameters{";
    os << "frequency: " << ::android::internal::ToString(frequency);
    os << ", signalDetectMode: " << ::android::internal::ToString(signalDetectMode);
    os << ", symbolRate: " << ::android::internal::ToString(symbolRate);
    os << ", dvbSStandard: " << ::android::internal::ToString(dvbSStandard);
    os << ", modulation: " << ::android::internal::ToString(modulation);
    os << ", innerFec: " << ::android::internal::ToString(innerFec);
    os << ", rollOff: " << ::android::internal::ToString(rollOff);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbSTuneParameters
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
