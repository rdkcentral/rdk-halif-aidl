#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPort.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioOutputPort : public ::android::BnInterface<IAudioOutputPort> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_registerListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_unregisterListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioOutputPort();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioOutputPort

class IAudioOutputPortDelegator : public BnAudioOutputPort {
public:
  explicit IAudioOutputPortDelegator(::android::sp<IAudioOutputPort> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::OutputPortCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& value, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(property, value, _aidl_return);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, ::com::rdk::hal::PropertyValue* _aidl_return) override {
    return _aidl_delegate->getProperty(property, _aidl_return);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& listener) override {
    return _aidl_delegate->registerListener(listener);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& listener) override {
    return _aidl_delegate->unregisterListener(listener);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioOutputPort::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioOutputPort> _aidl_delegate;
};  // class IAudioOutputPortDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
