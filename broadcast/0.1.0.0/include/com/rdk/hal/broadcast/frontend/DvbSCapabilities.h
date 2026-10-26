#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/DvbSInnerFec.h>
#include <com/rdk/hal/broadcast/frontend/DvbSModulation.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPilot.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPlsMode.h>
#include <com/rdk/hal/broadcast/frontend/DvbSRollOff.h>
#include <com/rdk/hal/broadcast/frontend/DvbSStandard.h>
#include <com/rdk/hal/broadcast/frontend/SpectralInversion.h>
#include <com/rdk/hal/broadcast/frontend/SymbolRate.h>
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
 * @brief DVB-S/S2/S2X satellite broadcast standard capabilities.
 *
 * The AUTO member of all the enums will only be returned if the frontend supports a real auto selection of the
 * respective parameter. Just choosing the first applicable value and bailing out on error doesn't count as AUTO mode.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbSCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Minimum symbol rate. */
  ::com::rdk::hal::broadcast::frontend::SymbolRate minSymbolRate;
  // @aidl-doc
  /** Maximum symbol rate. */
  ::com::rdk::hal::broadcast::frontend::SymbolRate maxSymbolRate;
  // @aidl-doc
  /** Whether the tuner can autodetect the symbol rate. */
  bool isAutoSymbolRateSupported = false;
  // @aidl-doc
  /** Supported DVB-S standards. */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbSStandard> dvbSStandards;
  // @aidl-doc
  /** Supported modulations. */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbSModulation> modulations;
  // @aidl-doc
  /** Supported code rates (inner FEC)  (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbSInnerFec> innerFecs;
  // @aidl-doc
  /** Supported roll-off values (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbSRollOff> rollOffs;
  // @aidl-doc
  /** Supported DVB-S2/S2X pilot modes (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbSPilot> pilots;
  // @aidl-doc
  /** Supported DVB-S/S2/S2X spectral inversion modes (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::SpectralInversion> inversions;
  // @aidl-doc
  /** Supported DVB-S2/S2X physical-layer scrambling modes (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbSPlsMode> plsModes;
  // @aidl-doc
  /** Whether DVB-S2/S2X input stream selection is supported. */
  bool isInputStreamIdSupported = false;
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbSCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, dvbSStandards, modulations, innerFecs, rollOffs, pilots, inversions, plsModes, isInputStreamIdSupported, extension) != std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.dvbSStandards, rhs.modulations, rhs.innerFecs, rhs.rollOffs, rhs.pilots, rhs.inversions, rhs.plsModes, rhs.isInputStreamIdSupported, rhs.extension);
  }
  inline bool operator<(const DvbSCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, dvbSStandards, modulations, innerFecs, rollOffs, pilots, inversions, plsModes, isInputStreamIdSupported, extension) < std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.dvbSStandards, rhs.modulations, rhs.innerFecs, rhs.rollOffs, rhs.pilots, rhs.inversions, rhs.plsModes, rhs.isInputStreamIdSupported, rhs.extension);
  }
  inline bool operator<=(const DvbSCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, dvbSStandards, modulations, innerFecs, rollOffs, pilots, inversions, plsModes, isInputStreamIdSupported, extension) <= std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.dvbSStandards, rhs.modulations, rhs.innerFecs, rhs.rollOffs, rhs.pilots, rhs.inversions, rhs.plsModes, rhs.isInputStreamIdSupported, rhs.extension);
  }
  inline bool operator==(const DvbSCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, dvbSStandards, modulations, innerFecs, rollOffs, pilots, inversions, plsModes, isInputStreamIdSupported, extension) == std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.dvbSStandards, rhs.modulations, rhs.innerFecs, rhs.rollOffs, rhs.pilots, rhs.inversions, rhs.plsModes, rhs.isInputStreamIdSupported, rhs.extension);
  }
  inline bool operator>(const DvbSCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, dvbSStandards, modulations, innerFecs, rollOffs, pilots, inversions, plsModes, isInputStreamIdSupported, extension) > std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.dvbSStandards, rhs.modulations, rhs.innerFecs, rhs.rollOffs, rhs.pilots, rhs.inversions, rhs.plsModes, rhs.isInputStreamIdSupported, rhs.extension);
  }
  inline bool operator>=(const DvbSCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, dvbSStandards, modulations, innerFecs, rollOffs, pilots, inversions, plsModes, isInputStreamIdSupported, extension) >= std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.dvbSStandards, rhs.modulations, rhs.innerFecs, rhs.rollOffs, rhs.pilots, rhs.inversions, rhs.plsModes, rhs.isInputStreamIdSupported, rhs.extension);
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
    os << "minSymbolRate: " << ::android::internal::ToString(minSymbolRate);
    os << ", maxSymbolRate: " << ::android::internal::ToString(maxSymbolRate);
    os << ", isAutoSymbolRateSupported: " << ::android::internal::ToString(isAutoSymbolRateSupported);
    os << ", dvbSStandards: " << ::android::internal::ToString(dvbSStandards);
    os << ", modulations: " << ::android::internal::ToString(modulations);
    os << ", innerFecs: " << ::android::internal::ToString(innerFecs);
    os << ", rollOffs: " << ::android::internal::ToString(rollOffs);
    os << ", pilots: " << ::android::internal::ToString(pilots);
    os << ", inversions: " << ::android::internal::ToString(inversions);
    os << ", plsModes: " << ::android::internal::ToString(plsModes);
    os << ", isInputStreamIdSupported: " << ::android::internal::ToString(isInputStreamIdSupported);
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
