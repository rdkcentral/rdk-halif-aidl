#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/Channel.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class AudioCapturePcmInfo : public ::android::Parcelable {
public:
  int32_t bitsPerSample = 0;
  int32_t containerBitsPerSample = 0;
  bool isSigned = false;
  bool isLittleEndian = false;
  ::std::vector<::com::rdk::hal::audiomixer::Channel> channelMap;
  inline bool operator!=(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) != std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator<(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) < std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator<=(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) <= std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator==(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) == std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator>(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) > std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator>=(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) >= std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.AudioCapturePcmInfo");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "AudioCapturePcmInfo{";
    os << "bitsPerSample: " << ::android::internal::ToString(bitsPerSample);
    os << ", containerBitsPerSample: " << ::android::internal::ToString(containerBitsPerSample);
    os << ", isSigned: " << ::android::internal::ToString(isSigned);
    os << ", isLittleEndian: " << ::android::internal::ToString(isLittleEndian);
    os << ", channelMap: " << ::android::internal::ToString(channelMap);
    os << "}";
    return os.str();
  }
};  // class AudioCapturePcmInfo
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
