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
// @aidl-doc
/**
 * @brief Capability flags for IDolbyMs12_2_6_Dap runtime command support.
 *
 * Each field indicates whether the corresponding set function in
 * IDolbyMs12_2_6_Dap is supported for the current output port.
 */
class DolbyMs12_2_6_DapCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Whether `setSurroundDecoderEnabled()` is supported. */
  bool supportsSurroundDecoderEnabled = false;
  // @aidl-doc
  /** Whether `setBassEnhancer()` is supported. */
  bool supportsBassEnhancer = false;
  // @aidl-doc
  /** Whether `setVolumeLeveller()` is supported. */
  bool supportsVolumeLeveller = false;
  // @aidl-doc
  /** Whether `setSurroundVirtualizer()` is supported. */
  bool supportsSurroundVirtualizer = false;
  // @aidl-doc
  /** Whether `setMediaIntelligentSteering()` is supported. */
  bool supportsMediaIntelligentSteering = false;
  // @aidl-doc
  /** Whether `setPostGain()` is supported. */
  bool supportsPostGain = false;
  // @aidl-doc
  /** Whether `setDialogueEnhancer()` is supported. */
  bool supportsDialogueEnhancer = false;
  // @aidl-doc
  /** Whether `setIntelligentEqualizerMode()` is supported. */
  bool supportsIntelligentEqualizerMode = false;
  // @aidl-doc
  /** Whether `setGraphicEqualizerMode()` is supported. */
  bool supportsGraphicEqualizerMode = false;
  // @aidl-doc
  /** Whether `setDynamicRangeControlMode()` is supported. */
  bool supportsDynamicRangeControlMode = false;
  // @aidl-doc
  /** Whether `setAtmosLock()` is supported. */
  bool supportsAtmosLock = false;
  // @aidl-doc
  /** Whether `setDownmixMode()` is supported. */
  bool supportsDownmixMode = false;
  // @aidl-doc
  /** Whether `setVolumeModelerEnabled()` is supported. */
  bool supportsVolumeModelerEnabled = false;
  // @aidl-doc
  /** Whether `setCenterSpreadingEnabled()` is supported. */
  bool supportsCenterSpreadingEnabled = false;
  // @aidl-doc
  /** Whether `setActiveDownmixEnabled()` is supported. */
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
