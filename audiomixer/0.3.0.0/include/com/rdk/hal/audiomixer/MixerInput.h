#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiomixer/ContentType.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class MixerInput : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::audiomixer::ContentType> supportedContentTypes;
  ::std::vector<::com::rdk::hal::audiodecoder::Codec> supportedCodecs;
  ::std::optional<::android::String16> name;
  inline bool operator!=(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) != std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator<(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) < std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator<=(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) <= std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator==(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) == std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator>(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) > std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator>=(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) >= std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.MixerInput");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "MixerInput{";
    os << "supportedContentTypes: " << ::android::internal::ToString(supportedContentTypes);
    os << ", supportedCodecs: " << ::android::internal::ToString(supportedCodecs);
    os << ", name: " << ::android::internal::ToString(name);
    os << "}";
    return os.str();
  }
};  // class MixerInput
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
