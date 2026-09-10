#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/ChannelType.h>
#include <com/rdk/hal/audiodecoder/PCMFormat.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class PCMMetadata : public ::android::Parcelable {
public:
  int32_t numChannels = 0;
  ::std::vector<::com::rdk::hal::audiodecoder::ChannelType> channelTypes;
  int32_t sampleRate = 0;
  ::com::rdk::hal::audiodecoder::PCMFormat format = ::com::rdk::hal::audiodecoder::PCMFormat(0);
  bool planarFormat = false;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) != std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator<(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) < std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator<=(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) <= std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator==(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) == std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator>(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) > std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator>=(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) >= std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiodecoder.PCMMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PCMMetadata{";
    os << "numChannels: " << ::android::internal::ToString(numChannels);
    os << ", channelTypes: " << ::android::internal::ToString(channelTypes);
    os << ", sampleRate: " << ::android::internal::ToString(sampleRate);
    os << ", format: " << ::android::internal::ToString(format);
    os << ", planarFormat: " << ::android::internal::ToString(planarFormat);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class PCMMetadata
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
