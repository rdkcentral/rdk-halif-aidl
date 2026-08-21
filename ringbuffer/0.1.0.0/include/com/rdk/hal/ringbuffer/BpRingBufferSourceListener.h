#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSourceListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class BpRingBufferSourceListener : public ::android::BpInterface<IRingBufferSourceListener> {
public:
  explicit BpRingBufferSourceListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRingBufferSourceListener() = default;
  ::android::binder::Status onDataAvailable(int32_t bytes) override;
  ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode code, const ::android::String16& message) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpRingBufferSourceListener
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
