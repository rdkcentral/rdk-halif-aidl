#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSink.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class BnRingBufferSink : public ::android::BnInterface<IRingBufferSink> {
public:
  static constexpr uint32_t TRANSACTION_getFileDescriptor = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInfo = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setNotificationThreshold = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_acquire = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_release = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnRingBufferSink();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnRingBufferSink

class IRingBufferSinkDelegator : public BnRingBufferSink {
public:
  explicit IRingBufferSinkDelegator(::android::sp<IRingBufferSink> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getFileDescriptor(::android::os::ParcelFileDescriptor* _aidl_return) override {
    return _aidl_delegate->getFileDescriptor(_aidl_return);
  }
  ::android::binder::Status getInfo(::com::rdk::hal::ringbuffer::RingBufferInfo* _aidl_return) override {
    return _aidl_delegate->getInfo(_aidl_return);
  }
  ::android::binder::Status setNotificationThreshold(int32_t bytes) override {
    return _aidl_delegate->setNotificationThreshold(bytes);
  }
  ::android::binder::Status acquire(int32_t bytes, ::std::optional<::com::rdk::hal::ringbuffer::RingBufferAcquireResult>* _aidl_return) override {
    return _aidl_delegate->acquire(bytes, _aidl_return);
  }
  ::android::binder::Status release(const ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id& id, int32_t bytes) override {
    return _aidl_delegate->release(id, bytes);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnRingBufferSink::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IRingBufferSink> _aidl_delegate;
};  // class IRingBufferSinkDelegator
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
