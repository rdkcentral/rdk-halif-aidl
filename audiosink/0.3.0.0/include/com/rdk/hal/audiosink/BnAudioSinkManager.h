#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/audiosink/IAudioSinkManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class BnAudioSinkManager : public ::android::BnInterface<IAudioSinkManager> {
public:
  static constexpr uint32_t TRANSACTION_getAudioSinkIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getPlatformCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getAudioSink = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioSinkManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioSinkManager

class IAudioSinkManagerDelegator : public BnAudioSinkManager {
public:
  explicit IAudioSinkManagerDelegator(::android::sp<IAudioSinkManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getAudioSinkIds(::std::vector<::com::rdk::hal::audiosink::IAudioSink::Id>* _aidl_return) override {
    return _aidl_delegate->getAudioSinkIds(_aidl_return);
  }
  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::audiosink::PlatformCapabilities* _aidl_return) override {
    return _aidl_delegate->getPlatformCapabilities(_aidl_return);
  }
  ::android::binder::Status getAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& audioSinkId, ::android::sp<::com::rdk::hal::audiosink::IAudioSink>* _aidl_return) override {
    return _aidl_delegate->getAudioSink(audioSinkId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioSinkManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioSinkManager> _aidl_delegate;
};  // class IAudioSinkManagerDelegator
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
