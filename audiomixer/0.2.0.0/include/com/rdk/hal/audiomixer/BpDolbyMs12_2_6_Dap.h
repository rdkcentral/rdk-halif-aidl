#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IDolbyMs12_2_6_Dap.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpDolbyMs12_2_6_Dap : public ::android::BpInterface<IDolbyMs12_2_6_Dap> {
public:
  explicit BpDolbyMs12_2_6_Dap(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDolbyMs12_2_6_Dap() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DapCapabilities* _aidl_return) override;
  ::android::binder::Status setSurroundDecoderEnabled(bool enabled) override;
  ::android::binder::Status getSurroundDecoderEnabled(bool* _aidl_return) override;
  ::android::binder::Status setBassEnhancer(int32_t boost) override;
  ::android::binder::Status getBassEnhancer(int32_t* _aidl_return) override;
  ::android::binder::Status setVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode mode, int32_t level) override;
  ::android::binder::Status getVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerSettings* _aidl_return) override;
  ::android::binder::Status setSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode mode, int32_t boost) override;
  ::android::binder::Status getSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerSettings* _aidl_return) override;
  ::android::binder::Status setMediaIntelligentSteering(bool enabled) override;
  ::android::binder::Status getMediaIntelligentSteering(bool* _aidl_return) override;
  ::android::binder::Status setPostGain(float gain) override;
  ::android::binder::Status getPostGain(float* _aidl_return) override;
  ::android::binder::Status setDialogueEnhancer(int32_t level) override;
  ::android::binder::Status getDialogueEnhancer(int32_t* _aidl_return) override;
  ::android::binder::Status setIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode mode) override;
  ::android::binder::Status getIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode* _aidl_return) override;
  ::android::binder::Status setGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode mode) override;
  ::android::binder::Status getGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode* _aidl_return) override;
  ::android::binder::Status setDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode mode) override;
  ::android::binder::Status getDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode* _aidl_return) override;
  ::android::binder::Status setAtmosLock(bool enabled) override;
  ::android::binder::Status getAtmosLock(bool* _aidl_return) override;
  ::android::binder::Status setDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode mode) override;
  ::android::binder::Status getDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode* _aidl_return) override;
  ::android::binder::Status setVolumeModelerEnabled(bool enabled) override;
  ::android::binder::Status getVolumeModelerEnabled(bool* _aidl_return) override;
  ::android::binder::Status setCenterSpreadingEnabled(bool enabled) override;
  ::android::binder::Status getCenterSpreadingEnabled(bool* _aidl_return) override;
  ::android::binder::Status setActiveDownmixEnabled(bool enabled) override;
  ::android::binder::Status getActiveDownmixEnabled(bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDolbyMs12_2_6_Dap
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
