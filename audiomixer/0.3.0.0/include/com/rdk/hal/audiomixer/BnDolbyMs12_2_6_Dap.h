#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IDolbyMs12_2_6_Dap.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnDolbyMs12_2_6_Dap : public ::android::BnInterface<IDolbyMs12_2_6_Dap> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_setSurroundDecoderEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getSurroundDecoderEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_setBassEnhancer = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getBassEnhancer = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_setVolumeLeveller = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getVolumeLeveller = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_setSurroundVirtualizer = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getSurroundVirtualizer = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_setMediaIntelligentSteering = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getMediaIntelligentSteering = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_setPostGain = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_getPostGain = ::android::IBinder::FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_setDialogueEnhancer = ::android::IBinder::FIRST_CALL_TRANSACTION + 13;
  static constexpr uint32_t TRANSACTION_getDialogueEnhancer = ::android::IBinder::FIRST_CALL_TRANSACTION + 14;
  static constexpr uint32_t TRANSACTION_setIntelligentEqualizerMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 15;
  static constexpr uint32_t TRANSACTION_getIntelligentEqualizerMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 16;
  static constexpr uint32_t TRANSACTION_setGraphicEqualizerMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 17;
  static constexpr uint32_t TRANSACTION_getGraphicEqualizerMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 18;
  static constexpr uint32_t TRANSACTION_setDynamicRangeControlMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 19;
  static constexpr uint32_t TRANSACTION_getDynamicRangeControlMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 20;
  static constexpr uint32_t TRANSACTION_setAtmosLock = ::android::IBinder::FIRST_CALL_TRANSACTION + 21;
  static constexpr uint32_t TRANSACTION_getAtmosLock = ::android::IBinder::FIRST_CALL_TRANSACTION + 22;
  static constexpr uint32_t TRANSACTION_setDownmixMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 23;
  static constexpr uint32_t TRANSACTION_getDownmixMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 24;
  static constexpr uint32_t TRANSACTION_setVolumeModelerEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 25;
  static constexpr uint32_t TRANSACTION_getVolumeModelerEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 26;
  static constexpr uint32_t TRANSACTION_setCenterSpreadingEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 27;
  static constexpr uint32_t TRANSACTION_getCenterSpreadingEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 28;
  static constexpr uint32_t TRANSACTION_setActiveDownmixEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 29;
  static constexpr uint32_t TRANSACTION_getActiveDownmixEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 30;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDolbyMs12_2_6_Dap();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDolbyMs12_2_6_Dap

class IDolbyMs12_2_6_DapDelegator : public BnDolbyMs12_2_6_Dap {
public:
  explicit IDolbyMs12_2_6_DapDelegator(::android::sp<IDolbyMs12_2_6_Dap> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DapCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status setSurroundDecoderEnabled(bool enabled) override {
    return _aidl_delegate->setSurroundDecoderEnabled(enabled);
  }
  ::android::binder::Status getSurroundDecoderEnabled(bool* _aidl_return) override {
    return _aidl_delegate->getSurroundDecoderEnabled(_aidl_return);
  }
  ::android::binder::Status setBassEnhancer(int32_t boost) override {
    return _aidl_delegate->setBassEnhancer(boost);
  }
  ::android::binder::Status getBassEnhancer(int32_t* _aidl_return) override {
    return _aidl_delegate->getBassEnhancer(_aidl_return);
  }
  ::android::binder::Status setVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode mode, int32_t level) override {
    return _aidl_delegate->setVolumeLeveller(mode, level);
  }
  ::android::binder::Status getVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerSettings* _aidl_return) override {
    return _aidl_delegate->getVolumeLeveller(_aidl_return);
  }
  ::android::binder::Status setSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode mode, int32_t boost) override {
    return _aidl_delegate->setSurroundVirtualizer(mode, boost);
  }
  ::android::binder::Status getSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerSettings* _aidl_return) override {
    return _aidl_delegate->getSurroundVirtualizer(_aidl_return);
  }
  ::android::binder::Status setMediaIntelligentSteering(bool enabled) override {
    return _aidl_delegate->setMediaIntelligentSteering(enabled);
  }
  ::android::binder::Status getMediaIntelligentSteering(bool* _aidl_return) override {
    return _aidl_delegate->getMediaIntelligentSteering(_aidl_return);
  }
  ::android::binder::Status setPostGain(float gain) override {
    return _aidl_delegate->setPostGain(gain);
  }
  ::android::binder::Status getPostGain(float* _aidl_return) override {
    return _aidl_delegate->getPostGain(_aidl_return);
  }
  ::android::binder::Status setDialogueEnhancer(int32_t level) override {
    return _aidl_delegate->setDialogueEnhancer(level);
  }
  ::android::binder::Status getDialogueEnhancer(int32_t* _aidl_return) override {
    return _aidl_delegate->getDialogueEnhancer(_aidl_return);
  }
  ::android::binder::Status setIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode mode) override {
    return _aidl_delegate->setIntelligentEqualizerMode(mode);
  }
  ::android::binder::Status getIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode* _aidl_return) override {
    return _aidl_delegate->getIntelligentEqualizerMode(_aidl_return);
  }
  ::android::binder::Status setGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode mode) override {
    return _aidl_delegate->setGraphicEqualizerMode(mode);
  }
  ::android::binder::Status getGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode* _aidl_return) override {
    return _aidl_delegate->getGraphicEqualizerMode(_aidl_return);
  }
  ::android::binder::Status setDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode mode) override {
    return _aidl_delegate->setDynamicRangeControlMode(mode);
  }
  ::android::binder::Status getDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode* _aidl_return) override {
    return _aidl_delegate->getDynamicRangeControlMode(_aidl_return);
  }
  ::android::binder::Status setAtmosLock(bool enabled) override {
    return _aidl_delegate->setAtmosLock(enabled);
  }
  ::android::binder::Status getAtmosLock(bool* _aidl_return) override {
    return _aidl_delegate->getAtmosLock(_aidl_return);
  }
  ::android::binder::Status setDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode mode) override {
    return _aidl_delegate->setDownmixMode(mode);
  }
  ::android::binder::Status getDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode* _aidl_return) override {
    return _aidl_delegate->getDownmixMode(_aidl_return);
  }
  ::android::binder::Status setVolumeModelerEnabled(bool enabled) override {
    return _aidl_delegate->setVolumeModelerEnabled(enabled);
  }
  ::android::binder::Status getVolumeModelerEnabled(bool* _aidl_return) override {
    return _aidl_delegate->getVolumeModelerEnabled(_aidl_return);
  }
  ::android::binder::Status setCenterSpreadingEnabled(bool enabled) override {
    return _aidl_delegate->setCenterSpreadingEnabled(enabled);
  }
  ::android::binder::Status getCenterSpreadingEnabled(bool* _aidl_return) override {
    return _aidl_delegate->getCenterSpreadingEnabled(_aidl_return);
  }
  ::android::binder::Status setActiveDownmixEnabled(bool enabled) override {
    return _aidl_delegate->setActiveDownmixEnabled(enabled);
  }
  ::android::binder::Status getActiveDownmixEnabled(bool* _aidl_return) override {
    return _aidl_delegate->getActiveDownmixEnabled(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDolbyMs12_2_6_Dap::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDolbyMs12_2_6_Dap> _aidl_delegate;
};  // class IDolbyMs12_2_6_DapDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
