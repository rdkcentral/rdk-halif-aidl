#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoder.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class BnAudioDecoder : public ::android::BnInterface<IAudioDecoder> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioDecoder();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioDecoder

class IAudioDecoderDelegator : public BnAudioDecoder {
public:
  explicit IAudioDecoderDelegator(::android::sp<IAudioDecoder> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::audiodecoder::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiodecoder::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status getState(::com::rdk::hal::audiodecoder::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status open(::com::rdk::hal::audiodecoder::Codec codec, bool secure, const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderControllerListener>& audioDecoderControllerListener, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>* _aidl_return) override {
    return _aidl_delegate->open(codec, secure, audioDecoderControllerListener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>& audioDecoderController, bool* _aidl_return) override {
    return _aidl_delegate->close(audioDecoderController, _aidl_return);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& audioDecoderEventListener, bool* _aidl_return) override {
    return _aidl_delegate->registerEventListener(audioDecoderEventListener, _aidl_return);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& audioDecoderEventListener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterEventListener(audioDecoderEventListener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioDecoder::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioDecoder> _aidl_delegate;
};  // class IAudioDecoderDelegator
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
