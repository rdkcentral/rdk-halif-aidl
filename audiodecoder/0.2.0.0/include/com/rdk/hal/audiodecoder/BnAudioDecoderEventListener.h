#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class BnAudioDecoderEventListener : public ::android::BnInterface<IAudioDecoderEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onDecodeError = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioDecoderEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioDecoderEventListener

class IAudioDecoderEventListenerDelegator : public BnAudioDecoderEventListener {
public:
  explicit IAudioDecoderEventListenerDelegator(::android::sp<IAudioDecoderEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onDecodeError(::com::rdk::hal::audiodecoder::ErrorCode errorCode, int32_t vendorErrorCode) override {
    return _aidl_delegate->onDecodeError(errorCode, vendorErrorCode);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiodecoder::State oldState, ::com::rdk::hal::audiodecoder::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioDecoderEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioDecoderEventListener> _aidl_delegate;
};  // class IAudioDecoderEventListenerDelegator
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
