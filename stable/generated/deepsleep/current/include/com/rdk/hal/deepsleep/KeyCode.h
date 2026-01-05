#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
class KeyCode : public ::android::Parcelable {
public:
  int32_t keyCode = 0;
  inline bool operator!=(const KeyCode& rhs) const {
    return std::tie(keyCode) != std::tie(rhs.keyCode);
  }
  inline bool operator<(const KeyCode& rhs) const {
    return std::tie(keyCode) < std::tie(rhs.keyCode);
  }
  inline bool operator<=(const KeyCode& rhs) const {
    return std::tie(keyCode) <= std::tie(rhs.keyCode);
  }
  inline bool operator==(const KeyCode& rhs) const {
    return std::tie(keyCode) == std::tie(rhs.keyCode);
  }
  inline bool operator>(const KeyCode& rhs) const {
    return std::tie(keyCode) > std::tie(rhs.keyCode);
  }
  inline bool operator>=(const KeyCode& rhs) const {
    return std::tie(keyCode) >= std::tie(rhs.keyCode);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.deepsleep.KeyCode");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "KeyCode{";
    os << "keyCode: " << ::android::internal::ToString(keyCode);
    os << "}";
    return os.str();
  }
};  // class KeyCode
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
