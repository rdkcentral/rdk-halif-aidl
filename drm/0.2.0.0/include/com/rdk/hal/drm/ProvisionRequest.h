#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
// @aidl-doc
/** A provisioning request to be sent to a provisioning server. */
class ProvisionRequest : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The opaque certificate request blob. */
  ::std::vector<uint8_t> request;
  // @aidl-doc
  /**
   * The URL that the provisioning request may be sent to,
   * if known by the HAL implementation. An app can choose to
   * override this URL. If the HAL implementation does not provide
   * a defaultUrl, the returned string must be empty.
   */
  ::std::string defaultUrl;
  inline bool operator!=(const ProvisionRequest& rhs) const {
    return std::tie(request, defaultUrl) != std::tie(rhs.request, rhs.defaultUrl);
  }
  inline bool operator<(const ProvisionRequest& rhs) const {
    return std::tie(request, defaultUrl) < std::tie(rhs.request, rhs.defaultUrl);
  }
  inline bool operator<=(const ProvisionRequest& rhs) const {
    return std::tie(request, defaultUrl) <= std::tie(rhs.request, rhs.defaultUrl);
  }
  inline bool operator==(const ProvisionRequest& rhs) const {
    return std::tie(request, defaultUrl) == std::tie(rhs.request, rhs.defaultUrl);
  }
  inline bool operator>(const ProvisionRequest& rhs) const {
    return std::tie(request, defaultUrl) > std::tie(rhs.request, rhs.defaultUrl);
  }
  inline bool operator>=(const ProvisionRequest& rhs) const {
    return std::tie(request, defaultUrl) >= std::tie(rhs.request, rhs.defaultUrl);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.ProvisionRequest");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ProvisionRequest{";
    os << "request: " << ::android::internal::ToString(request);
    os << ", defaultUrl: " << ::android::internal::ToString(defaultUrl);
    os << "}";
    return os.str();
  }
};  // class ProvisionRequest
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
