#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/HdcpLevel.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class HdcpLevels : public ::android::Parcelable {
public:
  ::com::rdk::hal::drm::HdcpLevel connectedLevel = ::com::rdk::hal::drm::HdcpLevel(0);
  ::com::rdk::hal::drm::HdcpLevel maxLevel = ::com::rdk::hal::drm::HdcpLevel(0);
  inline bool operator!=(const HdcpLevels& rhs) const {
    return std::tie(connectedLevel, maxLevel) != std::tie(rhs.connectedLevel, rhs.maxLevel);
  }
  inline bool operator<(const HdcpLevels& rhs) const {
    return std::tie(connectedLevel, maxLevel) < std::tie(rhs.connectedLevel, rhs.maxLevel);
  }
  inline bool operator<=(const HdcpLevels& rhs) const {
    return std::tie(connectedLevel, maxLevel) <= std::tie(rhs.connectedLevel, rhs.maxLevel);
  }
  inline bool operator==(const HdcpLevels& rhs) const {
    return std::tie(connectedLevel, maxLevel) == std::tie(rhs.connectedLevel, rhs.maxLevel);
  }
  inline bool operator>(const HdcpLevels& rhs) const {
    return std::tie(connectedLevel, maxLevel) > std::tie(rhs.connectedLevel, rhs.maxLevel);
  }
  inline bool operator>=(const HdcpLevels& rhs) const {
    return std::tie(connectedLevel, maxLevel) >= std::tie(rhs.connectedLevel, rhs.maxLevel);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.HdcpLevels");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "HdcpLevels{";
    os << "connectedLevel: " << ::android::internal::ToString(connectedLevel);
    os << ", maxLevel: " << ::android::internal::ToString(maxLevel);
    os << "}";
    return os.str();
  }
};  // class HdcpLevels
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
