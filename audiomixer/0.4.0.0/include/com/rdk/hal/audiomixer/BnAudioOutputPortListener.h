#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioOutputPortListener : public ::android::BnInterface<IAudioOutputPortListener> {
public:
  static constexpr uint32_t TRANSACTION_onPropertyChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioOutputPortListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioOutputPortListener

class IAudioOutputPortListenerDelegator : public BnAudioOutputPortListener {
public:
  explicit IAudioOutputPortListenerDelegator(::android::sp<IAudioOutputPortListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onPropertyChanged(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& newValue) override {
    return _aidl_delegate->onPropertyChanged(property, newValue);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioOutputPortListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioOutputPortListener> _aidl_delegate;
};  // class IAudioOutputPortListenerDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
