#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/SecurityLevel.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class SupportedContentType : public ::android::Parcelable {
public:
  ::android::String16 mime;
  ::com::rdk::hal::drm::SecurityLevel minLevel = ::com::rdk::hal::drm::SecurityLevel(0);
  ::com::rdk::hal::drm::SecurityLevel maxLevel = ::com::rdk::hal::drm::SecurityLevel(0);
  inline bool operator!=(const SupportedContentType& rhs) const {
    return std::tie(mime, minLevel, maxLevel) != std::tie(rhs.mime, rhs.minLevel, rhs.maxLevel);
  }
  inline bool operator<(const SupportedContentType& rhs) const {
    return std::tie(mime, minLevel, maxLevel) < std::tie(rhs.mime, rhs.minLevel, rhs.maxLevel);
  }
  inline bool operator<=(const SupportedContentType& rhs) const {
    return std::tie(mime, minLevel, maxLevel) <= std::tie(rhs.mime, rhs.minLevel, rhs.maxLevel);
  }
  inline bool operator==(const SupportedContentType& rhs) const {
    return std::tie(mime, minLevel, maxLevel) == std::tie(rhs.mime, rhs.minLevel, rhs.maxLevel);
  }
  inline bool operator>(const SupportedContentType& rhs) const {
    return std::tie(mime, minLevel, maxLevel) > std::tie(rhs.mime, rhs.minLevel, rhs.maxLevel);
  }
  inline bool operator>=(const SupportedContentType& rhs) const {
    return std::tie(mime, minLevel, maxLevel) >= std::tie(rhs.mime, rhs.minLevel, rhs.maxLevel);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.SupportedContentType");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SupportedContentType{";
    os << "mime: " << ::android::internal::ToString(mime);
    os << ", minLevel: " << ::android::internal::ToString(minLevel);
    os << ", maxLevel: " << ::android::internal::ToString(maxLevel);
    os << "}";
    return os.str();
  }
};  // class SupportedContentType
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
