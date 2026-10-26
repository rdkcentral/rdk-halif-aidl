#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief A Signal Strength Indicator (SSI) as defined in NorDig.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.SSI.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class SignalStrengthIndicator : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The indicator, as a percentage of the NorDig scale. */
  int32_t percent = -1;
  inline bool operator!=(const SignalStrengthIndicator& rhs) const {
    return std::tie(percent) != std::tie(rhs.percent);
  }
  inline bool operator<(const SignalStrengthIndicator& rhs) const {
    return std::tie(percent) < std::tie(rhs.percent);
  }
  inline bool operator<=(const SignalStrengthIndicator& rhs) const {
    return std::tie(percent) <= std::tie(rhs.percent);
  }
  inline bool operator==(const SignalStrengthIndicator& rhs) const {
    return std::tie(percent) == std::tie(rhs.percent);
  }
  inline bool operator>(const SignalStrengthIndicator& rhs) const {
    return std::tie(percent) > std::tie(rhs.percent);
  }
  inline bool operator>=(const SignalStrengthIndicator& rhs) const {
    return std::tie(percent) >= std::tie(rhs.percent);
  }

  // @aidl-doc
  /** No indicator reading. Distinct from MIN, which is a real reading of the weakest signal. */
  enum : int32_t { UNDEFINED = -1 };
  // @aidl-doc
  /** The lowest valid indicator value. */
  enum : int32_t { MIN = 0 };
  // @aidl-doc
  /** The highest valid indicator value. */
  enum : int32_t { MAX = 100 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.SignalStrengthIndicator");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SignalStrengthIndicator{";
    os << "percent: " << ::android::internal::ToString(percent);
    os << "}";
    return os.str();
  }
};  // class SignalStrengthIndicator
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
