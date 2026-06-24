#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class WhiteBalanceMultiPointSettings : public ::android::Parcelable {
public:
  ::std::vector<int32_t> r;
  ::std::vector<int32_t> g;
  ::std::vector<int32_t> b;
  inline bool operator!=(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(r, g, b) != std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator<(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(r, g, b) < std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator<=(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(r, g, b) <= std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator==(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(r, g, b) == std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator>(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(r, g, b) > std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator>=(const WhiteBalanceMultiPointSettings& rhs) const {
    return std::tie(r, g, b) >= std::tie(rhs.r, rhs.g, rhs.b);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.WhiteBalanceMultiPointSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "WhiteBalanceMultiPointSettings{";
    os << "r: " << ::android::internal::ToString(r);
    os << ", g: " << ::android::internal::ToString(g);
    os << ", b: " << ::android::internal::ToString(b);
    os << "}";
    return os.str();
  }
};  // class WhiteBalanceMultiPointSettings
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
