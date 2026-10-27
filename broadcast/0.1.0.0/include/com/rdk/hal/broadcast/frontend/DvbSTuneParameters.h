#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/DvbSInnerFec.h>
#include <com/rdk/hal/broadcast/frontend/DvbSInputStreamId.h>
#include <com/rdk/hal/broadcast/frontend/DvbSModulation.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPilot.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPlsCode.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPlsMode.h>
#include <com/rdk/hal/broadcast/frontend/DvbSRollOff.h>
#include <com/rdk/hal/broadcast/frontend/DvbSStandard.h>
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
 * @brief DVB-S/S2/S2X-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbSTuneParameters : public ::android::Parcelable {
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
   * Use SymbolRate.AUTO for auto symbol rate detection (if supported, see DvbSCapabilities).
   */
  ::com::rdk::hal::broadcast::frontend::SymbolRate symbolRate;
  // @aidl-doc
  /** Which DVB-S standard to use. */
  ::com::rdk::hal::broadcast::frontend::DvbSStandard dvbSStandard = ::com::rdk::hal::broadcast::frontend::DvbSStandard(0);
  // @aidl-doc
  /** The modulation to use. */
  ::com::rdk::hal::broadcast::frontend::DvbSModulation modulation = ::com::rdk::hal::broadcast::frontend::DvbSModulation(0);
  // @aidl-doc
  /** Inner FEC code rate. */
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec innerFec = ::com::rdk::hal::broadcast::frontend::DvbSInnerFec(0);
  // @aidl-doc
  /** Roll-off factor. */
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff rollOff = ::com::rdk::hal::broadcast::frontend::DvbSRollOff(0);
  // @aidl-doc
  /** DVB-S2/S2X pilot symbol mode. */
  ::com::rdk::hal::broadcast::frontend::DvbSPilot pilot = ::com::rdk::hal::broadcast::frontend::DvbSPilot(0);
  // @aidl-doc
  /** DVB-S/S2/S2X spectral inversion mode to use when tuning. */
  ::com::rdk::hal::broadcast::frontend::SpectralInversion inversion = ::com::rdk::hal::broadcast::frontend::SpectralInversion(0);
  // @aidl-doc
  /** DVB-S2/S2X input stream identifier; use DvbSInputStreamId.UNDEFINED when not selecting a specific stream. */
  ::com::rdk::hal::broadcast::frontend::DvbSInputStreamId inputStreamId;
  // @aidl-doc
  /** DVB-S2/S2X physical-layer scrambling mode. */
  ::com::rdk::hal::broadcast::frontend::DvbSPlsMode plsMode = ::com::rdk::hal::broadcast::frontend::DvbSPlsMode(0);
  // @aidl-doc
  /** DVB-S2/S2X physical-layer scrambling code (scrambling-sequence index). */
  ::com::rdk::hal::broadcast::frontend::DvbSPlsCode plsCode;
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, pilot, inversion, inputStreamId, plsMode, plsCode, extension) != std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.pilot, rhs.inversion, rhs.inputStreamId, rhs.plsMode, rhs.plsCode, rhs.extension);
  }
  inline bool operator<(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, pilot, inversion, inputStreamId, plsMode, plsCode, extension) < std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.pilot, rhs.inversion, rhs.inputStreamId, rhs.plsMode, rhs.plsCode, rhs.extension);
  }
  inline bool operator<=(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, pilot, inversion, inputStreamId, plsMode, plsCode, extension) <= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.pilot, rhs.inversion, rhs.inputStreamId, rhs.plsMode, rhs.plsCode, rhs.extension);
  }
  inline bool operator==(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, pilot, inversion, inputStreamId, plsMode, plsCode, extension) == std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.pilot, rhs.inversion, rhs.inputStreamId, rhs.plsMode, rhs.plsCode, rhs.extension);
  }
  inline bool operator>(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, pilot, inversion, inputStreamId, plsMode, plsCode, extension) > std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.pilot, rhs.inversion, rhs.inputStreamId, rhs.plsMode, rhs.plsCode, rhs.extension);
  }
  inline bool operator>=(const DvbSTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, symbolRate, dvbSStandard, modulation, innerFec, rollOff, pilot, inversion, inputStreamId, plsMode, plsCode, extension) >= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.symbolRate, rhs.dvbSStandard, rhs.modulation, rhs.innerFec, rhs.rollOff, rhs.pilot, rhs.inversion, rhs.inputStreamId, rhs.plsMode, rhs.plsCode, rhs.extension);
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
    os << ", pilot: " << ::android::internal::ToString(pilot);
    os << ", inversion: " << ::android::internal::ToString(inversion);
    os << ", inputStreamId: " << ::android::internal::ToString(inputStreamId);
    os << ", plsMode: " << ::android::internal::ToString(plsMode);
    os << ", plsCode: " << ::android::internal::ToString(plsCode);
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
