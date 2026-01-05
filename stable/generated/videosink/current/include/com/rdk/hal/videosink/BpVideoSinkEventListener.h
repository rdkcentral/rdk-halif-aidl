#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/videosink/IVideoSinkEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class BpVideoSinkEventListener : public ::android::BpInterface<IVideoSinkEventListener> {
public:
  explicit BpVideoSinkEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVideoSinkEventListener() = default;
  ::android::binder::Status onFirstFrameRendered(int64_t nsPresentationTime) override;
  ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) override;
  ::android::binder::Status onVideoUnderflow() override;
  ::android::binder::Status onVideoResumed() override;
  ::android::binder::Status onFlushComplete() override;
  ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVideoSinkEventListener
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
