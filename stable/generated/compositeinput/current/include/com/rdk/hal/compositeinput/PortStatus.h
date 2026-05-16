#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/SignalStatus.h>
#include <com/rdk/hal/compositeinput/VideoResolution.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class PortStatus : public ::android::Parcelable {
public:
  int32_t portId = 0;
  bool connected = false;
  bool active = false;
  ::com::rdk::hal::compositeinput::SignalStatus signalStatus = ::com::rdk::hal::compositeinput::SignalStatus(0);
  ::std::optional<::com::rdk::hal::compositeinput::VideoResolution> detectedResolution;
  inline bool operator!=(const PortStatus& rhs) const {
    return std::tie(portId, connected, active, signalStatus, detectedResolution) != std::tie(rhs.portId, rhs.connected, rhs.active, rhs.signalStatus, rhs.detectedResolution);
  }
  inline bool operator<(const PortStatus& rhs) const {
    return std::tie(portId, connected, active, signalStatus, detectedResolution) < std::tie(rhs.portId, rhs.connected, rhs.active, rhs.signalStatus, rhs.detectedResolution);
  }
  inline bool operator<=(const PortStatus& rhs) const {
    return std::tie(portId, connected, active, signalStatus, detectedResolution) <= std::tie(rhs.portId, rhs.connected, rhs.active, rhs.signalStatus, rhs.detectedResolution);
  }
  inline bool operator==(const PortStatus& rhs) const {
    return std::tie(portId, connected, active, signalStatus, detectedResolution) == std::tie(rhs.portId, rhs.connected, rhs.active, rhs.signalStatus, rhs.detectedResolution);
  }
  inline bool operator>(const PortStatus& rhs) const {
    return std::tie(portId, connected, active, signalStatus, detectedResolution) > std::tie(rhs.portId, rhs.connected, rhs.active, rhs.signalStatus, rhs.detectedResolution);
  }
  inline bool operator>=(const PortStatus& rhs) const {
    return std::tie(portId, connected, active, signalStatus, detectedResolution) >= std::tie(rhs.portId, rhs.connected, rhs.active, rhs.signalStatus, rhs.detectedResolution);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.PortStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PortStatus{";
    os << "portId: " << ::android::internal::ToString(portId);
    os << ", connected: " << ::android::internal::ToString(connected);
    os << ", active: " << ::android::internal::ToString(active);
    os << ", signalStatus: " << ::android::internal::ToString(signalStatus);
    os << ", detectedResolution: " << ::android::internal::ToString(detectedResolution);
    os << "}";
    return os.str();
  }
};  // class PortStatus
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
