#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/AtscModulation.h>
#include <com/rdk/hal/broadcast/frontend/Frequency.h>
#include <com/rdk/hal/broadcast/frontend/SignalDetectMode.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief ATSC-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class AtscTuneParameters : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The frequency to tune to. */
  ::com::rdk::hal::broadcast::frontend::Frequency frequency;
  // @aidl-doc
  /** Signal detect mode to use when tuning. */
  ::com::rdk::hal::broadcast::frontend::SignalDetectMode signalDetectMode = ::com::rdk::hal::broadcast::frontend::SignalDetectMode(0);
  // @aidl-doc
  /** The modulation to use. */
  ::com::rdk::hal::broadcast::frontend::AtscModulation modulation = ::com::rdk::hal::broadcast::frontend::AtscModulation(0);
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const AtscTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, modulation, extension) != std::tie(rhs.frequency, rhs.signalDetectMode, rhs.modulation, rhs.extension);
  }
  inline bool operator<(const AtscTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, modulation, extension) < std::tie(rhs.frequency, rhs.signalDetectMode, rhs.modulation, rhs.extension);
  }
  inline bool operator<=(const AtscTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, modulation, extension) <= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.modulation, rhs.extension);
  }
  inline bool operator==(const AtscTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, modulation, extension) == std::tie(rhs.frequency, rhs.signalDetectMode, rhs.modulation, rhs.extension);
  }
  inline bool operator>(const AtscTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, modulation, extension) > std::tie(rhs.frequency, rhs.signalDetectMode, rhs.modulation, rhs.extension);
  }
  inline bool operator>=(const AtscTuneParameters& rhs) const {
    return std::tie(frequency, signalDetectMode, modulation, extension) >= std::tie(rhs.frequency, rhs.signalDetectMode, rhs.modulation, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.AtscTuneParameters");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "AtscTuneParameters{";
    os << "frequency: " << ::android::internal::ToString(frequency);
    os << ", signalDetectMode: " << ::android::internal::ToString(signalDetectMode);
    os << ", modulation: " << ::android::internal::ToString(modulation);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class AtscTuneParameters
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
