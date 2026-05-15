#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AudioSourceType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class InputRouting : public ::android::Parcelable {
public:
  ::com::rdk::hal::audiomixer::AudioSourceType sourceType = ::com::rdk::hal::audiomixer::AudioSourceType(0);
  int32_t sourceIndex = 0;
  inline bool operator!=(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) != std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator<(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) < std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator<=(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) <= std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator==(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) == std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator>(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) > std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator>=(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) >= std::tie(rhs.sourceType, rhs.sourceIndex);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.InputRouting");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "InputRouting{";
    os << "sourceType: " << ::android::internal::ToString(sourceType);
    os << ", sourceIndex: " << ::android::internal::ToString(sourceIndex);
    os << "}";
    return os.str();
  }
};  // class InputRouting
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
