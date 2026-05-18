#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/FreeSync.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class PlatformCapabilities : public ::android::Parcelable {
public:
  int32_t maximumConcurrentStartedPorts = 0;
  ::com::rdk::hal::hdmiinput::FreeSync freeSync = ::com::rdk::hal::hdmiinput::FreeSync(0);
  inline bool operator!=(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) != std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator<(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) < std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator<=(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) <= std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator==(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) == std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator>(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) > std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator>=(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) >= std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmiinput.PlatformCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlatformCapabilities{";
    os << "maximumConcurrentStartedPorts: " << ::android::internal::ToString(maximumConcurrentStartedPorts);
    os << ", freeSync: " << ::android::internal::ToString(freeSync);
    os << "}";
    return os.str();
  }
};  // class PlatformCapabilities
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
