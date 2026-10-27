#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief A carrier to noise ratio, carrying its unit in the type.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.CNR.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class Cnr : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The carrier to noise ratio in dB.
   *
   * Defaults to -1000.0, which is far outside any physical ratio and means "no reading". AIDL does not permit a
   * float constant, so unlike every other value type in this package the sentinel cannot be named. A client should
   * treat any value below -999.0 as absent rather than test for equality, and should in any case take
   * SignalInfoReturn.readiness as the authoritative statement of whether the reading is usable.
   */
  float dB = -1000.000000f;
  inline bool operator!=(const Cnr& rhs) const {
    return std::tie(dB) != std::tie(rhs.dB);
  }
  inline bool operator<(const Cnr& rhs) const {
    return std::tie(dB) < std::tie(rhs.dB);
  }
  inline bool operator<=(const Cnr& rhs) const {
    return std::tie(dB) <= std::tie(rhs.dB);
  }
  inline bool operator==(const Cnr& rhs) const {
    return std::tie(dB) == std::tie(rhs.dB);
  }
  inline bool operator>(const Cnr& rhs) const {
    return std::tie(dB) > std::tie(rhs.dB);
  }
  inline bool operator>=(const Cnr& rhs) const {
    return std::tie(dB) >= std::tie(rhs.dB);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.Cnr");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Cnr{";
    os << "dB: " << ::android::internal::ToString(dB);
    os << "}";
    return os.str();
  }
};  // class Cnr
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
