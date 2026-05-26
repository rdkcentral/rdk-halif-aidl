#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class Port : public ::android::Parcelable {
public:
  ::std::string name;
  ::std::string description;
  inline bool operator!=(const Port& rhs) const {
    return std::tie(name, description) != std::tie(rhs.name, rhs.description);
  }
  inline bool operator<(const Port& rhs) const {
    return std::tie(name, description) < std::tie(rhs.name, rhs.description);
  }
  inline bool operator<=(const Port& rhs) const {
    return std::tie(name, description) <= std::tie(rhs.name, rhs.description);
  }
  inline bool operator==(const Port& rhs) const {
    return std::tie(name, description) == std::tie(rhs.name, rhs.description);
  }
  inline bool operator>(const Port& rhs) const {
    return std::tie(name, description) > std::tie(rhs.name, rhs.description);
  }
  inline bool operator>=(const Port& rhs) const {
    return std::tie(name, description) >= std::tie(rhs.name, rhs.description);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.Port");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Port{";
    os << "name: " << ::android::internal::ToString(name);
    os << ", description: " << ::android::internal::ToString(description);
    os << "}";
    return os.str();
  }
};  // class Port
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
