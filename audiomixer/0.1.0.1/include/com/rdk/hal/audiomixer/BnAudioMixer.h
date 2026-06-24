#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioMixer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioMixer : public ::android::BnInterface<IAudioMixer> {
public:
  static constexpr uint32_t TRANSACTION_getAudioOutputPortIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getAudioOutputPort = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_registerListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_unregisterListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getCurrentSourceCodecs = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getInputRouting = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioMixer();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioMixer

class IAudioMixerDelegator : public BnAudioMixer {
public:
  explicit IAudioMixerDelegator(::android::sp<IAudioMixer> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getAudioOutputPortIds(::std::vector<int32_t>* _aidl_return) override {
    return _aidl_delegate->getAudioOutputPortIds(_aidl_return);
  }
  ::android::binder::Status getAudioOutputPort(int32_t id, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPort>* _aidl_return) override {
    return _aidl_delegate->getAudioOutputPort(id, _aidl_return);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::Property property, ::com::rdk::hal::PropertyValue* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status open(bool secure, const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& audioMixerEventListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>* _aidl_return) override {
    return _aidl_delegate->open(secure, audioMixerEventListener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>& audioMixerController, bool* _aidl_return) override {
    return _aidl_delegate->close(audioMixerController, _aidl_return);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& listener) override {
    return _aidl_delegate->registerListener(listener);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& listener) override {
    return _aidl_delegate->unregisterListener(listener);
  }
  ::android::binder::Status getCurrentSourceCodecs(::std::vector<::com::rdk::hal::audiodecoder::Codec>* _aidl_return) override {
    return _aidl_delegate->getCurrentSourceCodecs(_aidl_return);
  }
  ::android::binder::Status getInputRouting(::std::vector<::com::rdk::hal::audiomixer::InputRouting>* _aidl_return) override {
    return _aidl_delegate->getInputRouting(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioMixer::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioMixer> _aidl_delegate;
};  // class IAudioMixerDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
