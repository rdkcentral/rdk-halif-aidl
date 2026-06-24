#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioCaptureListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioCaptureListener : public ::android::BnInterface<IAudioCaptureListener> {
public:
  static constexpr uint32_t TRANSACTION_onDataAvailable = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onStarted = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onStopped = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onError = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioCaptureListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioCaptureListener

class IAudioCaptureListenerDelegator : public BnAudioCaptureListener {
public:
  explicit IAudioCaptureListenerDelegator(::android::sp<IAudioCaptureListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onDataAvailable(int64_t offsetBytes, int32_t lengthBytes, const ::com::rdk::hal::audiomixer::AudioCaptureData& metadata) override {
    return _aidl_delegate->onDataAvailable(offsetBytes, lengthBytes, metadata);
  }
  ::android::binder::Status onStarted() override {
    return _aidl_delegate->onStarted();
  }
  ::android::binder::Status onStopped() override {
    return _aidl_delegate->onStopped();
  }
  ::android::binder::Status onError(::com::rdk::hal::audiomixer::AudioCaptureError error, const ::android::String16& message) override {
    return _aidl_delegate->onError(error, message);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioCaptureListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioCaptureListener> _aidl_delegate;
};  // class IAudioCaptureListenerDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
