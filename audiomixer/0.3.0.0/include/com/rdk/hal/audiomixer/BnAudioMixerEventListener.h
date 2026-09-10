#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioMixerEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioMixerEventListener : public ::android::BnInterface<IAudioMixerEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onInputCodecChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onError = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioMixerEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioMixerEventListener

class IAudioMixerEventListenerDelegator : public BnAudioMixerEventListener {
public:
  explicit IAudioMixerEventListenerDelegator(::android::sp<IAudioMixerEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onInputCodecChanged(int32_t audioMixerInputIndex, ::com::rdk::hal::audiodecoder::Codec codec, ::com::rdk::hal::audiomixer::ContentType contentType) override {
    return _aidl_delegate->onInputCodecChanged(audioMixerInputIndex, codec, contentType);
  }
  ::android::binder::Status onError(int32_t errorCode, const ::android::String16& message) override {
    return _aidl_delegate->onError(errorCode, message);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State oldState, ::com::rdk::hal::audiomixer::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioMixerEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioMixerEventListener> _aidl_delegate;
};  // class IAudioMixerEventListenerDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
