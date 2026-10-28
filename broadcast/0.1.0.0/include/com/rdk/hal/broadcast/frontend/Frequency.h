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
 * @brief An RF frequency, carrying its unit in the type.
 *
 * Used wherever a frequency is tuned to, reported or bounded, so that a frequency cannot be confused with a symbol
 * rate or with a frequency expressed in another unit. The valid range is resource-specific: see
 * FrontendCapabilities.minFrequency and FrontendCapabilities.maxFrequency for the frontend in question.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class Frequency : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The frequency in Hertz. */
  int64_t hertz = 0L;
  inline bool operator!=(const Frequency& rhs) const {
    return std::tie(hertz) != std::tie(rhs.hertz);
  }
  inline bool operator<(const Frequency& rhs) const {
    return std::tie(hertz) < std::tie(rhs.hertz);
  }
  inline bool operator<=(const Frequency& rhs) const {
    return std::tie(hertz) <= std::tie(rhs.hertz);
  }
  inline bool operator==(const Frequency& rhs) const {
    return std::tie(hertz) == std::tie(rhs.hertz);
  }
  inline bool operator>(const Frequency& rhs) const {
    return std::tie(hertz) > std::tie(rhs.hertz);
  }
  inline bool operator>=(const Frequency& rhs) const {
    return std::tie(hertz) >= std::tie(rhs.hertz);
  }

  // @aidl-doc
  /** No frequency selected. */
  enum : int64_t { UNDEFINED = 0L };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.Frequency");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Frequency{";
    os << "hertz: " << ::android::internal::ToString(hertz);
    os << "}";
    return os.str();
  }
};  // class Frequency
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
