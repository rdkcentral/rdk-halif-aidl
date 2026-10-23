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
#include <com/rdk/hal/broadcast/frontend/DvbTStandard.h>
#include <com/rdk/hal/broadcast/frontend/DvbTTransmissionMode.h>
#include <com/rdk/hal/broadcast/frontend/SpectralInversion.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief DVB-T specific capabilities.
 *
 * The AUTO member of all the enums will only be returned if the frontend supports a real auto selection of the
 * respective parameter. Just choosing the first applicable value and bailing out on error doesn't count as AUTO mode.
 *
 * There is deliberately no capability flag for PLP selection. PLP selection is a mandatory requirement for a DVB-T2
 * frontend, so a frontend that reports DvbTStandard.T2 in dvbTStandards shall support DvbTTuneParameters.plpId,
 * including DvbTPlpId.AUTO.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbTCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Supported bandwidths. */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTBandwidth> bandwidths;
  // @aidl-doc
  /** Supported standards. */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTStandard> dvbTStandards;
  // @aidl-doc
  /** Supported constellations (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTConstellation> constellations;
  // @aidl-doc
  /** Supported code rates (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value> codeRates;
  // @aidl-doc
  /** Supported guard intervals (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTGuardInterval> guardIntervals;
  // @aidl-doc
  /** Supported transmission mode (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTTransmissionMode> transmissionModes;
  // @aidl-doc
  /** Supported spectral inversion modes (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::SpectralInversion> inversions;
  // @aidl-doc
  /** Supported hierarchical transmission modes (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTHierarchy> hierarchies;
  // @aidl-doc
  /** Supported MISO modes (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTMiso> misoModes;
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, dvbTStandards, constellations, codeRates, guardIntervals, transmissionModes, inversions, hierarchies, misoModes, extension) != std::tie(rhs.bandwidths, rhs.dvbTStandards, rhs.constellations, rhs.codeRates, rhs.guardIntervals, rhs.transmissionModes, rhs.inversions, rhs.hierarchies, rhs.misoModes, rhs.extension);
  }
  inline bool operator<(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, dvbTStandards, constellations, codeRates, guardIntervals, transmissionModes, inversions, hierarchies, misoModes, extension) < std::tie(rhs.bandwidths, rhs.dvbTStandards, rhs.constellations, rhs.codeRates, rhs.guardIntervals, rhs.transmissionModes, rhs.inversions, rhs.hierarchies, rhs.misoModes, rhs.extension);
  }
  inline bool operator<=(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, dvbTStandards, constellations, codeRates, guardIntervals, transmissionModes, inversions, hierarchies, misoModes, extension) <= std::tie(rhs.bandwidths, rhs.dvbTStandards, rhs.constellations, rhs.codeRates, rhs.guardIntervals, rhs.transmissionModes, rhs.inversions, rhs.hierarchies, rhs.misoModes, rhs.extension);
  }
  inline bool operator==(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, dvbTStandards, constellations, codeRates, guardIntervals, transmissionModes, inversions, hierarchies, misoModes, extension) == std::tie(rhs.bandwidths, rhs.dvbTStandards, rhs.constellations, rhs.codeRates, rhs.guardIntervals, rhs.transmissionModes, rhs.inversions, rhs.hierarchies, rhs.misoModes, rhs.extension);
  }
  inline bool operator>(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, dvbTStandards, constellations, codeRates, guardIntervals, transmissionModes, inversions, hierarchies, misoModes, extension) > std::tie(rhs.bandwidths, rhs.dvbTStandards, rhs.constellations, rhs.codeRates, rhs.guardIntervals, rhs.transmissionModes, rhs.inversions, rhs.hierarchies, rhs.misoModes, rhs.extension);
  }
  inline bool operator>=(const DvbTCapabilities& rhs) const {
    return std::tie(bandwidths, dvbTStandards, constellations, codeRates, guardIntervals, transmissionModes, inversions, hierarchies, misoModes, extension) >= std::tie(rhs.bandwidths, rhs.dvbTStandards, rhs.constellations, rhs.codeRates, rhs.guardIntervals, rhs.transmissionModes, rhs.inversions, rhs.hierarchies, rhs.misoModes, rhs.extension);
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
    os << ", dvbTStandards: " << ::android::internal::ToString(dvbTStandards);
    os << ", constellations: " << ::android::internal::ToString(constellations);
    os << ", codeRates: " << ::android::internal::ToString(codeRates);
    os << ", guardIntervals: " << ::android::internal::ToString(guardIntervals);
    os << ", transmissionModes: " << ::android::internal::ToString(transmissionModes);
    os << ", inversions: " << ::android::internal::ToString(inversions);
    os << ", hierarchies: " << ::android::internal::ToString(hierarchies);
    os << ", misoModes: " << ::android::internal::ToString(misoModes);
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
