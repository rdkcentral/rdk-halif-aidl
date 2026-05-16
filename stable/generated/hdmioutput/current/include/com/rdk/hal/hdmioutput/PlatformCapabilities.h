#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/FreeSync.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class PlatformCapabilities : public ::android::Parcelable {
public:
  double nativeFrameRate = 0.000000;
  ::com::rdk::hal::hdmioutput::FreeSync freeSync = ::com::rdk::hal::hdmioutput::FreeSync(0);
  inline bool operator!=(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) != std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator<(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) < std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator<=(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) <= std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator==(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) == std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator>(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) > std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator>=(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) >= std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmioutput.PlatformCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlatformCapabilities{";
    os << "nativeFrameRate: " << ::android::internal::ToString(nativeFrameRate);
    os << ", freeSync: " << ::android::internal::ToString(freeSync);
    os << "}";
    return os.str();
  }
};  // class PlatformCapabilities
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
