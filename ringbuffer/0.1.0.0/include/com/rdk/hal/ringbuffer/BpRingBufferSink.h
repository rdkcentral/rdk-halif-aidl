#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSink.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class BpRingBufferSink : public ::android::BpInterface<IRingBufferSink> {
public:
  explicit BpRingBufferSink(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRingBufferSink() = default;
  ::android::binder::Status getFileDescriptor(::android::os::ParcelFileDescriptor* _aidl_return) override;
  ::android::binder::Status getInfo(::com::rdk::hal::ringbuffer::RingBufferInfo* _aidl_return) override;
  ::android::binder::Status setNotificationThreshold(int32_t bytes) override;
  ::android::binder::Status acquire(int32_t bytes, ::std::optional<::com::rdk::hal::ringbuffer::RingBufferAcquireResult>* _aidl_return) override;
  ::android::binder::Status release(const ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id& id, int32_t bytes) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpRingBufferSink
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
