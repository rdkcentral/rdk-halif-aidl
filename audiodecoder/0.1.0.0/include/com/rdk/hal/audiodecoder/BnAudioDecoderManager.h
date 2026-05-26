#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class BnAudioDecoderManager : public ::android::BnInterface<IAudioDecoderManager> {
public:
  static constexpr uint32_t TRANSACTION_getAudioDecoderIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getAudioDecoder = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioDecoderManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioDecoderManager

class IAudioDecoderManagerDelegator : public BnAudioDecoderManager {
public:
  explicit IAudioDecoderManagerDelegator(::android::sp<IAudioDecoderManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getAudioDecoderIds(::std::vector<::com::rdk::hal::audiodecoder::IAudioDecoder::Id>* _aidl_return) override {
    return _aidl_delegate->getAudioDecoderIds(_aidl_return);
  }
  ::android::binder::Status getAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& decoderResourceId, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoder>* _aidl_return) override {
    return _aidl_delegate->getAudioDecoder(decoderResourceId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioDecoderManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioDecoderManager> _aidl_delegate;
};  // class IAudioDecoderManagerDelegator
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
