#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiosink/IAudioSink.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class BnAudioSink : public ::android::BnInterface<IAudioSink> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_registerEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_unregisterEventListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioSink();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioSink

class IAudioSinkDelegator : public BnAudioSink {
public:
  explicit IAudioSinkDelegator(::android::sp<IAudioSink> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::audiosink::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiosink::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiosink::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(property, propertyValue, _aidl_return);
  }
  ::android::binder::Status getState(::com::rdk::hal::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status open(::com::rdk::hal::audiosink::ContentType contentType, const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkControllerListener>& audioSinkControllerListener, ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>* _aidl_return) override {
    return _aidl_delegate->open(contentType, audioSinkControllerListener, _aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>& audioSinkController, bool* _aidl_return) override {
    return _aidl_delegate->close(audioSinkController, _aidl_return);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& audioSinkEventListener, bool* _aidl_return) override {
    return _aidl_delegate->registerEventListener(audioSinkEventListener, _aidl_return);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& audioSinkEventListener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterEventListener(audioSinkEventListener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioSink::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioSink> _aidl_delegate;
};  // class IAudioSinkDelegator
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
