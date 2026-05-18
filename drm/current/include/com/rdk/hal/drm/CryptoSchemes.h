#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/SupportedContentType.h>
#include <com/rdk/hal/drm/Uuid.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class CryptoSchemes : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::drm::Uuid> uuids;
  ::std::vector<::com::rdk::hal::drm::SupportedContentType> mimeTypes;
  inline bool operator!=(const CryptoSchemes& rhs) const {
    return std::tie(uuids, mimeTypes) != std::tie(rhs.uuids, rhs.mimeTypes);
  }
  inline bool operator<(const CryptoSchemes& rhs) const {
    return std::tie(uuids, mimeTypes) < std::tie(rhs.uuids, rhs.mimeTypes);
  }
  inline bool operator<=(const CryptoSchemes& rhs) const {
    return std::tie(uuids, mimeTypes) <= std::tie(rhs.uuids, rhs.mimeTypes);
  }
  inline bool operator==(const CryptoSchemes& rhs) const {
    return std::tie(uuids, mimeTypes) == std::tie(rhs.uuids, rhs.mimeTypes);
  }
  inline bool operator>(const CryptoSchemes& rhs) const {
    return std::tie(uuids, mimeTypes) > std::tie(rhs.uuids, rhs.mimeTypes);
  }
  inline bool operator>=(const CryptoSchemes& rhs) const {
    return std::tie(uuids, mimeTypes) >= std::tie(rhs.uuids, rhs.mimeTypes);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.CryptoSchemes");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CryptoSchemes{";
    os << "uuids: " << ::android::internal::ToString(uuids);
    os << ", mimeTypes: " << ::android::internal::ToString(mimeTypes);
    os << "}";
    return os.str();
  }
};  // class CryptoSchemes
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
