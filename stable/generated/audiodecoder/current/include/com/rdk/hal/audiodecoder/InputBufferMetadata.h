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
namespace audiodecoder {
class InputBufferMetadata : public ::android::Parcelable {
public:
  int64_t nsPresentationTime = 0L;
  bool endOfStream = false;
  bool discontinuity = false;
  int32_t trimStartNs = 0;
  int32_t trimEndNs = 0;
  inline bool operator!=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, endOfStream, discontinuity, trimStartNs, trimEndNs) != std::tie(rhs.nsPresentationTime, rhs.endOfStream, rhs.discontinuity, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator<(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, endOfStream, discontinuity, trimStartNs, trimEndNs) < std::tie(rhs.nsPresentationTime, rhs.endOfStream, rhs.discontinuity, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator<=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, endOfStream, discontinuity, trimStartNs, trimEndNs) <= std::tie(rhs.nsPresentationTime, rhs.endOfStream, rhs.discontinuity, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator==(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, endOfStream, discontinuity, trimStartNs, trimEndNs) == std::tie(rhs.nsPresentationTime, rhs.endOfStream, rhs.discontinuity, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator>(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, endOfStream, discontinuity, trimStartNs, trimEndNs) > std::tie(rhs.nsPresentationTime, rhs.endOfStream, rhs.discontinuity, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator>=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, endOfStream, discontinuity, trimStartNs, trimEndNs) >= std::tie(rhs.nsPresentationTime, rhs.endOfStream, rhs.discontinuity, rhs.trimStartNs, rhs.trimEndNs);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiodecoder.InputBufferMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "InputBufferMetadata{";
    os << "nsPresentationTime: " << ::android::internal::ToString(nsPresentationTime);
    os << ", endOfStream: " << ::android::internal::ToString(endOfStream);
    os << ", discontinuity: " << ::android::internal::ToString(discontinuity);
    os << ", trimStartNs: " << ::android::internal::ToString(trimStartNs);
    os << ", trimEndNs: " << ::android::internal::ToString(trimEndNs);
    os << "}";
    return os.str();
  }
};  // class InputBufferMetadata
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
