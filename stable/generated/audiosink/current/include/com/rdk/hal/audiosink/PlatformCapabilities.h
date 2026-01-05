#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/PCMFormat.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class PlatformCapabilities : public ::android::Parcelable {
public:
  bool supportsLowLatency = false;
  int32_t systemMixerSampleRateHz = 0;
  ::com::rdk::hal::audiodecoder::PCMFormat systemMixerPCMFormat = ::com::rdk::hal::audiodecoder::PCMFormat(0);
  bool supportsPlanarFormat = false;
  bool supportsSoCProprietary = false;
  int32_t maxNumChannels = 0;
  bool supportsDolbyAtmos = false;
  inline bool operator!=(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, systemMixerSampleRateHz, systemMixerPCMFormat, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) != std::tie(rhs.supportsLowLatency, rhs.systemMixerSampleRateHz, rhs.systemMixerPCMFormat, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator<(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, systemMixerSampleRateHz, systemMixerPCMFormat, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) < std::tie(rhs.supportsLowLatency, rhs.systemMixerSampleRateHz, rhs.systemMixerPCMFormat, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator<=(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, systemMixerSampleRateHz, systemMixerPCMFormat, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) <= std::tie(rhs.supportsLowLatency, rhs.systemMixerSampleRateHz, rhs.systemMixerPCMFormat, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator==(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, systemMixerSampleRateHz, systemMixerPCMFormat, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) == std::tie(rhs.supportsLowLatency, rhs.systemMixerSampleRateHz, rhs.systemMixerPCMFormat, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator>(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, systemMixerSampleRateHz, systemMixerPCMFormat, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) > std::tie(rhs.supportsLowLatency, rhs.systemMixerSampleRateHz, rhs.systemMixerPCMFormat, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator>=(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, systemMixerSampleRateHz, systemMixerPCMFormat, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) >= std::tie(rhs.supportsLowLatency, rhs.systemMixerSampleRateHz, rhs.systemMixerPCMFormat, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiosink.PlatformCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlatformCapabilities{";
    os << "supportsLowLatency: " << ::android::internal::ToString(supportsLowLatency);
    os << ", systemMixerSampleRateHz: " << ::android::internal::ToString(systemMixerSampleRateHz);
    os << ", systemMixerPCMFormat: " << ::android::internal::ToString(systemMixerPCMFormat);
    os << ", supportsPlanarFormat: " << ::android::internal::ToString(supportsPlanarFormat);
    os << ", supportsSoCProprietary: " << ::android::internal::ToString(supportsSoCProprietary);
    os << ", maxNumChannels: " << ::android::internal::ToString(maxNumChannels);
    os << ", supportsDolbyAtmos: " << ::android::internal::ToString(supportsDolbyAtmos);
    os << "}";
    return os.str();
  }
};  // class PlatformCapabilities
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
