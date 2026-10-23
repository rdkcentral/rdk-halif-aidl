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
 * @brief A count of errors that the demodulator was unable to correct.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.UNCORRECTED_ERRORS.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class UncorrectedErrorCount : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The actual count. */
  int64_t value = -1L;
  inline bool operator!=(const UncorrectedErrorCount& rhs) const {
    return std::tie(value) != std::tie(rhs.value);
  }
  inline bool operator<(const UncorrectedErrorCount& rhs) const {
    return std::tie(value) < std::tie(rhs.value);
  }
  inline bool operator<=(const UncorrectedErrorCount& rhs) const {
    return std::tie(value) <= std::tie(rhs.value);
  }
  inline bool operator==(const UncorrectedErrorCount& rhs) const {
    return std::tie(value) == std::tie(rhs.value);
  }
  inline bool operator>(const UncorrectedErrorCount& rhs) const {
    return std::tie(value) > std::tie(rhs.value);
  }
  inline bool operator>=(const UncorrectedErrorCount& rhs) const {
    return std::tie(value) >= std::tie(rhs.value);
  }

  // @aidl-doc
  /** No count available. Distinct from a real count of zero, which means no uncorrected errors. */
  enum : int64_t { UNDEFINED = -1L };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.UncorrectedErrorCount");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "UncorrectedErrorCount{";
    os << "value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class UncorrectedErrorCount
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
