#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSink.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSinkListener.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSource.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSourceListener.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class IRingBuffer : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBuffer)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status setSize(int32_t bytes) = 0;
  virtual ::android::binder::Status setOverflowing(bool enabled) = 0;
  virtual ::android::binder::Status registerProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& sink) = 0;
  virtual ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& source) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IRingBuffer

class IRingBufferDefault : public IRingBuffer {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setSize(int32_t /*bytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setOverflowing(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& /*sink*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& /*source*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IRingBufferDefault
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
