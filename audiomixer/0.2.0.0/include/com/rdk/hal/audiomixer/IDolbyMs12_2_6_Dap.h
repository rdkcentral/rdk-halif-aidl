#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_DapCapabilities.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_DownmixMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_DrcMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_GeqMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_IeqMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_LevellerMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_LevellerSettings.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_VirtualizerMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_VirtualizerSettings.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IDolbyMs12_2_6_Dap : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DolbyMs12_2_6_Dap)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DapCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status setSurroundDecoderEnabled(bool enabled) = 0;
  virtual ::android::binder::Status getSurroundDecoderEnabled(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setBassEnhancer(int32_t boost) = 0;
  virtual ::android::binder::Status getBassEnhancer(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status setVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode mode, int32_t level) = 0;
  virtual ::android::binder::Status getVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerSettings* _aidl_return) = 0;
  virtual ::android::binder::Status setSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode mode, int32_t boost) = 0;
  virtual ::android::binder::Status getSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerSettings* _aidl_return) = 0;
  virtual ::android::binder::Status setMediaIntelligentSteering(bool enabled) = 0;
  virtual ::android::binder::Status getMediaIntelligentSteering(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setPostGain(float gain) = 0;
  virtual ::android::binder::Status getPostGain(float* _aidl_return) = 0;
  virtual ::android::binder::Status setDialogueEnhancer(int32_t level) = 0;
  virtual ::android::binder::Status getDialogueEnhancer(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status setIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode mode) = 0;
  virtual ::android::binder::Status getIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode* _aidl_return) = 0;
  virtual ::android::binder::Status setGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode mode) = 0;
  virtual ::android::binder::Status getGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode* _aidl_return) = 0;
  virtual ::android::binder::Status setDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode mode) = 0;
  virtual ::android::binder::Status getDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode* _aidl_return) = 0;
  virtual ::android::binder::Status setAtmosLock(bool enabled) = 0;
  virtual ::android::binder::Status getAtmosLock(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode mode) = 0;
  virtual ::android::binder::Status getDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode* _aidl_return) = 0;
  virtual ::android::binder::Status setVolumeModelerEnabled(bool enabled) = 0;
  virtual ::android::binder::Status getVolumeModelerEnabled(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setCenterSpreadingEnabled(bool enabled) = 0;
  virtual ::android::binder::Status getCenterSpreadingEnabled(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setActiveDownmixEnabled(bool enabled) = 0;
  virtual ::android::binder::Status getActiveDownmixEnabled(bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDolbyMs12_2_6_Dap

class IDolbyMs12_2_6_DapDefault : public IDolbyMs12_2_6_Dap {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DapCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSurroundDecoderEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSurroundDecoderEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setBassEnhancer(int32_t /*boost*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getBassEnhancer(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode /*mode*/, int32_t /*level*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerSettings* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode /*mode*/, int32_t /*boost*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerSettings* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setMediaIntelligentSteering(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getMediaIntelligentSteering(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPostGain(float /*gain*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPostGain(float* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setDialogueEnhancer(int32_t /*level*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDialogueEnhancer(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAtmosLock(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAtmosLock(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVolumeModelerEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVolumeModelerEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setCenterSpreadingEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCenterSpreadingEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setActiveDownmixEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getActiveDownmixEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDolbyMs12_2_6_DapDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
