#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/MixerInput.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class Capabilities : public ::android::Parcelable {
public:
  bool supportsSecure = false;
  ::std::vector<::com::rdk::hal::audiomixer::MixerInput> inputs;
  ::std::optional<::android::String16> name;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportsSecure, inputs, name) != std::tie(rhs.supportsSecure, rhs.inputs, rhs.name);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportsSecure, inputs, name) < std::tie(rhs.supportsSecure, rhs.inputs, rhs.name);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportsSecure, inputs, name) <= std::tie(rhs.supportsSecure, rhs.inputs, rhs.name);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportsSecure, inputs, name) == std::tie(rhs.supportsSecure, rhs.inputs, rhs.name);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportsSecure, inputs, name) > std::tie(rhs.supportsSecure, rhs.inputs, rhs.name);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportsSecure, inputs, name) >= std::tie(rhs.supportsSecure, rhs.inputs, rhs.name);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportsSecure: " << ::android::internal::ToString(supportsSecure);
    os << ", inputs: " << ::android::internal::ToString(inputs);
    os << ", name: " << ::android::internal::ToString(name);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
