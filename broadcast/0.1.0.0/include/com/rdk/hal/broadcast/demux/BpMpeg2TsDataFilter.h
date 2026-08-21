#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/demux/IMpeg2TsDataFilter.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BpMpeg2TsDataFilter : public ::android::BpInterface<IMpeg2TsDataFilter> {
public:
  explicit BpMpeg2TsDataFilter(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpMpeg2TsDataFilter() = default;
  ::android::binder::Status setPids(const ::std::vector<int32_t>& pids) override;
  ::android::binder::Status setAllPids() override;
  ::android::binder::Status maxPids(int32_t* _aidl_return) override;
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) override;
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& consumer) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpMpeg2TsDataFilter
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
