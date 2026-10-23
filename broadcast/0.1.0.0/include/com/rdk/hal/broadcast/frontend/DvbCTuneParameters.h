#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/DvbCAnnex.h>
#include <com/rdk/hal/broadcast/frontend/DvbCBandwidth.h>
#include <com/rdk/hal/broadcast/frontend/DvbCCodeRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbCModulation.h>
#include <com/rdk/hal/broadcast/frontend/Frequency.h>
#include <com/rdk/hal/broadcast/frontend/SignalDetectMode.h>
#include <com/rdk/hal/broadcast/frontend/SpectralInversion.h>
#include <com/rdk/hal/broadcast/frontend/SymbolRate.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief DVB-C-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbCTuneParameters : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The frequency to tune to. */
  ::com::rdk::hal::broadcast::frontend::Frequency frequency;
  // @aidl-doc
  /** Signal detect mode to use when tuning. */
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode signalDetectMode = ::com::rdk::hal::broadcast::frontend::SignalDetectMode(0);
  // @aidl-doc
  /**
   * The symbol rate.
   *
   * Use SymbolRate.AUTO for auto symbol rate detection (if supported, see DvbCCapabilities).
   */
  ::com::rdk::hal::broadcast::frontend::SymbolRate symbolRate;
  // @aidl-doc
  /** The bandwidth to use. */
  ::com::rdk::hal::broadcast::frontend::DvbCBandwidth bandwidth = ::com::rdk::hal::broadcast::frontend::DvbCBandwidth(0);
  // @aidl-doc
  /** Which DVB-C Annex to use. */
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex dvbCAnnex = ::com::rdk::hal::broadcast::frontend::DvbCAnnex(0);
  // @aidl-doc
  /** The modulation to use. */
  ::com::rdk::hal::broadcast::frontend::DvbCModulation modulation = ::com::rdk::hal::broadcast::frontend::DvbCModulation(0);
  // @aidl-doc
  /** Code rate - the inner FEC. */
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate codeRate = ::com::rdk::hal::broadcast::frontend::DvbCCodeRate(0);
  // @aidl-doc
  /** Spectral inversion mode to use when tuning. */
  ::com::rdk::hal::broadcast::frontend::SpectralInversion inversion = ::com::rdk::hal::broadcast::frontend::SpectralInversion(0);
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codeRate, inversion, extension) != std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codeRate, rhs.inversion, rhs.extension);
  }
  inline bool operator<(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codeRate, inversion, extension) < std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codeRate, rhs.inversion, rhs.extension);
  }
  inline bool operator<=(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codeRate, inversion, extension) <= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codeRate, rhs.inversion, rhs.extension);
  }
  inline bool operator==(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codeRate, inversion, extension) == std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codeRate, rhs.inversion, rhs.extension);
  }
  inline bool operator>(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codeRate, inversion, extension) > std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codeRate, rhs.inversion, rhs.extension);
  }
  inline bool operator>=(const DvbCTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, bandwidth, dvbCAnnex, modulation, codeRate, inversion, extension) >= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.bandwidth, rhs.dvbCAnnex, rhs.modulation, rhs.codeRate, rhs.inversion, rhs.extension);
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
    os << ", codeRate: " << ::android::internal::ToString(codeRate);
    os << ", inversion: " << ::android::internal::ToString(inversion);
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
