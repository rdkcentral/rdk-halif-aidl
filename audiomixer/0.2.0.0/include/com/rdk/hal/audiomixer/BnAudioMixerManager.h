#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioMixerManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioMixerManager : public ::android::BnInterface<IAudioMixerManager> {
public:
  static constexpr uint32_t TRANSACTION_getAudioMixerIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getAudioMixer = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioMixerManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioMixerManager

class IAudioMixerManagerDelegator : public BnAudioMixerManager {
public:
  explicit IAudioMixerManagerDelegator(::android::sp<IAudioMixerManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getAudioMixerIds(::std::vector<::com::rdk::hal::audiomixer::IAudioMixer::Id>* _aidl_return) override {
    return _aidl_delegate->getAudioMixerIds(_aidl_return);
  }
  ::android::binder::Status getAudioMixer(::com::rdk::hal::audiomixer::IAudioMixer::Id id, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixer>* _aidl_return) override {
    return _aidl_delegate->getAudioMixer(id, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioMixerManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioMixerManager> _aidl_delegate;
};  // class IAudioMixerManagerDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
