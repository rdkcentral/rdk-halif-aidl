#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class DolbyMs12_2_6_DapCapabilities : public ::android::Parcelable {
public:
  bool supportsSurroundDecoderEnabled = false;
  bool supportsBassEnhancer = false;
  bool supportsVolumeLeveller = false;
  bool supportsSurroundVirtualizer = false;
  bool supportsMediaIntelligentSteering = false;
  bool supportsPostGain = false;
  bool supportsDialogueEnhancer = false;
  bool supportsIntelligentEqualizerMode = false;
  bool supportsGraphicEqualizerMode = false;
  bool supportsDynamicRangeControlMode = false;
  bool supportsAtmosLock = false;
  bool supportsDownmixMode = false;
  bool supportsVolumeModelerEnabled = false;
  bool supportsCenterSpreadingEnabled = false;
  bool supportsActiveDownmixEnabled = false;
  inline bool operator!=(const DolbyMs12_2_6_DapCapabilities& rhs) const {
    return std::tie(supportsSurroundDecoderEnabled, supportsBassEnhancer, supportsVolumeLeveller, supportsSurroundVirtualizer, supportsMediaIntelligentSteering, supportsPostGain, supportsDialogueEnhancer, supportsIntelligentEqualizerMode, supportsGraphicEqualizerMode, supportsDynamicRangeControlMode, supportsAtmosLock, supportsDownmixMode, supportsVolumeModelerEnabled, supportsCenterSpreadingEnabled, supportsActiveDownmixEnabled) != std::tie(rhs.supportsSurroundDecoderEnabled, rhs.supportsBassEnhancer, rhs.supportsVolumeLeveller, rhs.supportsSurroundVirtualizer, rhs.supportsMediaIntelligentSteering, rhs.supportsPostGain, rhs.supportsDialogueEnhancer, rhs.supportsIntelligentEqualizerMode, rhs.supportsGraphicEqualizerMode, rhs.supportsDynamicRangeControlMode, rhs.supportsAtmosLock, rhs.supportsDownmixMode, rhs.supportsVolumeModelerEnabled, rhs.supportsCenterSpreadingEnabled, rhs.supportsActiveDownmixEnabled);
  }
  inline bool operator<(const DolbyMs12_2_6_DapCapabilities& rhs) const {
    return std::tie(supportsSurroundDecoderEnabled, supportsBassEnhancer, supportsVolumeLeveller, supportsSurroundVirtualizer, supportsMediaIntelligentSteering, supportsPostGain, supportsDialogueEnhancer, supportsIntelligentEqualizerMode, supportsGraphicEqualizerMode, supportsDynamicRangeControlMode, supportsAtmosLock, supportsDownmixMode, supportsVolumeModelerEnabled, supportsCenterSpreadingEnabled, supportsActiveDownmixEnabled) < std::tie(rhs.supportsSurroundDecoderEnabled, rhs.supportsBassEnhancer, rhs.supportsVolumeLeveller, rhs.supportsSurroundVirtualizer, rhs.supportsMediaIntelligentSteering, rhs.supportsPostGain, rhs.supportsDialogueEnhancer, rhs.supportsIntelligentEqualizerMode, rhs.supportsGraphicEqualizerMode, rhs.supportsDynamicRangeControlMode, rhs.supportsAtmosLock, rhs.supportsDownmixMode, rhs.supportsVolumeModelerEnabled, rhs.supportsCenterSpreadingEnabled, rhs.supportsActiveDownmixEnabled);
  }
  inline bool operator<=(const DolbyMs12_2_6_DapCapabilities& rhs) const {
    return std::tie(supportsSurroundDecoderEnabled, supportsBassEnhancer, supportsVolumeLeveller, supportsSurroundVirtualizer, supportsMediaIntelligentSteering, supportsPostGain, supportsDialogueEnhancer, supportsIntelligentEqualizerMode, supportsGraphicEqualizerMode, supportsDynamicRangeControlMode, supportsAtmosLock, supportsDownmixMode, supportsVolumeModelerEnabled, supportsCenterSpreadingEnabled, supportsActiveDownmixEnabled) <= std::tie(rhs.supportsSurroundDecoderEnabled, rhs.supportsBassEnhancer, rhs.supportsVolumeLeveller, rhs.supportsSurroundVirtualizer, rhs.supportsMediaIntelligentSteering, rhs.supportsPostGain, rhs.supportsDialogueEnhancer, rhs.supportsIntelligentEqualizerMode, rhs.supportsGraphicEqualizerMode, rhs.supportsDynamicRangeControlMode, rhs.supportsAtmosLock, rhs.supportsDownmixMode, rhs.supportsVolumeModelerEnabled, rhs.supportsCenterSpreadingEnabled, rhs.supportsActiveDownmixEnabled);
  }
  inline bool operator==(const DolbyMs12_2_6_DapCapabilities& rhs) const {
    return std::tie(supportsSurroundDecoderEnabled, supportsBassEnhancer, supportsVolumeLeveller, supportsSurroundVirtualizer, supportsMediaIntelligentSteering, supportsPostGain, supportsDialogueEnhancer, supportsIntelligentEqualizerMode, supportsGraphicEqualizerMode, supportsDynamicRangeControlMode, supportsAtmosLock, supportsDownmixMode, supportsVolumeModelerEnabled, supportsCenterSpreadingEnabled, supportsActiveDownmixEnabled) == std::tie(rhs.supportsSurroundDecoderEnabled, rhs.supportsBassEnhancer, rhs.supportsVolumeLeveller, rhs.supportsSurroundVirtualizer, rhs.supportsMediaIntelligentSteering, rhs.supportsPostGain, rhs.supportsDialogueEnhancer, rhs.supportsIntelligentEqualizerMode, rhs.supportsGraphicEqualizerMode, rhs.supportsDynamicRangeControlMode, rhs.supportsAtmosLock, rhs.supportsDownmixMode, rhs.supportsVolumeModelerEnabled, rhs.supportsCenterSpreadingEnabled, rhs.supportsActiveDownmixEnabled);
  }
  inline bool operator>(const DolbyMs12_2_6_DapCapabilities& rhs) const {
    return std::tie(supportsSurroundDecoderEnabled, supportsBassEnhancer, supportsVolumeLeveller, supportsSurroundVirtualizer, supportsMediaIntelligentSteering, supportsPostGain, supportsDialogueEnhancer, supportsIntelligentEqualizerMode, supportsGraphicEqualizerMode, supportsDynamicRangeControlMode, supportsAtmosLock, supportsDownmixMode, supportsVolumeModelerEnabled, supportsCenterSpreadingEnabled, supportsActiveDownmixEnabled) > std::tie(rhs.supportsSurroundDecoderEnabled, rhs.supportsBassEnhancer, rhs.supportsVolumeLeveller, rhs.supportsSurroundVirtualizer, rhs.supportsMediaIntelligentSteering, rhs.supportsPostGain, rhs.supportsDialogueEnhancer, rhs.supportsIntelligentEqualizerMode, rhs.supportsGraphicEqualizerMode, rhs.supportsDynamicRangeControlMode, rhs.supportsAtmosLock, rhs.supportsDownmixMode, rhs.supportsVolumeModelerEnabled, rhs.supportsCenterSpreadingEnabled, rhs.supportsActiveDownmixEnabled);
  }
  inline bool operator>=(const DolbyMs12_2_6_DapCapabilities& rhs) const {
    return std::tie(supportsSurroundDecoderEnabled, supportsBassEnhancer, supportsVolumeLeveller, supportsSurroundVirtualizer, supportsMediaIntelligentSteering, supportsPostGain, supportsDialogueEnhancer, supportsIntelligentEqualizerMode, supportsGraphicEqualizerMode, supportsDynamicRangeControlMode, supportsAtmosLock, supportsDownmixMode, supportsVolumeModelerEnabled, supportsCenterSpreadingEnabled, supportsActiveDownmixEnabled) >= std::tie(rhs.supportsSurroundDecoderEnabled, rhs.supportsBassEnhancer, rhs.supportsVolumeLeveller, rhs.supportsSurroundVirtualizer, rhs.supportsMediaIntelligentSteering, rhs.supportsPostGain, rhs.supportsDialogueEnhancer, rhs.supportsIntelligentEqualizerMode, rhs.supportsGraphicEqualizerMode, rhs.supportsDynamicRangeControlMode, rhs.supportsAtmosLock, rhs.supportsDownmixMode, rhs.supportsVolumeModelerEnabled, rhs.supportsCenterSpreadingEnabled, rhs.supportsActiveDownmixEnabled);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.DolbyMs12_2_6_DapCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DolbyMs12_2_6_DapCapabilities{";
    os << "supportsSurroundDecoderEnabled: " << ::android::internal::ToString(supportsSurroundDecoderEnabled);
    os << ", supportsBassEnhancer: " << ::android::internal::ToString(supportsBassEnhancer);
    os << ", supportsVolumeLeveller: " << ::android::internal::ToString(supportsVolumeLeveller);
    os << ", supportsSurroundVirtualizer: " << ::android::internal::ToString(supportsSurroundVirtualizer);
    os << ", supportsMediaIntelligentSteering: " << ::android::internal::ToString(supportsMediaIntelligentSteering);
    os << ", supportsPostGain: " << ::android::internal::ToString(supportsPostGain);
    os << ", supportsDialogueEnhancer: " << ::android::internal::ToString(supportsDialogueEnhancer);
    os << ", supportsIntelligentEqualizerMode: " << ::android::internal::ToString(supportsIntelligentEqualizerMode);
    os << ", supportsGraphicEqualizerMode: " << ::android::internal::ToString(supportsGraphicEqualizerMode);
    os << ", supportsDynamicRangeControlMode: " << ::android::internal::ToString(supportsDynamicRangeControlMode);
    os << ", supportsAtmosLock: " << ::android::internal::ToString(supportsAtmosLock);
    os << ", supportsDownmixMode: " << ::android::internal::ToString(supportsDownmixMode);
    os << ", supportsVolumeModelerEnabled: " << ::android::internal::ToString(supportsVolumeModelerEnabled);
    os << ", supportsCenterSpreadingEnabled: " << ::android::internal::ToString(supportsCenterSpreadingEnabled);
    os << ", supportsActiveDownmixEnabled: " << ::android::internal::ToString(supportsActiveDownmixEnabled);
    os << "}";
    return os.str();
  }
};  // class DolbyMs12_2_6_DapCapabilities
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
