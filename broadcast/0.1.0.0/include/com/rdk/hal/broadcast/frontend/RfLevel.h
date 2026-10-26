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
 * @brief An RF signal level, carrying its unit in the type.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.RF_LEVEL.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class RfLevel : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The signal level in dBm.
   *
   * Defaults to -1000.0, which is far outside any physical RF level and means "no reading". AIDL does not permit a
   * float constant, so unlike every other value type in this package the sentinel cannot be named. A client should
   * treat any value below -999.0 as absent rather than test for equality, and should in any case take
   * SignalInfoReturn.readiness as the authoritative statement of whether the reading is usable.
   */
  float dBm = -1000.000000f;
  inline bool operator!=(const RfLevel& rhs) const {
    return std::tie(dBm) != std::tie(rhs.dBm);
  }
  inline bool operator<(const RfLevel& rhs) const {
    return std::tie(dBm) < std::tie(rhs.dBm);
  }
  inline bool operator<=(const RfLevel& rhs) const {
    return std::tie(dBm) <= std::tie(rhs.dBm);
  }
  inline bool operator==(const RfLevel& rhs) const {
    return std::tie(dBm) == std::tie(rhs.dBm);
  }
  inline bool operator>(const RfLevel& rhs) const {
    return std::tie(dBm) > std::tie(rhs.dBm);
  }
  inline bool operator>=(const RfLevel& rhs) const {
    return std::tie(dBm) >= std::tie(rhs.dBm);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.RfLevel");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "RfLevel{";
    os << "dBm: " << ::android::internal::ToString(dBm);
    os << "}";
    return os.str();
  }
};  // class RfLevel
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
