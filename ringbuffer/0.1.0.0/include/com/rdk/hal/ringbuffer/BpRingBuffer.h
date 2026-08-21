#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/ringbuffer/IRingBuffer.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class BpRingBuffer : public ::android::BpInterface<IRingBuffer> {
public:
  explicit BpRingBuffer(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRingBuffer() = default;
  ::android::binder::Status setSize(int32_t bytes) override;
  ::android::binder::Status setOverflowing(bool enabled) override;
  ::android::binder::Status registerProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) override;
  ::android::binder::Status unregisterProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& sink) override;
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) override;
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& source) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpRingBuffer
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
