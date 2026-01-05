#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiosink/IAudioSinkController.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class BnAudioSinkController : public ::android::BnInterface<IAudioSinkController> {
public:
  static constexpr uint32_t TRANSACTION_setAudioDecoder = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getAudioDecoder = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_queueAudioFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_flush = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getVolume = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_setVolume = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_setVolumeRamp = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioSinkController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioSinkController

class IAudioSinkControllerDelegator : public BnAudioSinkController {
public:
  explicit IAudioSinkControllerDelegator(::android::sp<IAudioSinkController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status setAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& audioDecoderId, bool* _aidl_return) override {
    return _aidl_delegate->setAudioDecoder(audioDecoderId, _aidl_return);
  }
  ::android::binder::Status getAudioDecoder(::com::rdk::hal::audiodecoder::IAudioDecoder::Id* _aidl_return) override {
    return _aidl_delegate->getAudioDecoder(_aidl_return);
  }
  ::android::binder::Status start() override {
    return _aidl_delegate->start();
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status queueAudioFrame(int64_t nsPresentationTime, int64_t bufferHandle, const ::com::rdk::hal::audiodecoder::FrameMetadata& metadata, bool* _aidl_return) override {
    return _aidl_delegate->queueAudioFrame(nsPresentationTime, bufferHandle, metadata, _aidl_return);
  }
  ::android::binder::Status flush() override {
    return _aidl_delegate->flush();
  }
  ::android::binder::Status getVolume(::com::rdk::hal::audiosink::Volume* _aidl_return) override {
    return _aidl_delegate->getVolume(_aidl_return);
  }
  ::android::binder::Status setVolume(const ::com::rdk::hal::audiosink::Volume& volume, bool* _aidl_return) override {
    return _aidl_delegate->setVolume(volume, _aidl_return);
  }
  ::android::binder::Status setVolumeRamp(double targetVolume, int32_t overMs, ::com::rdk::hal::audiosink::VolumeRamp volumeRamp, bool* _aidl_return) override {
    return _aidl_delegate->setVolumeRamp(targetVolume, overMs, volumeRamp, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioSinkController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioSinkController> _aidl_delegate;
};  // class IAudioSinkControllerDelegator
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
