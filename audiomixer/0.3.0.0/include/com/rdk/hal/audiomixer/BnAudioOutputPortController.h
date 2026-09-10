#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortController.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioOutputPortController : public ::android::BnInterface<IAudioOutputPortController> {
public:
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getDolbyMs12_2_6_Dap = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getAudioCapture = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioOutputPortController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioOutputPortController

class IAudioOutputPortControllerDelegator : public BnAudioOutputPortController {
public:
  explicit IAudioOutputPortControllerDelegator(::android::sp<IAudioOutputPortController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& value, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(property, value, _aidl_return);
  }
  ::android::binder::Status getDolbyMs12_2_6_Dap(::android::sp<::com::rdk::hal::audiomixer::IDolbyMs12_2_6_Dap>* _aidl_return) override {
    return _aidl_delegate->getDolbyMs12_2_6_Dap(_aidl_return);
  }
  ::android::binder::Status getAudioCapture(const ::android::sp<::com::rdk::hal::audiomixer::IAudioCaptureListener>& audioCaptureListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioCapture>* _aidl_return) override {
    return _aidl_delegate->getAudioCapture(audioCaptureListener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioOutputPortController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioOutputPortController> _aidl_delegate;
};  // class IAudioOutputPortControllerDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
