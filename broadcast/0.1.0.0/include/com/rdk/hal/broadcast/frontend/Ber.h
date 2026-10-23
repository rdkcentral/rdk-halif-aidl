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
 * @brief A bit error rate, expressed as a count of error bits per 1 billion bits.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.BER and SignalInfoProperty.PRE_BER, the latter being the
 * rate measured before error correction.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class Ber : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The number of error bits per 1 billion bits. */
  int32_t errorBitsPerBillion = -1;
  inline bool operator!=(const Ber& rhs) const {
    return std::tie(errorBitsPerBillion) != std::tie(rhs.errorBitsPerBillion);
  }
  inline bool operator<(const Ber& rhs) const {
    return std::tie(errorBitsPerBillion) < std::tie(rhs.errorBitsPerBillion);
  }
  inline bool operator<=(const Ber& rhs) const {
    return std::tie(errorBitsPerBillion) <= std::tie(rhs.errorBitsPerBillion);
  }
  inline bool operator==(const Ber& rhs) const {
    return std::tie(errorBitsPerBillion) == std::tie(rhs.errorBitsPerBillion);
  }
  inline bool operator>(const Ber& rhs) const {
    return std::tie(errorBitsPerBillion) > std::tie(rhs.errorBitsPerBillion);
  }
  inline bool operator>=(const Ber& rhs) const {
    return std::tie(errorBitsPerBillion) >= std::tie(rhs.errorBitsPerBillion);
  }

  // @aidl-doc
  /** No bit error rate reading. Distinct from MIN, which is a real reading of zero errors. */
  enum : int32_t { UNDEFINED = -1 };
  // @aidl-doc
  /** The lowest valid bit error rate. */
  enum : int32_t { MIN = 0 };
  // @aidl-doc
  /** The highest valid bit error rate, i.e. every bit in error. */
  enum : int32_t { MAX = 1000000000 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.Ber");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Ber{";
    os << "errorBitsPerBillion: " << ::android::internal::ToString(errorBitsPerBillion);
    os << "}";
    return os.str();
  }
};  // class Ber
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
