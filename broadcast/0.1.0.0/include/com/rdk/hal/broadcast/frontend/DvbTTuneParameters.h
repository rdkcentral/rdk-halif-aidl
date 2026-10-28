#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/DvbTBandwidth.h>
#include <com/rdk/hal/broadcast/frontend/DvbTCodeRates.h>
#include <com/rdk/hal/broadcast/frontend/DvbTConstellation.h>
#include <com/rdk/hal/broadcast/frontend/DvbTGuardInterval.h>
#include <com/rdk/hal/broadcast/frontend/DvbTHierarchy.h>
#include <com/rdk/hal/broadcast/frontend/DvbTMiso.h>
#include <com/rdk/hal/broadcast/frontend/DvbTPlpId.h>
#include <com/rdk/hal/broadcast/frontend/DvbTStandard.h>
#include <com/rdk/hal/broadcast/frontend/DvbTTransmissionMode.h>
#include <com/rdk/hal/broadcast/frontend/Frequency.h>
#include <com/rdk/hal/broadcast/frontend/SignalDetectMode.h>
#include <com/rdk/hal/broadcast/frontend/SpectralInversion.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief DVB-T-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbTTuneParameters : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The frequency to tune to. */
  ::com::rdk::hal::broadcast::frontend::Frequency frequency;
  // @aidl-doc
  /** Signal detect mode to use when tuning. */
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode signalDetectMode = ::com::rdk::hal::broadcast::frontend::SignalDetectMode(0);
  // @aidl-doc
  /** The bandwidth to use. */
  ::com::rdk::hal::broadcast::frontend::DvbTBandwidth bandwidth = ::com::rdk::hal::broadcast::frontend::DvbTBandwidth(0);
  // @aidl-doc
  /** Which DVB-T Standard to use. */
  ::com::rdk::hal::broadcast::frontend::DvbTStandard dvbTStandard = ::com::rdk::hal::broadcast::frontend::DvbTStandard(0);
  // @aidl-doc
  /** The constellation to use. */
  ::com::rdk::hal::broadcast::frontend::DvbTConstellation constellation = ::com::rdk::hal::broadcast::frontend::DvbTConstellation(0);
  // @aidl-doc
  /** LP and HP code rates for DVB-T/T2. */
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates codeRates;
  // @aidl-doc
  /** The guard interval to use. */
  ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval guardInterval = ::com::rdk::hal::broadcast::frontend::DvbTGuardInterval(0);
  // @aidl-doc
  /** The transmission mode to use. */
  ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode transmissionMode = ::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode(0);
  // @aidl-doc
  /** DVB-T/T2 spectral inversion mode to use when tuning. */
  ::com::rdk::hal::broadcast::frontend::SpectralInversion inversion = ::com::rdk::hal::broadcast::frontend::SpectralInversion(0);
  // @aidl-doc
  /** DVB-T hierarchical transmission mode. */
  ::com::rdk::hal::broadcast::frontend::DvbTHierarchy hierarchy = ::com::rdk::hal::broadcast::frontend::DvbTHierarchy(0);
  // @aidl-doc
  /** DVB-T MISO mode to use when tuning. */
  ::com::rdk::hal::broadcast::frontend::DvbTMiso misoMode = ::com::rdk::hal::broadcast::frontend::DvbTMiso(0);
  // @aidl-doc
  /**
   * The plp id for DVB-T2.
   *
   * Use DvbTPlpId.AUTO for auto. Otherwise specify a value in the range DvbTPlpId.MIN to DvbTPlpId.MAX.
   *
   * PLP selection is mandatory for a DVB-T2 frontend, so no capability query is needed: any frontend that reports
   * DvbTStandard.T2 in DvbTCapabilities.dvbTStandards shall honour this field. It is ignored when tuning DVB-T.
   */
  ::com::rdk::hal::broadcast::frontend::DvbTPlpId plpId;
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, constellation, codeRates, guardInterval, transmissionMode, inversion, hierarchy, misoMode, plpId, extension) != std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.constellation, rhs.codeRates, rhs.guardInterval, rhs.transmissionMode, rhs.inversion, rhs.hierarchy, rhs.misoMode, rhs.plpId, rhs.extension);
  }
  inline bool operator<(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, constellation, codeRates, guardInterval, transmissionMode, inversion, hierarchy, misoMode, plpId, extension) < std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.constellation, rhs.codeRates, rhs.guardInterval, rhs.transmissionMode, rhs.inversion, rhs.hierarchy, rhs.misoMode, rhs.plpId, rhs.extension);
  }
  inline bool operator<=(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, constellation, codeRates, guardInterval, transmissionMode, inversion, hierarchy, misoMode, plpId, extension) <= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.constellation, rhs.codeRates, rhs.guardInterval, rhs.transmissionMode, rhs.inversion, rhs.hierarchy, rhs.misoMode, rhs.plpId, rhs.extension);
  }
  inline bool operator==(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, constellation, codeRates, guardInterval, transmissionMode, inversion, hierarchy, misoMode, plpId, extension) == std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.constellation, rhs.codeRates, rhs.guardInterval, rhs.transmissionMode, rhs.inversion, rhs.hierarchy, rhs.misoMode, rhs.plpId, rhs.extension);
  }
  inline bool operator>(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, constellation, codeRates, guardInterval, transmissionMode, inversion, hierarchy, misoMode, plpId, extension) > std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.constellation, rhs.codeRates, rhs.guardInterval, rhs.transmissionMode, rhs.inversion, rhs.hierarchy, rhs.misoMode, rhs.plpId, rhs.extension);
  }
  inline bool operator>=(const DvbTTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, bandwidth, dvbTStandard, constellation, codeRates, guardInterval, transmissionMode, inversion, hierarchy, misoMode, plpId, extension) >= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.bandwidth, rhs.dvbTStandard, rhs.constellation, rhs.codeRates, rhs.guardInterval, rhs.transmissionMode, rhs.inversion, rhs.hierarchy, rhs.misoMode, rhs.plpId, rhs.extension);
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
    os << ", constellation: " << ::android::internal::ToString(constellation);
    os << ", codeRates: " << ::android::internal::ToString(codeRates);
    os << ", guardInterval: " << ::android::internal::ToString(guardInterval);
    os << ", transmissionMode: " << ::android::internal::ToString(transmissionMode);
    os << ", inversion: " << ::android::internal::ToString(inversion);
    os << ", hierarchy: " << ::android::internal::ToString(hierarchy);
    os << ", misoMode: " << ::android::internal::ToString(misoMode);
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
