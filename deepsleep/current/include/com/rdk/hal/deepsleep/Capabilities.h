#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/deepsleep/WakeUpTrigger.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
class Capabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger> supportedTriggers;
  ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger> preconfiguredTriggers;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedTriggers, preconfiguredTriggers) != std::tie(rhs.supportedTriggers, rhs.preconfiguredTriggers);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedTriggers, preconfiguredTriggers) < std::tie(rhs.supportedTriggers, rhs.preconfiguredTriggers);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedTriggers, preconfiguredTriggers) <= std::tie(rhs.supportedTriggers, rhs.preconfiguredTriggers);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedTriggers, preconfiguredTriggers) == std::tie(rhs.supportedTriggers, rhs.preconfiguredTriggers);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedTriggers, preconfiguredTriggers) > std::tie(rhs.supportedTriggers, rhs.preconfiguredTriggers);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedTriggers, preconfiguredTriggers) >= std::tie(rhs.supportedTriggers, rhs.preconfiguredTriggers);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.deepsleep.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedTriggers: " << ::android::internal::ToString(supportedTriggers);
    os << ", preconfiguredTriggers: " << ::android::internal::ToString(preconfiguredTriggers);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
