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
namespace videodecoder {
class InputBufferMetadata : public ::android::Parcelable {
public:
  int64_t nsPresentationTime = 0L;
  bool discontinuity = false;
  inline bool operator!=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity) != std::tie(rhs.nsPresentationTime, rhs.discontinuity);
  }
  inline bool operator<(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity) < std::tie(rhs.nsPresentationTime, rhs.discontinuity);
  }
  inline bool operator<=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity) <= std::tie(rhs.nsPresentationTime, rhs.discontinuity);
  }
  inline bool operator==(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity) == std::tie(rhs.nsPresentationTime, rhs.discontinuity);
  }
  inline bool operator>(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity) > std::tie(rhs.nsPresentationTime, rhs.discontinuity);
  }
  inline bool operator>=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity) >= std::tie(rhs.nsPresentationTime, rhs.discontinuity);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.InputBufferMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "InputBufferMetadata{";
    os << "nsPresentationTime: " << ::android::internal::ToString(nsPresentationTime);
    os << ", discontinuity: " << ::android::internal::ToString(discontinuity);
    os << "}";
    return os.str();
  }
};  // class InputBufferMetadata
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
