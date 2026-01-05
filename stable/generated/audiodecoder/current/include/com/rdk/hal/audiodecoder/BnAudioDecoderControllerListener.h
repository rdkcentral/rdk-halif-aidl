#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class BnAudioDecoderControllerListener : public ::android::BnInterface<IAudioDecoderControllerListener> {
public:
  static constexpr uint32_t TRANSACTION_onFrameOutput = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioDecoderControllerListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioDecoderControllerListener

class IAudioDecoderControllerListenerDelegator : public BnAudioDecoderControllerListener {
public:
  explicit IAudioDecoderControllerListenerDelegator(::android::sp<IAudioDecoderControllerListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata>& metadata) override {
    return _aidl_delegate->onFrameOutput(nsPresentationTime, frameBufferHandle, metadata);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioDecoderControllerListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioDecoderControllerListener> _aidl_delegate;
};  // class IAudioDecoderControllerListenerDelegator
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
