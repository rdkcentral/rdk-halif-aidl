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
namespace videodecoder {
class Fraction : public ::android::Parcelable {
public:
  int32_t numerator = 0;
  int32_t denominator = 0;
  inline bool operator!=(const Fraction& rhs) const {
    return std::tie(numerator, denominator) != std::tie(rhs.numerator, rhs.denominator);
  }
  inline bool operator<(const Fraction& rhs) const {
    return std::tie(numerator, denominator) < std::tie(rhs.numerator, rhs.denominator);
  }
  inline bool operator<=(const Fraction& rhs) const {
    return std::tie(numerator, denominator) <= std::tie(rhs.numerator, rhs.denominator);
  }
  inline bool operator==(const Fraction& rhs) const {
    return std::tie(numerator, denominator) == std::tie(rhs.numerator, rhs.denominator);
  }
  inline bool operator>(const Fraction& rhs) const {
    return std::tie(numerator, denominator) > std::tie(rhs.numerator, rhs.denominator);
  }
  inline bool operator>=(const Fraction& rhs) const {
    return std::tie(numerator, denominator) >= std::tie(rhs.numerator, rhs.denominator);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.Fraction");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Fraction{";
    os << "numerator: " << ::android::internal::ToString(numerator);
    os << ", denominator: " << ::android::internal::ToString(denominator);
    os << "}";
    return os.str();
  }
};  // class Fraction
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
