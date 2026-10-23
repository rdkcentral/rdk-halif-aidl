#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/DvbCAnnex.h>
#include <com/rdk/hal/broadcast/frontend/DvbCBandwidth.h>
#include <com/rdk/hal/broadcast/frontend/DvbCCodeRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbCModulation.h>
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
 * @brief DVB-C capability struct.
 *
 * The AUTO member of all the enums will only be returned if the frontend supports a real auto selection of the
 * respective parameter. Just choosing the first applicable value and bailing out on error doesn't count as AUTO mode.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbCCapabilities : public ::android::Parcelable {
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
  /** Supported bandwidths. */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbCBandwidth> bandwidths;
  // @aidl-doc
  /** Supported annex standards. */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbCAnnex> dvbCAnnexes;
  // @aidl-doc
  /** Supported modulations (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbCModulation> modulations;
  // @aidl-doc
  /** Supported code rates (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbCCodeRate> codeRates;
  // @aidl-doc
  /** Supported spectral inversion modes (AUTO is mandatory). */
  ::std::vector<::com::rdk::hal::broadcast::frontend::SpectralInversion> inversions;
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbCCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, bandwidths, dvbCAnnexes, modulations, codeRates, inversions, extension) != std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.bandwidths, rhs.dvbCAnnexes, rhs.modulations, rhs.codeRates, rhs.inversions, rhs.extension);
  }
  inline bool operator<(const DvbCCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, bandwidths, dvbCAnnexes, modulations, codeRates, inversions, extension) < std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.bandwidths, rhs.dvbCAnnexes, rhs.modulations, rhs.codeRates, rhs.inversions, rhs.extension);
  }
  inline bool operator<=(const DvbCCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, bandwidths, dvbCAnnexes, modulations, codeRates, inversions, extension) <= std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.bandwidths, rhs.dvbCAnnexes, rhs.modulations, rhs.codeRates, rhs.inversions, rhs.extension);
  }
  inline bool operator==(const DvbCCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, bandwidths, dvbCAnnexes, modulations, codeRates, inversions, extension) == std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.bandwidths, rhs.dvbCAnnexes, rhs.modulations, rhs.codeRates, rhs.inversions, rhs.extension);
  }
  inline bool operator>(const DvbCCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, bandwidths, dvbCAnnexes, modulations, codeRates, inversions, extension) > std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.bandwidths, rhs.dvbCAnnexes, rhs.modulations, rhs.codeRates, rhs.inversions, rhs.extension);
  }
  inline bool operator>=(const DvbCCapabilities& rhs) const {
    return std::tie(minSymbolRate, maxSymbolRate, isAutoSymbolRateSupported, bandwidths, dvbCAnnexes, modulations, codeRates, inversions, extension) >= std::tie(rhs.minSymbolRate, rhs.maxSymbolRate, rhs.isAutoSymbolRateSupported, rhs.bandwidths, rhs.dvbCAnnexes, rhs.modulations, rhs.codeRates, rhs.inversions, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbCCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbCCapabilities{";
    os << "minSymbolRate: " << ::android::internal::ToString(minSymbolRate);
    os << ", maxSymbolRate: " << ::android::internal::ToString(maxSymbolRate);
    os << ", isAutoSymbolRateSupported: " << ::android::internal::ToString(isAutoSymbolRateSupported);
    os << ", bandwidths: " << ::android::internal::ToString(bandwidths);
    os << ", dvbCAnnexes: " << ::android::internal::ToString(dvbCAnnexes);
    os << ", modulations: " << ::android::internal::ToString(modulations);
    os << ", codeRates: " << ::android::internal::ToString(codeRates);
    os << ", inversions: " << ::android::internal::ToString(inversions);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbCCapabilities
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
