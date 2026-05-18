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
namespace drm {
class ProvideProvisionResponseResult : public ::android::Parcelable {
public:
  ::std::vector<uint8_t> certificate;
  ::std::vector<uint8_t> wrappedKey;
  inline bool operator!=(const ProvideProvisionResponseResult& rhs) const {
    return std::tie(certificate, wrappedKey) != std::tie(rhs.certificate, rhs.wrappedKey);
  }
  inline bool operator<(const ProvideProvisionResponseResult& rhs) const {
    return std::tie(certificate, wrappedKey) < std::tie(rhs.certificate, rhs.wrappedKey);
  }
  inline bool operator<=(const ProvideProvisionResponseResult& rhs) const {
    return std::tie(certificate, wrappedKey) <= std::tie(rhs.certificate, rhs.wrappedKey);
  }
  inline bool operator==(const ProvideProvisionResponseResult& rhs) const {
    return std::tie(certificate, wrappedKey) == std::tie(rhs.certificate, rhs.wrappedKey);
  }
  inline bool operator>(const ProvideProvisionResponseResult& rhs) const {
    return std::tie(certificate, wrappedKey) > std::tie(rhs.certificate, rhs.wrappedKey);
  }
  inline bool operator>=(const ProvideProvisionResponseResult& rhs) const {
    return std::tie(certificate, wrappedKey) >= std::tie(rhs.certificate, rhs.wrappedKey);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.ProvideProvisionResponseResult");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ProvideProvisionResponseResult{";
    os << "certificate: " << ::android::internal::ToString(certificate);
    os << ", wrappedKey: " << ::android::internal::ToString(wrappedKey);
    os << "}";
    return os.str();
  }
};  // class ProvideProvisionResponseResult
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
