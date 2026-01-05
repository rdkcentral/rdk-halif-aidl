#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/CodecCapabilities.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class Capabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::videodecoder::CodecCapabilities> supportedCodecs;
  ::std::vector<::com::rdk::hal::videodecoder::DynamicRange> supportedDynamicRanges;
  bool supportsSecure = false;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportsSecure) != std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportsSecure);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportsSecure) < std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportsSecure);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportsSecure) <= std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportsSecure);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportsSecure) == std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportsSecure);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportsSecure) > std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportsSecure);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedCodecs, supportedDynamicRanges, supportsSecure) >= std::tie(rhs.supportedCodecs, rhs.supportedDynamicRanges, rhs.supportsSecure);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedCodecs: " << ::android::internal::ToString(supportedCodecs);
    os << ", supportedDynamicRanges: " << ::android::internal::ToString(supportedDynamicRanges);
    os << ", supportsSecure: " << ::android::internal::ToString(supportsSecure);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
