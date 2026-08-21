#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/Bandwidth.h>
#include <com/rdk/hal/broadcast/frontend/CodingRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbCAnnex.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <com/rdk/hal/broadcast/frontend/SignalDetectMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class DvbCTuneParameters : public ::android::Parcelable {
public:
  int64_t frequency = 0L;
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode signalDetectMode = ::com::rdk::hal::broadcast::frontend::SignalDetectMode(0);
  int32_t symbolRate = 0;
  ::com::rdk::hal::broadcast::frontend::Bandwidth bandwidth = ::com::rdk::hal::broadcast::frontend::Bandwidth(0);
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex dvbCAnnex = ::com::rdk::hal::broadcast::frontend::DvbCAnnex(0);
  ::com::rdk::hal::broadcast::frontend::Modulation modulation = ::com::rdk::hal::broadcast::frontend::Modulation(0);
  ::com::rdk::hal::broadcast::frontend::CodingRate codingRate = ::com::rdk::hal::broadcast::frontend::CodingRate(0);
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codingRate, extension) != std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codingRate, rhs.extension);
  }
  inline bool operator<(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codingRate, extension) < std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codingRate, rhs.extension);
  }
  inline bool operator<=(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codingRate, extension) <= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codingRate, rhs.extension);
  }
  inline bool operator==(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codingRate, extension) == std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codingRate, rhs.extension);
  }
  inline bool operator>(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codingRate, extension) > std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codingRate, rhs.extension);
  }
  inline bool operator>=(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codingRate, extension) >= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codingRate, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbCTuneParameters");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbCTuneParameters{";
    os << "frequency: " << ::android::internal::ToString(frequency);
    os << ", signalDetectMode: " << ::android::internal::ToString(signalDetectMode);
    os << ", symbolRate: " << ::android::internal::ToString(symbolRate);
    os << ", bandwidth: " << ::android::internal::ToString(bandwidth);
    os << ", dvbCAnnex: " << ::android::internal::ToString(dvbCAnnex);
    os << ", modulation: " << ::android::internal::ToString(modulation);
    os << ", codingRate: " << ::android::internal::ToString(codingRate);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbCTuneParameters
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
