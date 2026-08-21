#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/demux/IDemuxSoftwareInput.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BpDemuxSoftwareInput : public ::android::BpInterface<IDemuxSoftwareInput> {
public:
  explicit BpDemuxSoftwareInput(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDemuxSoftwareInput() = default;
  ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id* _aidl_return) override;
  ::android::binder::Status openForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) override;
  ::android::binder::Status closeForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& bufferSink) override;
  ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) override;
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDemuxSoftwareInput
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
