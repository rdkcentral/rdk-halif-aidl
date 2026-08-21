#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/ringbuffer/IRingBuffer.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class BnRingBuffer : public ::android::BnInterface<IRingBuffer> {
public:
  static constexpr uint32_t TRANSACTION_setSize = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_setOverflowing = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_registerProducer = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_unregisterProducer = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_registerConsumer = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_unregisterConsumer = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnRingBuffer();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnRingBuffer

class IRingBufferDelegator : public BnRingBuffer {
public:
  explicit IRingBufferDelegator(::android::sp<IRingBuffer> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status setSize(int32_t bytes) override {
    return _aidl_delegate->setSize(bytes);
  }
  ::android::binder::Status setOverflowing(bool enabled) override {
    return _aidl_delegate->setOverflowing(enabled);
  }
  ::android::binder::Status registerProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) override {
    return _aidl_delegate->registerProducer(listener, _aidl_return);
  }
  ::android::binder::Status unregisterProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& sink) override {
    return _aidl_delegate->unregisterProducer(sink);
  }
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) override {
    return _aidl_delegate->registerConsumer(listener, _aidl_return);
  }
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& source) override {
    return _aidl_delegate->unregisterConsumer(source);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnRingBuffer::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IRingBuffer> _aidl_delegate;
};  // class IRingBufferDelegator
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
