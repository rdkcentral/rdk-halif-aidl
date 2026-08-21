#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSinkListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class BnRingBufferSinkListener : public ::android::BnInterface<IRingBufferSinkListener> {
public:
  static constexpr uint32_t TRANSACTION_onSpaceAvailable = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onFlushRequested = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onError = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnRingBufferSinkListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnRingBufferSinkListener

class IRingBufferSinkListenerDelegator : public BnRingBufferSinkListener {
public:
  explicit IRingBufferSinkListenerDelegator(::android::sp<IRingBufferSinkListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onSpaceAvailable(int32_t bytes) override {
    return _aidl_delegate->onSpaceAvailable(bytes);
  }
  ::android::binder::Status onFlushRequested() override {
    return _aidl_delegate->onFlushRequested();
  }
  ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode code, const ::android::String16& message) override {
    return _aidl_delegate->onError(code, message);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnRingBufferSinkListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IRingBufferSinkListener> _aidl_delegate;
};  // class IRingBufferSinkListenerDelegator
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
