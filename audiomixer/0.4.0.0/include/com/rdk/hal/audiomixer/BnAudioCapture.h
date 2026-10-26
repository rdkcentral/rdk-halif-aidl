#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiomixer/IAudioCapture.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BnAudioCapture : public ::android::BnInterface<IAudioCapture> {
public:
  static constexpr uint32_t TRANSACTION_getSharedMemory = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_releaseSharedMemory = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_releaseData = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioCapture();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioCapture

class IAudioCaptureDelegator : public BnAudioCapture {
public:
  explicit IAudioCaptureDelegator(::android::sp<IAudioCapture> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getSharedMemory(::std::vector<int64_t>* sharedMemorySizeBytes, ::android::os::ParcelFileDescriptor* _aidl_return) override {
    return _aidl_delegate->getSharedMemory(sharedMemorySizeBytes, _aidl_return);
  }
  ::android::binder::Status releaseSharedMemory() override {
    return _aidl_delegate->releaseSharedMemory();
  }
  ::android::binder::Status start() override {
    return _aidl_delegate->start();
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status releaseData(int64_t offsetBytes, int32_t lengthBytes) override {
    return _aidl_delegate->releaseData(offsetBytes, lengthBytes);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioCapture::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioCapture> _aidl_delegate;
};  // class IAudioCaptureDelegator
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
