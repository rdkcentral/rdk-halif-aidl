#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSinkListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class BpRingBufferSinkListener : public ::android::BpInterface<IRingBufferSinkListener> {
public:
  explicit BpRingBufferSinkListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRingBufferSinkListener() = default;
  ::android::binder::Status onSpaceAvailable(int32_t bytes) override;
  ::android::binder::Status onFlushRequested() override;
  ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode code, const ::android::String16& message) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpRingBufferSinkListener
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
