#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/KeyRequestType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class KeyRequest : public ::android::Parcelable {
public:
  ::std::vector<uint8_t> request;
  ::com::rdk::hal::drm::KeyRequestType requestType = ::com::rdk::hal::drm::KeyRequestType(0);
  ::android::String16 defaultUrl;
  inline bool operator!=(const KeyRequest& rhs) const {
    return std::tie(request, requestType, defaultUrl) != std::tie(rhs.request, rhs.requestType, rhs.defaultUrl);
  }
  inline bool operator<(const KeyRequest& rhs) const {
    return std::tie(request, requestType, defaultUrl) < std::tie(rhs.request, rhs.requestType, rhs.defaultUrl);
  }
  inline bool operator<=(const KeyRequest& rhs) const {
    return std::tie(request, requestType, defaultUrl) <= std::tie(rhs.request, rhs.requestType, rhs.defaultUrl);
  }
  inline bool operator==(const KeyRequest& rhs) const {
    return std::tie(request, requestType, defaultUrl) == std::tie(rhs.request, rhs.requestType, rhs.defaultUrl);
  }
  inline bool operator>(const KeyRequest& rhs) const {
    return std::tie(request, requestType, defaultUrl) > std::tie(rhs.request, rhs.requestType, rhs.defaultUrl);
  }
  inline bool operator>=(const KeyRequest& rhs) const {
    return std::tie(request, requestType, defaultUrl) >= std::tie(rhs.request, rhs.requestType, rhs.defaultUrl);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.KeyRequest");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "KeyRequest{";
    os << "request: " << ::android::internal::ToString(request);
    os << ", requestType: " << ::android::internal::ToString(requestType);
    os << ", defaultUrl: " << ::android::internal::ToString(defaultUrl);
    os << "}";
    return os.str();
  }
};  // class KeyRequest
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
