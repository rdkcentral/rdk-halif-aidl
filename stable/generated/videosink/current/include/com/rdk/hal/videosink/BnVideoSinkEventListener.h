#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/videosink/IVideoSinkEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class BnVideoSinkEventListener : public ::android::BnInterface<IVideoSinkEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onFirstFrameRendered = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onEndOfStream = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onVideoUnderflow = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onVideoResumed = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onFlushComplete = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVideoSinkEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVideoSinkEventListener

class IVideoSinkEventListenerDelegator : public BnVideoSinkEventListener {
public:
  explicit IVideoSinkEventListenerDelegator(::android::sp<IVideoSinkEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onFirstFrameRendered(int64_t nsPresentationTime) override {
    return _aidl_delegate->onFirstFrameRendered(nsPresentationTime);
  }
  ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) override {
    return _aidl_delegate->onEndOfStream(nsPresentationTime);
  }
  ::android::binder::Status onVideoUnderflow() override {
    return _aidl_delegate->onVideoUnderflow();
  }
  ::android::binder::Status onVideoResumed() override {
    return _aidl_delegate->onVideoResumed();
  }
  ::android::binder::Status onFlushComplete() override {
    return _aidl_delegate->onFlushComplete();
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVideoSinkEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVideoSinkEventListener> _aidl_delegate;
};  // class IVideoSinkEventListenerDelegator
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
