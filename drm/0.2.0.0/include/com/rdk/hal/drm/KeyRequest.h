#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/KeyRequestType.h>
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
/** A key request to be sent to a license server. */
class KeyRequest : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The opaque key request blob. */
  ::std::vector<uint8_t> request;
  // @aidl-doc
  /**
   * Enumerated type:
   *     INITIAL - the first key request for a license
   *     NONE - indicates that no request is needed because the keys
   *         are already loaded
   *     RENEWAL - is a subsequent key request used to refresh the
   *         keys in a license
   *     RELEASE - indicates keys are being released
   *     UPDATE - indicates that the keys need to be refetched after
   *         the initial license request
   */
  ::com::rdk::hal::drm::KeyRequestType requestType = ::com::rdk::hal::drm::KeyRequestType(0);
  // @aidl-doc
  /**
   * The URL that the request may be sent to,
   * if provided by the drm HAL. The app can choose to
   * override this URL. If the HAL implementation does not provide
   * a defaultUrl, the returned string must be empty.
   */
  ::std::string defaultUrl;
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
